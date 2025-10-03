#include "VisaInstrument.hpp"
#include "exceptions.hpp"

#include <visa.h> // The actual VISA C API header
#include <vector>
#include <utility> // For std::swap
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds
#include <string>  // For std::stoi, std::to_string
#include <algorithm> // For trim function

namespace {
// Helper to trim leading/trailing whitespace, making string parsing more robust.
std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) {
        return ""; // String is all whitespace
    }
    auto end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, (end - start + 1));
}
} // namespace

namespace cvisa {

// --- Constructor and Destructor ---

VisaInstrument::VisaInstrument(const std::string& resourceName,
                               std::optional<unsigned int> timeout_ms,
                               std::optional<char> read_termination,
                               std::optional<char> write_termination) {
    ViStatus status = viOpenDefaultRM(&m_resourceManagerHandle);
    if (status < VI_SUCCESS) {
        throw ConnectionException("Failed to open VISA Default Resource Manager.");
    }

    status = viOpen(m_resourceManagerHandle, const_cast<char*>(resourceName.c_str()), VI_NULL, VI_NULL, &m_instrumentHandle);
    if (status < VI_SUCCESS) {
        viClose(m_resourceManagerHandle); // Clean up RM handle before throwing
        throw ConnectionException("Failed to connect to instrument: " + resourceName);
    }

    // Apply optional settings now that the connection is established
    if (timeout_ms) {
        setTimeout(*timeout_ms);
    }
    if (read_termination) {
        setReadTermination(*read_termination);
    }
    if (write_termination) {
        setWriteTermination(*write_termination);
    }
}

VisaInstrument::~VisaInstrument() {
    closeConnection();
}

void VisaInstrument::closeConnection() {
    // Destructors must not throw. We call viClose but don't check the status.
    if (m_instrumentHandle != VI_NULL) {
        viClose(m_instrumentHandle);
        m_instrumentHandle = VI_NULL;
    }
    if (m_resourceManagerHandle != VI_NULL) {
        viClose(m_resourceManagerHandle);
        m_resourceManagerHandle = VI_NULL;
    }
}


// --- Move Semantics ---

VisaInstrument::VisaInstrument(VisaInstrument&& other) noexcept {
    m_resourceManagerHandle = other.m_resourceManagerHandle;
    m_instrumentHandle = other.m_instrumentHandle;
    other.m_resourceManagerHandle = VI_NULL;
    other.m_instrumentHandle = VI_NULL;
}

VisaInstrument& VisaInstrument::operator=(VisaInstrument&& other) noexcept {
    if (this != &other) {
        closeConnection();
        m_resourceManagerHandle = other.m_resourceManagerHandle;
        m_instrumentHandle = other.m_instrumentHandle;
        other.m_resourceManagerHandle = VI_NULL;
        other.m_instrumentHandle = VI_NULL;
    }
    return *this;
}


// --- Core I/O Operations ---

void VisaInstrument::write(const std::string& command) {
    ViUInt32 returnCount = 0;
    ViStatus status = viWrite(m_instrumentHandle, (unsigned char*)command.c_str(), static_cast<ViUInt32>(command.length()), &returnCount);
    checkStatus(status, "viWrite");
}

std::string VisaInstrument::read(size_t bufferSize) {
    std::vector<char> buffer(bufferSize);
    ViUInt32 returnCount = 0;
    ViStatus status = viRead(m_instrumentHandle, (unsigned char*)buffer.data(), static_cast<ViUInt32>(buffer.size()), &returnCount);
    checkStatus(status, "viRead");
    return std::string(buffer.data(), returnCount);
}

std::string VisaInstrument::query(const std::string& command, size_t bufferSize, unsigned int delay_ms) {
    write(command);
    if (delay_ms > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    return read(bufferSize);
}


// --- SCPI Convenience Methods ---

std::string VisaInstrument::getIdentification(const std::string& cmd) {
    return trim(query(cmd));
}

void VisaInstrument::reset(const std::string& cmd) {
    write(cmd);
}

void VisaInstrument::clearStatus(const std::string& cmd) {
    write(cmd);
}

void VisaInstrument::waitToContinue(const std::string& cmd) {
    write(cmd);
}

bool VisaInstrument::isOperationComplete(const std::string& cmd) {
    return trim(query(cmd)) == "1";
}

int VisaInstrument::runSelfTest(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return std::stoi(response);
    } catch (const std::exception& e) {
        throw CommandException("Invalid response from self-test query ('" + cmd + "'): " + response);
    }
}

uint8_t VisaInstrument::getStatusByte(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getStatusByte ('" + cmd + "'): " + response);
    }
}

uint8_t VisaInstrument::getEventStatusRegister(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getEventStatusRegister ('" + cmd + "'): " + response);
    }
}

void VisaInstrument::setEventStatusEnable(uint8_t mask, const std::string& cmd_prefix) {
    write(cmd_prefix + " " + std::to_string(mask));
}

uint8_t VisaInstrument::getEventStatusEnable(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getEventStatusEnable ('" + cmd + "'): " + response);
    }
}

void VisaInstrument::setServiceRequestEnable(uint8_t mask, const std::string& cmd_prefix) {
    write(cmd_prefix + " " + std::to_string(mask));
}

uint8_t VisaInstrument::getServiceRequestEnable(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getServiceRequestEnable ('" + cmd + "'): " + response);
    }
}


// --- Configuration ---

void VisaInstrument::setTimeout(unsigned int timeout_ms) {
    ViStatus status = viSetAttribute(m_instrumentHandle, VI_ATTR_TMO_VALUE, timeout_ms);
    checkStatus(status, "viSetAttribute (Timeout)");
}

void VisaInstrument::setReadTermination(char term_char, bool enable) {
    ViStatus status;
    status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR, static_cast<ViInt8>(term_char));
    checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR for Read)");

    status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR_EN, enable ? VI_TRUE : VI_FALSE);
    checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR_EN for Read)");
}

void VisaInstrument::setWriteTermination(char term_char) {
    ViStatus status;
    status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR, static_cast<ViInt8>(term_char));
    checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR for Write)");

    status = viSetAttribute(m_instrumentHandle, VI_ATTR_SEND_END_EN, VI_TRUE);
    checkStatus(status, "viSetAttribute (VI_ATTR_SEND_END_EN for Write)");
}


// --- Private Helper ---

void VisaInstrument::checkStatus(ViStatus status, const std::string& functionName) {
    if (status < VI_SUCCESS) {
        char errorBuffer[256] = {0};
        // Use the resource manager handle to get error descriptions, as it's more reliable.
        viStatusDesc(m_resourceManagerHandle, status, errorBuffer);

        std::string errorMessage = "VISA Error in " + functionName + ": " + errorBuffer + " (Status: " + std::to_string(status) + ")";

        if (status == VI_ERROR_TMO) { // Timeout is a command error
             throw CommandException(errorMessage);
        }
        if (status == VI_ERROR_RSRC_NFOUND || status == VI_ERROR_RSRC_LOCKED || status == VI_ERROR_CONN_LOST) {
            throw ConnectionException(errorMessage);
        } else if (status == VI_ERROR_INV_EXPR || status == VI_ERROR_NLISTENERS) {
            throw CommandException(errorMessage);
        } else {
            throw VisaException(errorMessage);
        }
    }
}

} // namespace cvisa