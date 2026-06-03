#ifndef CVISA_VISA_INTERFACE_HPP
#define CVISA_VISA_INTERFACE_HPP

#include "Logger.hpp"
#include "IVISABackend.hpp"

#include <cstdint>
#include <future>
#include <string>
#include <vector>

// Include IVI Foundation VISA type definitions
#include "../internal/visatype.h"

namespace cvisa {

    /**
     * @class VISACom
     * @brief A C++11 compliant RAII wrapper for IVI Foundation VISA C API.
     *
     * This class encapsulates a VISA session, providing resource management through RAII.
     * It can be constructed with a VISA resource string for immediate connection (RAII-style) 
     * or constructed empty for manual connection management.
     * 
     * The class supports:
     * - Automatic resource cleanup in destructor (RAII pattern)
     * - Move semantics for efficient resource transfer
     * - Flexible timeout and termination character configuration
     * - Automatic error checking after commands
     * - Comprehensive logging and error reporting
     * 
     * @note This class uses IVI Foundation VISA types internally, ensuring compatibility
     * with standard VISA implementations like Keysight/Agilent VISA and National Instruments VISA.
     * 
     * @see https://www.ivifoundation.org/
     */
    class VISACom {
      public:
        // Configuration
        static const size_t DEFAULT_READ_BUFFER_SIZE   = 2048;
        static const size_t DEFAULT_BINARY_BUFFER_SIZE = 4096;

      protected:
        // --- Member Variables ---
        static const size_t ERROR_BUFFER_SIZE = 256;

        std::string  mAddress;
        unsigned int mTimeout;
        bool         mTimeoutSet;
        char         mReadTermChar;
        bool         mReadTermCharSet;
        char         mWriteTermChar;
        bool         mWriteTermSet;

        // IVI Foundation VISA handles
        ViSession mRmHandle;
        ViSession mInstHandle;

        // Backend for IVI Foundation VISA C API
        IVISABackend* mBackend;
        bool          mOwnBackend;

        // Logging
        LogLevel mLogLevel;

        // Error Checking
        bool mAutoErrorCheck;

      public:
        // --- Constructors and Destructor ---
        /**
         * @brief Default constructor. Creates a disconnected interface object.
         */
        VISACom();

        /**
         * @brief Constructor with optional backend injection for testing.
         * @param backend Pointer to an IVISABackend implementation. If null, a RealVISABackend is used.
         * @param ownBackend If true, VISACom takes ownership of the backend pointer and will delete it.
         */
        explicit VISACom(IVISABackend* backend, bool ownBackend = false);

        /**
         * @brief Constructs and connects with resource name only.
         */
        explicit VISACom(const std::string& resourceName);

        /**
         * @brief Constructs and connects with timeout and read termination.
         */
        explicit VISACom(const std::string& resourceName, unsigned int timeoutMs, char termChar);

        /**
         * @brief Destructor. Disconnects from the instrument if connected.
         */
        virtual ~VISACom();

        // --- Rule of Five: Move semantics enabled, copy semantics disabled ---
        VISACom(const VISACom&)            = delete;
        VISACom& operator=(const VISACom&) = delete;

        /**
         * @brief Move constructor.
         *
         * Transfers ownership of the VISA session from another `VISACom`
         * object. The other object is left in a disconnected, but valid, state.
         *
         * @param other The object to move from.
         */
        VISACom(VISACom&& other) noexcept;

        /**
         * @brief Move assignment operator.
         *
         * Transfers ownership of the VISA session from another `VISACom`
         * object. The other object is left in a disconnected, but valid, state.
         *
         * @param other The object to move from.
         * @return A reference to this object.
         */
        VISACom& operator=(VISACom&& other) noexcept;

        // --- Configuration ---
        /**
         * @brief Sets the VISA resource name for the instrument.
         *
         * This can only be done when the interface is disconnected.
         *
         * @param resourceName The VISA resource string (e.g., "GPIB0::1::INSTR").
         * @throws ConnectionException if the interface is already connected.
         */
        virtual void setAddress(const std::string& resourceName);

        /**
         * @brief Sets the communication timeout for VISA operations.
         *
         * This value is applied to the instrument immediately if connected, or
         * during the next `connect()` call.
         *
         * @param timeoutMs The timeout in milliseconds.
         */
        virtual void setTimeout(unsigned int timeoutMs);

        /**
         * @brief Configures the character used to terminate read operations.
         *
         * This value is applied to the instrument immediately if connected, or
         * during the next `connect()` call.
         *
         * @param termChar The termination character.
         * @param enable If true, read termination is enabled; otherwise, it's
         * disabled.
         */
        virtual void setReadTermination(char termChar, bool enable = true);
        /**
         * @brief Configures the character to be appended to every write operation.
         *
         * @param termChar The termination character to append to writes.
         */
        virtual void setWriteTermination(char termChar);

        /**
         * @brief Sets the verbosity level for logging.
         * @param level The desired logging level.
         */
        virtual void setVerbose(LogLevel level);

        /**
         * @brief Enables or disables automatic instrument error checking.
         *
         * When enabled, the driver will query the instrument's error queue
         * (SYST:ERR?) after every `write` or `query` operation and throw an
         * exception if an error is reported.
         *
         * @param enable True to enable automatic error checking, false to disable.
         */
        virtual void enableAutoErrorCheck(bool enable);

        // --- Manual Connection Management ---
        /**
         * @brief Manually establishes a connection to the instrument.
         *
         * A resource name must have been set via `setAddress()` or the constructor
         * prior to calling this.
         *
         * @throws ConnectionException if no resource name is set or if connection
         * fails.
         */
        void connect();

        /**
         * @brief Sets the resource name and immediately connects.
         * @param resourceName The VISA resource string.
         * @throws ConnectionException if connection fails.
         */
        void connect(const std::string& resourceName);

        /**
         * @brief Disconnects from the instrument.
         *
         * Safe to call even if already disconnected.
         */
        void disconnect();

        /**
         * @brief Checks if the interface is currently connected to an instrument.
         * @return True if connected, false otherwise.
         */
        bool isConnected() const;

        /**
         * @brief Gets the current VISA resource name.
         * @return The resource name string.
         */
        std::string getAddress() const;

        /**
         * @brief Gets the current timeout value.
         * @return The timeout in milliseconds.
         */
        unsigned int getTimeout() const;

        // --- Core I/O Operations ---
        /**
         * @brief Writes a command string to the instrument.
         * @param command The SCPI command string to send.
         * @throws ConnectionException if the interface is not connected.
         * @throws CommandException on a VISA communication error.
         */
        virtual void write(const std::string& command);

        /**
         * @brief Writes a block of binary data to the instrument.
         *
         * This method is suitable for sending waveform data or other large binary
         * payloads. It does not append any termination characters.
         *
         * @param data A vector of bytes to send to the instrument.
         * @throws ConnectionException if the interface is not connected.
         * @throws CommandException on a VISA communication error.
         */
        virtual void writeBinary(const std::vector<uint8_t>& data);

        /**
         * @brief Reads a string-based response from the instrument.
         *
         * This operation will read up to `bufferSize` bytes or until a
         * termination character is encountered if one has been configured.
         *
         * @param bufferSize The maximum number of bytes to read.
         * @return The string response from the instrument.
         * @throws ConnectionException if the interface is not connected.
         * @throws TimeoutException if the read operation times out.
         * @throws CommandException on other VISA communication errors.
         */
        virtual std::string read(size_t bufferSize = DEFAULT_READ_BUFFER_SIZE);

        /**
         * @brief Reads a block of binary data from the instrument.
         *
         * This method is designed to read binary data, such as a captured
         * waveform. It reads up to `bufferSize` bytes. The instrument must be
         * configured to send binary data (e.g., using an appropriate `FORMAT`
         * command) before calling this.
         *
         * @param bufferSize The maximum number of bytes to read.
         * @return A vector of bytes containing the data read from the instrument.
         * @throws ConnectionException if the interface is not connected.
         * @throws TimeoutException if the read operation times out.
         * @throws CommandException on other VISA communication errors.
         */
        virtual std::vector<uint8_t> readBinary(size_t bufferSize = DEFAULT_BINARY_BUFFER_SIZE);

        /**
         * @brief Performs a query: writes a command and reads the response.
         *
         * @param command The SCPI query string to send (e.g., "*IDN_Query?").
         * @param bufferSize The maximum number of bytes to expect in the response.
         * @param delayMs An optional delay in milliseconds to wait between the
         * write and read operations.
         * @return The string response from the instrument.
         * @throws ConnectionException if the interface is not connected.
         * @throws TimeoutException if the read operation times out.
         * @throws CommandException on other VISA communication errors.
         */
        virtual std::string query(const std::string& command, size_t bufferSize = DEFAULT_READ_BUFFER_SIZE, unsigned int delayMs = 0);

        /**
         * @brief Performs a query asynchronously.
         *
         * @param command The SCPI query string to send.
         * @param bufferSize The maximum number of bytes for the response.
         * @param delayMs Optional delay between write and read.
         * @return A `std::future<std::string>` that will hold the instrument's
         * response.
         * @throws ConnectionException if the interface is not connected.
         */
        virtual std::future<std::string> queryAsync(const std::string& command, size_t bufferSize = DEFAULT_READ_BUFFER_SIZE, unsigned int delayMs = 0);

        /**
         * @brief Waits for the instrument to complete its current operation.
         *
         * Sends "*OPC?" and waits for a response.
         *
         * @param timeoutMs Optional timeout for this specific wait.
         * @return True if operation completed, false on timeout.
         */
        virtual bool waitForOPC(unsigned int timeoutMs = 0);

        // --- Instrument Control & Status ---
        /**
         * @brief Clears the communication interface of the instrument.
         *
         * This function sends a bus-specific command (e.g., GPIB Selected Device
         * Clear) to the instrument, which should abort any pending operations and
         * return the interface to a known state. This is useful for error
         * recovery.
         *
         * @throws ConnectionException if the interface is not connected.
         * @throws VisaException on a VISA communication error.
         */
        void clear();

        /**
         * @brief Reads the instrument's status byte using a serial poll.
         *
         * This performs a serial poll (or equivalent bus-specific operation) to
         * read the status byte without parsing a response message. The status
         * byte often contains summary information about the instrument's state,
         * such as whether an error is available in the queue or if an operation is
         * complete.
         *
         * @return The value of the status byte (an 8-bit integer).
         * @throws ConnectionException if the interface is not connected.
         * @throws VisaException on a VISA communication error.
         */
        uint8_t readStatusByte();

        // --- Static Utilities ---
        static std::vector<std::string> findResources(const std::string& query = "?*INSTR");

      private:
        // --- Configuration Helpers ---
        void applyTimeout();
        void applyReadTermination();
        void applyWriteTermination();

        void checkStatus(ViStatus status, const std::string& functionName);
        void applyConfiguration();
    };

}    // namespace cvisa

#endif    // CVISA_VISA_INTERFACE_HPP
