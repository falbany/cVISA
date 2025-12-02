#include "VisaInterface.hpp"

#include <visa.h>

#include <chrono>
#include <string>
#include <thread>
#include <utility>  // for std::move
#include <vector>

#include "Logger.hpp"
#include "exceptions.hpp"
#include "utils.hpp"

namespace cvisa {

// --- Constructors and Destructor ---

VisaInterface::VisaInterface()
    : m_timeout_ms(0),
      m_timeout_ms_set(false),
      m_read_termination('\n'),
      m_read_termination_set(false),
      m_write_termination('\n'),
      m_write_termination_set(false),
      m_resourceManagerHandle(VI_NULL),
      m_instrumentHandle(VI_NULL),
      m_logLevel(LogLevel::WARNING),
      m_autoErrorCheckEnabled(false) {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "VisaInterface default constructed.");
}

VisaInterface::VisaInterface(const std::string& resourceName)
    : VisaInterface() {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "VisaInterface constructed with resource name.");
    setResource(resourceName);
    connect();
}

VisaInterface::VisaInterface(const std::string& resourceName,
                             unsigned int timeout_ms, char read_termination)
    : VisaInterface() {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "VisaInterface constructed with resource, timeout, and term "
                "char.");
    setResource(resourceName);
    setTimeout(timeout_ms);
    setReadTermination(read_termination);
    connect();
}

VisaInterface::~VisaInterface() {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "VisaInterface destructed.");
    disconnect();
}

// --- Manual Connection Management ---

void VisaInterface::setResource(const std::string& resourceName) {
    if (isConnected()) {
        Logger::log(m_logLevel, LogLevel::ERROR, m_resourceName,
                    "Attempted to set resource while already connected.");
        throw ConnectionException("Cannot set resource while connected.");
    }
    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Setting resource to: " + resourceName);
    m_resourceName = resourceName;
}

void VisaInterface::connect() {
    if (isConnected()) {
        Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                    "Connect called but already connected.");
        return;
    }
    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Attempting to connect...");
    if (m_resourceName.empty()) {
        Logger::log(m_logLevel, LogLevel::ERROR, m_resourceName,
                    "Connection failed: resource name is empty.");
        throw ConnectionException(
            "Cannot connect: VISA resource name is not set.");
    }
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Resource name: " + m_resourceName);

    ViStatus status = viOpenDefaultRM(&m_resourceManagerHandle);
    if (status < VI_SUCCESS) {
        Logger::log(m_logLevel, LogLevel::ERROR, m_resourceName,
                    "Failed to open VISA Default Resource Manager.");
        throw ConnectionException(
            "Failed to open VISA Default Resource Manager.");
    }

    status = viOpen(m_resourceManagerHandle,
                    const_cast<char*>(m_resourceName.c_str()), VI_NULL, VI_NULL,
                    &m_instrumentHandle);
    if (status < VI_SUCCESS) {
        viClose(m_resourceManagerHandle);
        m_resourceManagerHandle = VI_NULL;
        Logger::log(m_logLevel, LogLevel::ERROR, m_resourceName,
                    "Failed to connect to instrument: " + m_resourceName);
        throw ConnectionException("Failed to connect to instrument: " +
                                  m_resourceName);
    }

    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Successfully connected to " + m_resourceName);
    applyConfiguration();
}

void VisaInterface::disconnect() {
    if (!isConnected()) {
        return;
    }
    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Disconnecting from " + m_resourceName);
    if (m_instrumentHandle != VI_NULL) {
        viClose(m_instrumentHandle);
        m_instrumentHandle = VI_NULL;
        Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                    "Instrument handle closed.");
    }
    if (m_resourceManagerHandle != VI_NULL) {
        viClose(m_resourceManagerHandle);
        m_resourceManagerHandle = VI_NULL;
        Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                    "Resource manager handle closed.");
    }
    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Disconnection complete.");
}

bool VisaInterface::isConnected() const {
    return m_instrumentHandle != VI_NULL;
}

// --- Move Semantics ---

VisaInterface::VisaInterface(VisaInterface&& other) noexcept
    : m_resourceName(std::move(other.m_resourceName)),
      m_timeout_ms(other.m_timeout_ms),
      m_timeout_ms_set(other.m_timeout_ms_set),
      m_read_termination(other.m_read_termination),
      m_read_termination_set(other.m_read_termination_set),
      m_write_termination(other.m_write_termination),
      m_write_termination_set(other.m_write_termination_set),
      m_resourceManagerHandle(other.m_resourceManagerHandle),
      m_instrumentHandle(other.m_instrumentHandle),
      m_logLevel(other.m_logLevel) {
    other.m_resourceManagerHandle = VI_NULL;
    other.m_instrumentHandle = VI_NULL;
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "VisaInterface move constructed.");
}

VisaInterface& VisaInterface::operator=(VisaInterface&& other) noexcept {
    if (this != &other) {
        disconnect();
        m_resourceName = std::move(other.m_resourceName);
        m_timeout_ms = other.m_timeout_ms;
        m_timeout_ms_set = other.m_timeout_ms_set;
        m_read_termination = other.m_read_termination;
        m_read_termination_set = other.m_read_termination_set;
        m_write_termination = other.m_write_termination;
        m_write_termination_set = other.m_write_termination_set;
        m_resourceManagerHandle = other.m_resourceManagerHandle;
        m_instrumentHandle = other.m_instrumentHandle;
        m_logLevel = other.m_logLevel;
        other.m_resourceManagerHandle = VI_NULL;
        other.m_instrumentHandle = VI_NULL;
        Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                    "VisaInterface move assigned.");
    }
    return *this;
}

// --- Core I/O Operations ---

void VisaInterface::write(const std::string& command) {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot write.");
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Writing command: " + command);
    ViUInt32 returnCount = 0;
    ViStatus status =
        viWrite(m_instrumentHandle, (unsigned char*)command.c_str(),
                static_cast<ViUInt32>(command.length()), &returnCount);
    checkStatus(status, "viWrite");
}

void VisaInterface::writeBinary(const std::vector<uint8_t>& data) {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot write binary data.");
    Logger::log(
        m_logLevel, LogLevel::DEBUG, m_resourceName,
        "Writing binary data of size: " + utils::to_string(data.size()));
    ViUInt32 returnCount = 0;
    ViStatus status = viWrite(m_instrumentHandle, (unsigned char*)data.data(),
                              static_cast<ViUInt32>(data.size()), &returnCount);
    checkStatus(status, "viWrite (binary)");
}

std::string VisaInterface::read(size_t bufferSize) {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot read.");
    Logger::log(
        m_logLevel, LogLevel::DEBUG,
        "Reading data (buffer size: " + utils::to_string(bufferSize) + ")");
    std::vector<char> buffer(bufferSize);
    ViUInt32 returnCount = 0;
    ViStatus status =
        viRead(m_instrumentHandle, (unsigned char*)buffer.data(),
               static_cast<ViUInt32>(buffer.size()), &returnCount);
    checkStatus(status, "viRead");
    std::string result(buffer.data(), returnCount);
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Read " + utils::to_string(returnCount) + " bytes: " + result);
    return result;
}

std::vector<uint8_t> VisaInterface::readBinary(size_t bufferSize) {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot read binary data.");
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Reading binary data (buffer size: " +
                    utils::to_string(bufferSize) + ")");
    std::vector<uint8_t> buffer(bufferSize);
    ViUInt32 returnCount = 0;
    ViStatus status =
        viRead(m_instrumentHandle, buffer.data(),
               static_cast<ViUInt32>(buffer.size()), &returnCount);
    checkStatus(status, "viRead (binary)");
    buffer.resize(returnCount);
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Read " + utils::to_string(returnCount) + " binary bytes.");
    return buffer;
}

std::string VisaInterface::query(const std::string& command, size_t bufferSize,
                                 unsigned int delay_ms) {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot query.");
    write(command);
    if (delay_ms > 0) {
        Logger::log(m_logLevel, LogLevel::DEBUG,
                    "Delaying for " + utils::to_string(delay_ms) +
                        "ms before reading.");
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    return read(bufferSize);
}

std::future<std::string> VisaInterface::queryAsync(const std::string& command,
                                                   size_t bufferSize,
                                                   unsigned int delay_ms) {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot query asynchronously.");
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Starting asynchronous query.");
    return std::async(std::launch::async,
                      [this, command, bufferSize, delay_ms]() {
                          return this->query(command, bufferSize, delay_ms);
                      });
}

// --- Instrument Control & Status ---

void VisaInterface::clear() {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot clear.");
    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Clearing instrument interface.");
    ViStatus status = viClear(m_instrumentHandle);
    checkStatus(status, "viClear");
}

uint8_t VisaInterface::readStatusByte() {
    if (!isConnected())
        throw ConnectionException(
            "Not connected to an instrument. Cannot read status byte.");
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Reading status byte.");
    ViUInt16 statusByte = 0;
    ViStatus status = viReadSTB(m_instrumentHandle, &statusByte);
    checkStatus(status, "viReadSTB");
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Status byte received: " + utils::to_string(statusByte));
    return static_cast<uint8_t>(statusByte);
}

// --- Configuration ---

void VisaInterface::setVerbose(LogLevel level) {
    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Changing log level.");
    m_logLevel = level;
}

void VisaInterface::enableAutoErrorCheck(bool enable) {
    Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                "Automatic error checking " +
                    std::string(enable ? "enabled" : "disabled") + ".");
    m_autoErrorCheckEnabled = enable;
}

void VisaInterface::setTimeout(unsigned int timeout_ms) {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Setting timeout to " + utils::to_string(timeout_ms) + " ms.");
    m_timeout_ms = timeout_ms;
    m_timeout_ms_set = true;
    if (isConnected()) {
        ViStatus status =
            viSetAttribute(m_instrumentHandle, VI_ATTR_TMO_VALUE, m_timeout_ms);
        checkStatus(status, "viSetAttribute (Timeout)");
    }
}

void VisaInterface::setReadTermination(char term_char, bool enable) {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Setting read termination character to '" +
                    std::string(1, term_char) +
                    "' with enable=" + utils::to_string(enable));
    m_read_termination = term_char;
    m_read_termination_set = enable;
    if (isConnected()) {
        ViStatus status;
        status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR,
                                static_cast<ViInt8>(m_read_termination));
        checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR for Read)");
        status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR_EN,
                                m_read_termination_set ? VI_TRUE : VI_FALSE);
        checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR_EN for Read)");
    }
}

void VisaInterface::setWriteTermination(char term_char) {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Setting write termination character to '" +
                    std::string(1, term_char) + "'.");
    m_write_termination = term_char;
    m_write_termination_set = true;
    if (isConnected()) {
        ViStatus status;
        status = viSetAttribute(m_instrumentHandle, VI_ATTR_TERMCHAR,
                                static_cast<ViInt8>(m_write_termination));
        checkStatus(status, "viSetAttribute (VI_ATTR_TERMCHAR for Write)");
        status =
            viSetAttribute(m_instrumentHandle, VI_ATTR_SEND_END_EN, VI_TRUE);
        checkStatus(status, "viSetAttribute (VI_ATTR_SEND_END_EN for Write)");
    }
}

// --- Static Utilities ---

std::vector<std::string> VisaInterface::findResources(
    const std::string& query) {
    ViSession rmSession = VI_NULL;
    ViStatus status = viOpenDefaultRM(&rmSession);
    if (status < VI_SUCCESS) {
        throw VisaException(
            "Could not open VISA Default Resource Manager to find resources.");
    }

    ViFindList findList;
    ViUInt32 returnCount = 0;
    char instrumentDescription[VI_FIND_BUFLEN];
    std::vector<std::string> resources;

    status = viFindRsrc(rmSession, const_cast<char*>(query.c_str()), &findList,
                        &returnCount, instrumentDescription);
    if (status < VI_SUCCESS) {
        viClose(rmSession);
        if (status == VI_ERROR_RSRC_NFOUND) return {};
        throw VisaException("Failed to find VISA resources.");
    }

    resources.emplace_back(instrumentDescription);
    for (ViUInt32 i = 1; i < returnCount; ++i) {
        status = viFindNext(findList, instrumentDescription);
        if (status < VI_SUCCESS) break;
        resources.emplace_back(instrumentDescription);
    }

    viClose(findList);
    viClose(rmSession);

    return resources;
}

// --- Private Helpers ---

void VisaInterface::applyConfiguration() {
    Logger::log(m_logLevel, LogLevel::DEBUG, m_resourceName,
                "Applying stored configurations.");
    if (m_timeout_ms_set) setTimeout(m_timeout_ms);
    if (m_read_termination_set) setReadTermination(m_read_termination, true);
    if (m_write_termination_set) setWriteTermination(m_write_termination);
}

void VisaInterface::checkStatus(ViStatus status,
                                const std::string& functionName) {
    if (status < VI_SUCCESS) {
        char errorBuffer[256] = {0};
        viStatusDesc(m_resourceManagerHandle, status, errorBuffer);
        std::string errorMessage =
            "VISA Error in " + functionName + ": " + errorBuffer +
            " (Status: " + utils::to_string(status) + ")";
        Logger::log(m_logLevel, LogLevel::ERROR, m_resourceName, errorMessage);
        if (status == VI_ERROR_TMO) throw TimeoutException(errorMessage);
        if (status == VI_ERROR_RSRC_NFOUND || status == VI_ERROR_RSRC_LOCKED ||
            status == VI_ERROR_CONN_LOST) {
            throw ConnectionException(errorMessage);
        } else if (status == VI_ERROR_INV_EXPR ||
                   status == VI_ERROR_NLISTENERS) {
            throw CommandException(errorMessage);
        } else {
            throw VisaException(errorMessage);
        }
    }
}

}  // namespace cvisa
