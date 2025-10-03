#include "VisaInstrument.hpp"
#include "exceptions.hpp"

#include <visa.h> // The actual VISA C API header
#include <vector>
#include <utility> // For std::swap

namespace cvisa {

// --- Constructor and Destructor ---

VisaInstrument::VisaInstrument(const std::string& resourceName) {
    ViStatus status = viOpenDefaultRM(&m_resourceManagerHandle);
    if (status < VI_SUCCESS) {
        // We can't use checkStatus here because we don't have a handle yet
        // to query the description. So, we throw a more generic message.
        throw ConnectionException("Failed to open VISA Default Resource Manager.");
    }

    status = viOpen(m_resourceManagerHandle, const_cast<char*>(resourceName.c_str()), VI_NULL, VI_NULL, &m_instrumentHandle);
    if (status < VI_SUCCESS) {
        viClose(m_resourceManagerHandle); // Clean up the RM handle
        throw ConnectionException("Failed to connect to instrument: " + resourceName);
    }
}

VisaInstrument::~VisaInstrument() {
    closeConnection();
}

void VisaInstrument::closeConnection() {
    // Destructors should not throw. We call viClose but don't check status.
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
    // Steal the resources from the other object
    m_resourceManagerHandle = other.m_resourceManagerHandle;
    m_instrumentHandle = other.m_instrumentHandle;

    // Leave the other object in a valid but empty state
    other.m_resourceManagerHandle = VI_NULL;
    other.m_instrumentHandle = VI_NULL;
}

VisaInstrument& VisaInstrument::operator=(VisaInstrument&& other) noexcept {
    if (this != &other) {
        // 1. Release our own resources
        closeConnection();

        // 2. Steal resources from the other object
        m_resourceManagerHandle = other.m_resourceManagerHandle;
        m_instrumentHandle = other.m_instrumentHandle;

        // 3. Leave the other object in a valid but empty state
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

    // Return the part of the buffer that was actually filled
    return std::string(buffer.data(), returnCount);
}

std::string VisaInstrument::query(const std::string& command, size_t bufferSize) {
    write(command);
    return read(bufferSize);
}


// --- SCPI Convenience Methods ---

std::string VisaInstrument::getIdentification(const std::string& cmd) {
    return query(cmd);
}

void VisaInstrument::reset(const std::string& cmd) {
    write(cmd);
}

void VisaInstrument::clearStatus(const std::string& cmd) {
    write(cmd);
}


// --- Configuration ---

void VisaInstrument::setTimeout(unsigned int timeout_ms) {
    ViStatus status = viSetAttribute(m_instrumentHandle, VI_ATTR_TMO_VALUE, timeout_ms);
    checkStatus(status, "viSetAttribute (Timeout)");
}


// --- Private Helper ---

void VisaInstrument::checkStatus(ViStatus status, const std::string& functionName) {
    if (status < VI_SUCCESS) {
        // Buffer to hold the error description
        char errorBuffer[256] = {0};
        // Ask the VISA library for a description of the error
        viStatusDesc(m_instrumentHandle, status, errorBuffer);

        std::string errorMessage = "VISA Error in " + functionName + ": " + errorBuffer;

        // Decide which exception type is more appropriate
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