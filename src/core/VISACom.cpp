#include "exceptions.hpp"
#include "Logger.hpp"
#include "VISACom.hpp"
#include "RealVISABackend.hpp"
#include "../utils/utils.hpp"
#include "../internal/visatype.h"

#include <chrono>
#include <string>
#include <thread>
#include <utility>    // for std::move
#include <vector>

namespace cvisa {

    // --- Constructors and Destructor ---

    VISACom::VISACom() : VISACom(nullptr, true) {}

    VISACom::VISACom(IVISABackend* backend, bool ownBackend)
        : mTimeout(0),
          mTimeoutSet(false),
          mReadTermChar('\n'),
          mReadTermCharSet(false),
          mWriteTermChar('\n'),
          mWriteTermSet(false),
          mRmHandle(VI_NULL),
          mInstHandle(VI_NULL),
          mBackend(backend),
          mOwnBackend(ownBackend),
          mLogLevel(LogLevel::WARNING),
          mAutoErrorCheck(false) {
        if (mBackend == nullptr) {
            mBackend    = new RealVISABackend();
            mOwnBackend = true;
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "VISACom constructed using IVI Foundation VISA.");
    }

    VISACom::VISACom(const std::string& resourceName) : VISACom() {
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "VISACom constructed with resource name.");
        setAddress(resourceName);
        connect();
    }

    VISACom::VISACom(const std::string& resourceName, unsigned int timeoutMs, char termChar) : VISACom() {
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "VISACom constructed with resource, timeout, and termination character.");
        setAddress(resourceName);
        mTimeout         = timeoutMs;
        mTimeoutSet      = true;
        mReadTermChar    = termChar;
        mReadTermCharSet = true;
        connect();
    }

    VISACom::~VISACom() {
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "VISACom destructed.");
        disconnect();
        if (mOwnBackend && mBackend != nullptr) {
            delete mBackend;
            mBackend = nullptr;
        }
    }

    VISACom::VISACom(VISACom&& other) noexcept
        : mAddress(std::move(other.mAddress)),
          mTimeout(other.mTimeout),
          mTimeoutSet(other.mTimeoutSet),
          mReadTermChar(other.mReadTermChar),
          mReadTermCharSet(other.mReadTermCharSet),
          mWriteTermChar(other.mWriteTermChar),
          mWriteTermSet(other.mWriteTermSet),
          mRmHandle(other.mRmHandle),
          mInstHandle(other.mInstHandle),
          mBackend(other.mBackend),
          mOwnBackend(other.mOwnBackend),
          mLogLevel(other.mLogLevel),
          mAutoErrorCheck(other.mAutoErrorCheck) {
        other.mRmHandle   = VI_NULL;
        other.mInstHandle = VI_NULL;
        other.mBackend    = nullptr;
        other.mOwnBackend = false;
    }

    VISACom& VISACom::operator=(VISACom&& other) noexcept {
        if (this != &other) {
            disconnect();
            if (mOwnBackend && mBackend != nullptr) {
                delete mBackend;
            }

            mAddress         = std::move(other.mAddress);
            mTimeout         = other.mTimeout;
            mTimeoutSet      = other.mTimeoutSet;
            mReadTermChar    = other.mReadTermChar;
            mReadTermCharSet = other.mReadTermCharSet;
            mWriteTermChar   = other.mWriteTermChar;
            mWriteTermSet    = other.mWriteTermSet;
            mRmHandle        = other.mRmHandle;
            mInstHandle      = other.mInstHandle;
            mBackend         = other.mBackend;
            mOwnBackend      = other.mOwnBackend;
            mLogLevel        = other.mLogLevel;
            mAutoErrorCheck  = other.mAutoErrorCheck;

            other.mRmHandle   = VI_NULL;
            other.mInstHandle = VI_NULL;
            other.mBackend    = nullptr;
            other.mOwnBackend = false;
        }
        return *this;
    }

    // --- Manual Connection Management ---

    void VISACom::setAddress(const std::string& resourceName) {
        if (isConnected()) {
            Logger::log(mLogLevel, LogLevel::ERROR, mAddress, "Attempted to set resource while already connected.");
            throw ConnectionException("Cannot set resource while connected.");
        }
        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Setting resource to: " + resourceName);
        mAddress = resourceName;
    }

    void VISACom::connect(const std::string& resourceName) {
        setAddress(resourceName);
        connect();
    }

    void VISACom::connect() {
        if (isConnected()) {
            Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Connect called but already connected.");
            return;
        }
        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Attempting to connect using IVI Foundation VISA...");
        if (mAddress.empty()) {
            Logger::log(mLogLevel, LogLevel::ERROR, mAddress, "Connection failed: resource name is empty.");
            throw ConnectionException("Cannot connect: VISA resource name is not set.");
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Resource name: " + mAddress);

        ViStatus status = mBackend->visaOpenDefaultRM(&mRmHandle);
        if (status < VI_SUCCESS) {
            Logger::log(mLogLevel, LogLevel::ERROR, mAddress, "Failed to open VISA Default Resource Manager.");
            throw ConnectionException("Failed to open VISA Default Resource Manager.");
        }

        // Use IVI Foundation VISA types directly - ViRsrc is const char*
        // Create a const_cast wrapper to interface with the C API
        ViRsrc rsrcName = const_cast<char*>(mAddress.c_str());
        status          = mBackend->visaOpen(mRmHandle, rsrcName, VI_NULL, VI_NULL, &mInstHandle);
        if (status < VI_SUCCESS) {
            mBackend->visaClose(mRmHandle);
            mRmHandle = VI_NULL;
            Logger::log(mLogLevel, LogLevel::ERROR, mAddress, "Failed to connect to instrument: " + mAddress);
            throw ConnectionException("Failed to connect to instrument: " + mAddress);
        }

        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Successfully connected to " + mAddress);
        applyConfiguration();
    }

    void VISACom::disconnect() {
        if (!isConnected()) {
            return;
        }
        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Disconnecting from " + mAddress);
        if (mInstHandle != VI_NULL) {
            mBackend->visaClose(mInstHandle);
            mInstHandle = VI_NULL;
            Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Instrument handle closed.");
        }
        if (mRmHandle != VI_NULL) {
            mBackend->visaClose(mRmHandle);
            mRmHandle = VI_NULL;
            Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Resource manager handle closed.");
        }
        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Disconnection complete.");
    }

    bool VISACom::isConnected() const { return mInstHandle != VI_NULL; }

    std::string VISACom::getAddress() const { return mAddress; }

    unsigned int VISACom::getTimeout() const { return mTimeout; }

    // --- Core I/O Operations ---

    void VISACom::write(const std::string& command) {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot write.");
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Writing command: " + command);
        ViUInt32 returnCount = 0;
        // Use ViBuf type from IVI Foundation
        ViStatus status = mBackend->visaWrite(mInstHandle, (ViBuf)command.c_str(), static_cast<ViUInt32>(command.length()), &returnCount);
        checkStatus(status, "visaWrite");
    }

    void VISACom::writeBinary(const std::vector<uint8_t>& data) {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot write binary data.");
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Writing binary data of size: " + utils::to_string(data.size()));
        ViUInt32 returnCount = 0;
        ViStatus status      = mBackend->visaWrite(mInstHandle, (ViBuf)data.data(), static_cast<ViUInt32>(data.size()), &returnCount);
        checkStatus(status, "visaWrite (binary)");
    }

    std::string VISACom::read(size_t bufferSize) {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot read.");
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Reading data (buffer size: " + utils::to_string(bufferSize) + ")");
        std::vector<ViChar> buffer(bufferSize);
        ViUInt32            returnCount = 0;
        ViStatus            status      = mBackend->visaRead(mInstHandle, (ViPBuf)buffer.data(), static_cast<ViUInt32>(buffer.size()), &returnCount);
        checkStatus(status, "visaRead");
        std::string result(buffer.data(), returnCount);
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Read " + utils::to_string(returnCount) + " bytes: " + result);
        return result;
    }

    std::vector<uint8_t> VISACom::readBinary(size_t bufferSize) {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot read binary data.");
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Reading binary data (buffer size: " + utils::to_string(bufferSize) + ")");
        std::vector<uint8_t> buffer(bufferSize);
        ViUInt32             returnCount = 0;
        ViStatus             status      = mBackend->visaRead(mInstHandle, (ViPBuf)buffer.data(), static_cast<ViUInt32>(buffer.size()), &returnCount);
        checkStatus(status, "visaRead (binary)");
        buffer.resize(returnCount);
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Read " + utils::to_string(returnCount) + " binary bytes.");
        return buffer;
    }

    std::string VISACom::query(const std::string& command, size_t bufferSize, unsigned int delayMs) {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot query.");
        }
        write(command);
        if (delayMs > 0) {
            Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Delaying for " + utils::to_string(delayMs) + "ms before reading.");
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
        return read(bufferSize);
    }

    std::future<std::string> VISACom::queryAsync(const std::string& command, size_t bufferSize, unsigned int delayMs) {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot query asynchronously.");
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Starting asynchronous query.");
        return std::async(std::launch::async, [this, command, bufferSize, delayMs]() { return this->query(command, bufferSize, delayMs); });
    }

    bool VISACom::waitForOPC(unsigned int timeoutMs) {
        if (!isConnected()) {
            throw ConnectionException("Not connected. Cannot wait for OPC.");
        }

        unsigned int originalTimeout = mTimeout;
        if (timeoutMs > 0) {
            setTimeout(timeoutMs);
        }

        try {
            std::string response = query("*OPC?");
            if (timeoutMs > 0) {
                setTimeout(originalTimeout);
            }
            return response.find('1') != std::string::npos;
        } catch (...) {
            if (timeoutMs > 0) {
                setTimeout(originalTimeout);
            }
            throw;
        }
    }

    // --- Instrument Control & Status ---

    void VISACom::clear() {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot clear.");
        }
        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Clearing instrument interface.");
        ViStatus status = mBackend->visaClear(mInstHandle);
        checkStatus(status, "visaClear");
    }

    uint8_t VISACom::readStatusByte() {
        if (!isConnected()) {
            throw ConnectionException("Not connected to an instrument. Cannot read status byte.");
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Reading status byte.");
        ViUInt16 statusByte = 0;
        ViStatus status     = mBackend->visaReadSTB(mInstHandle, &statusByte);
        checkStatus(status, "visaReadSTB");
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Status byte received: " + utils::to_string(statusByte));
        return static_cast<uint8_t>(statusByte);
    }

    // --- Configuration ---

    void VISACom::setVerbose(LogLevel level) {
        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Changing log level.");
        mLogLevel = level;
    }

    void VISACom::enableAutoErrorCheck(bool enable) {
        Logger::log(mLogLevel, LogLevel::INFO, mAddress, "Automatic error checking " + std::string(enable ? "enabled" : "disabled") + ".");
        mAutoErrorCheck = enable;
    }

    void VISACom::setTimeout(unsigned int timeoutMs) {
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Setting timeout to " + utils::to_string(timeoutMs) + " ms.");
        mTimeout    = timeoutMs;
        mTimeoutSet = true;
        applyTimeout();
    }

    void VISACom::setReadTermination(char termChar, bool enable) {
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress,
                    "Setting read termination character to '" + std::string(1, termChar) + "' with enable=" + utils::to_string(enable));
        mReadTermChar    = termChar;
        mReadTermCharSet = enable;
        if (isConnected()) {
            if (mReadTermCharSet) {
                applyReadTermination();
            } else {
                ViStatus status = mBackend->visaSetAttribute(mInstHandle, VI_ATTR_TERMCHAR_EN, VI_FALSE);
                checkStatus(status, "visaSetAttribute (Disable VI_ATTR_TERMCHAR_EN)");
            }
        }
    }

    void VISACom::setWriteTermination(char termChar) {
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Setting write termination character to '" + std::string(1, termChar) + "'.");
        mWriteTermChar = termChar;
        mWriteTermSet  = true;
        applyWriteTermination();
    }

    // --- Static Utilities ---

    std::vector<std::string> VISACom::findResources(const std::string& query) {
        RealVISABackend backend;
        ViSession       rmSession = VI_NULL;
        ViStatus        status    = backend.visaOpenDefaultRM(&rmSession);
        if (status < VI_SUCCESS) {
            throw VisaException("Could not open VISA Default Resource Manager to find resources.");
        }

        ViFindList               findList    = 0;
        ViUInt32                 returnCount = 0;
        ViRsrc                   instrumentDescription;
        std::vector<std::string> resources;

        status = backend.visaFindRsrc(rmSession, query.c_str(), &findList, &returnCount, instrumentDescription);
        if (status < VI_SUCCESS) {
            backend.visaClose(rmSession);
            if (status == VI_ERROR_RSRC_NFOUND) {
                return {};
            }
            throw VisaException("Failed to find VISA resources.");
        }

        if (returnCount > 0) {
            resources.emplace_back(instrumentDescription);
            for (ViUInt32 i = 1; i < returnCount; ++i) {
                status = backend.visaFindNext(findList, instrumentDescription);
                if (status < VI_SUCCESS) {
                    break;
                }
                resources.emplace_back(instrumentDescription);
            }
        }

        if (findList != 0) {
            backend.visaClose(findList);
        }
        backend.visaClose(rmSession);

        return resources;
    }

    // --- Private Helpers ---

    void VISACom::applyTimeout() {
        if (!isConnected() || !mTimeoutSet) {
            return;
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Applying timeout: " + utils::to_string(mTimeout) + " ms.");
        ViStatus status = mBackend->visaSetAttribute(mInstHandle, VI_ATTR_TMO_VALUE, static_cast<ViUInt32>(mTimeout));
        checkStatus(status, "visaSetAttribute (Timeout)");
    }

    void VISACom::applyReadTermination() {
        if (!isConnected() || !mReadTermCharSet) {
            return;
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Applying read termination char '" + std::string(1, mReadTermChar) + "' with enable=true");
        ViStatus status;
        status = mBackend->visaSetAttribute(mInstHandle, VI_ATTR_TERMCHAR, static_cast<ViInt8>(mReadTermChar));
        checkStatus(status, "visaSetAttribute (VI_ATTR_TERMCHAR for Read)");
        status = mBackend->visaSetAttribute(mInstHandle, VI_ATTR_TERMCHAR_EN, VI_TRUE);
        checkStatus(status, "visaSetAttribute (VI_ATTR_TERMCHAR_EN for Read)");
    }

    void VISACom::applyWriteTermination() {
        if (!isConnected() || !mWriteTermSet) {
            return;
        }
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Applying write termination char '" + std::string(1, mWriteTermChar) + "'.");
        ViStatus status;
        status = mBackend->visaSetAttribute(mInstHandle, VI_ATTR_TERMCHAR, static_cast<ViInt8>(mWriteTermChar));
        checkStatus(status, "visaSetAttribute (VI_ATTR_TERMCHAR for Write)");
        status = mBackend->visaSetAttribute(mInstHandle, VI_ATTR_SEND_END_EN, VI_TRUE);
        checkStatus(status, "visaSetAttribute (VI_ATTR_SEND_END_EN for Write)");
    }

    void VISACom::applyConfiguration() {
        Logger::log(mLogLevel, LogLevel::DEBUG, mAddress, "Applying stored IVI Foundation VISA configurations.");
        applyTimeout();
        applyReadTermination();
        applyWriteTermination();
    }

    void VISACom::checkStatus(ViStatus status, const std::string& functionName) {
        if (status < VI_SUCCESS) {
            ViChar errorBuffer[ERROR_BUFFER_SIZE] = {0};
            mBackend->visaStatusDesc(mRmHandle, status, errorBuffer);
            std::string errorMessage = "IVI Foundation VISA Error in " + functionName + ": " + std::string(errorBuffer) + " (Status: " + utils::to_string(status) + ")";
            Logger::log(mLogLevel, LogLevel::ERROR, mAddress, errorMessage);
            if (status == VI_ERROR_TMO) {
                throw TimeoutException(errorMessage);
            }
            if (status == VI_ERROR_RSRC_NFOUND || status == VI_ERROR_RSRC_LOCKED || status == VI_ERROR_CONN_LOST) {
                throw ConnectionException(errorMessage);
            }
            if (status == VI_ERROR_INV_EXPR || status == VI_ERROR_NLISTENERS) {
                throw CommandException(errorMessage);
            }
            throw VisaException(errorMessage);
        }
    }

}    // namespace cvisa
