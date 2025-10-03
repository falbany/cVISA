#include "VisaInterface.hpp"
#include "exceptions.hpp"

#include <visa.h>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include <string>
#include <algorithm>

namespace {
// Helper to trim leading/trailing whitespace
std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, (end - start + 1));
}
} // namespace

namespace cvisa {

// --- Constructor and Destructor ---

VisaInterface::VisaInterface(const std::string& resourceName,
                               std::optional<unsigned int> timeout_ms,
                               std::optional<char> read_termination,
                               std::optional<char> write_termination) {
    ViStatus status = viOpenDefaultRM(&m_resourceManagerHandle);
    if (status < VI_SUCCESS) {
        throw ConnectionException("Failed to open VISA Default Resource Manager.");
    }

    status = viOpen(m_resourceManagerHandle, const_cast<char*>(resourceName.c_str()), VI_NULL, VI_NULL, &m_instrumentHandle);
    if (status < VI_SUCCESS) {
        viClose(m_resourceManagerHandle);
        throw ConnectionException("Failed to connect to instrument: " + resourceName);
    }

    if (timeout_ms) setTimeout(*timeout_ms);
    if (read_termination) setReadTermination(*read_termination);
    if (write_termination) setWriteTermination(*write_termination);
}

VisaInterface::~VisaInterface() {
    closeConnection();
}

void VisaInterface::closeConnection() {
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

VisaInterface::VisaInterface(VisaInterface&& other) noexcept {
    m_resourceManagerHandle = other.m_resourceManagerHandle;
    m_instrumentHandle = other.m_instrumentHandle;
    other.m_resourceManagerHandle = VI_NULL;
    other.m_instrumentHandle = VI_NULL;
}

VisaInterface& VisaInterface::operator=(VisaInterface&& other) noexcept {
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

void VisaInterface::write(const std::string& command) {
    ViUInt32 returnCount = 0;
    ViStatus status = viWrite(m_instrumentHandle, (unsigned char*)command.c_str(), static_cast<ViUInt32>(command.length()), &returnCount);
    checkStatus(status, "viWrite");
}

std::string VisaInterface::read(size_t bufferSize) {
    std::vector<char> buffer(bufferSize);
    ViUInt32 returnCount = 0;
    ViStatus status = viRead(m_instrumentHandle, (unsigned char*)buffer.data(), static_cast<ViUInt32>(buffer.size()), &returnCount);
    checkStatus(status, "viRead");
    return std::string(buffer.data(), returnCount);
}

std::string VisaInterface::query(const std::string& command, size_t bufferSize, unsigned int delay_ms) {
    write(command);
    if (delay_ms > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    return read(bufferSize);
}

// --- SCPI Convenience Methods ---

std::string VisaInterface::getIdentification(const std::string& cmd) {
    return trim(query(cmd));
}

void VisaInterface::reset(const std::string& cmd) {
    write(cmd);
}

void VisaInterface::clearStatus(const std::string& cmd) {
    write(cmd);
}

void VisaInterface::waitToContinue(const std::string& cmd) {
    write(cmd);
}

bool VisaInterface::isOperationComplete(const std::string& cmd) {
    return trim(query(cmd)) == "1";
}

int VisaInterface::runSelfTest(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return std::stoi(response);
    } catch (const std::exception& e) {
        throw CommandException("Invalid response from self-test query ('" + cmd + "'): " + response);
    }
}

uint8_t VisaInterface::getStatusByte(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getStatusByte ('" + cmd + "'): " + response);
    }
}

uint8_t VisaInterface::getEventStatusRegister(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getEventStatusRegister ('" + cmd + "'): " + response);
    }
}

void VisaInterface::setEventStatusEnable(uint8_t mask, const std::string& cmd_prefix) {
    write(cmd_prefix + " " + std::to_string(mask));
}

uint8_t VisaInterface::getEventStatusEnable(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getEventStatusEnable ('" + cmd + "'): " + response);
    }
}

void VisaInterface::setServiceRequestEnable(uint8_t mask, const std::string& cmd_prefix) {
    write(cmd_prefix + " " + std::to_string(mask));
}

uint8_t VisaInterface::getServiceRequestEnable(const std::string& cmd) {
    std::string response = trim(query(cmd));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getServiceRequestEnable ('" + cmd + "'): " + response);
    }
}

// --- Configuration ---

void VisaInterface::setTimeout(unsigned int timeout_ms) {
    ViStatus status = viSetAttribute(m_instrumentHandle, VI_ATTR_TMO_VALUE, timeout_ms);
    checkStatus(status, "viSetAttribute (Timeout)");
}

void VisaInterface::setReadTermination(char term_char, bool enable) {
    ViStatus status;
    status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR, static_cast<ViInt8>(term_char));
    checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR for Read)");
    status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR_EN, enable ? VI_TRUE : VI_FALSE);
    checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR_EN for Read)");
}

void VisaInterface::setWriteTermination(char term_char) {
    ViStatus status;
    status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR, static_cast<ViInt8>(term_char));
    checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR for Write)");
    status = viSetAttribute(m_instrumentHandle, VI_ATTR_SEND_END_EN, VI_TRUE);
    checkStatus(status, "viSetAttribute (VI_ATTR_SEND_END_EN for Write)");
}

// --- Static Utilities ---

std::vector<std::string> VisaInterface::findResources(const std::string& query) {
    ViSession rmSession = VI_NULL;
    ViStatus status = viOpenDefaultRM(&rmSession);
    if (status < VI_SUCCESS) {
        throw VisaException("Could not open VISA Default Resource Manager to find resources.");
    }

    ViFindList findList;
    ViUInt32 returnCount = 0;
    char instrumentDescription[VI_FIND_BUFLEN];
    std::vector<std::string> resources;

    status = viFindRsrc(rmSession, const_cast<char*>(query.c_str()), &findList, &returnCount, instrumentDescription);

    if (status < VI_SUCCESS) {
        viClose(rmSession);
        // VI_ERROR_RSRC_NFOUND is a normal condition if no instruments are found.
        if (status == VI_ERROR_RSRC_NFOUND) {
            return {}; // Return an empty list, not an error.
        }
        throw VisaException("Failed to find VISA resources.");
    }

    resources.push_back(instrumentDescription);

    for (ViUInt32 i = 1; i < returnCount; ++i) {
        status = viFindNext(findList, instrumentDescription);
        if (status < VI_SUCCESS) {
            // Clean up and ignore errors on findNext, just stop searching.
            break;
        }
        resources.push_back(instrumentDescription);
    }

    // Clean up the find list and the resource manager session
    viClose(findList);
    viClose(rmSession);

    return resources;
}

// --- Private Helper ---

void VisaInterface::checkStatus(ViStatus status, const std::string& functionName) {
    if (status < VI_SUCCESS) {
        char errorBuffer[256] = {0};
        viStatusDesc(m_resourceManagerHandle, status, errorBuffer);
        std::string errorMessage = "VISA Error in " + functionName + ": " + errorBuffer + " (Status: " + std::to_string(status) + ")";
        if (status == VI_ERROR_TMO) {
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