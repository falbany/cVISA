#ifndef CVISA_VISA_INTERFACE_HPP
#define CVISA_VISA_INTERFACE_HPP

#include "Logger.hpp"

#include <cstdint>
#include <future>
#include <stdexcept>
#include <string>
#include <vector>

// Forward-declare VISA types to avoid including visa.h in a public header.
using ViSession = unsigned long;
using ViStatus  = long;

namespace cvisa {

    /**
 * @class VisaInterface
 * @brief A C++11 compliant RAII wrapper for the VISA C API with flexible
 * connection management.
 *
 * This class encapsulates a VISA session. It can be constructed with a VISA
 * resource string for immediate connection (RAII-style) or constructed empty
 * for manual connection management.
 */
    class VisaInterface {
      private:
        // --- Member Variables ---
        std::string  m_resourceName;
        unsigned int m_timeout_ms;
        bool         m_timeout_ms_set;
        char         m_read_termination;
        bool         m_read_termination_set;
        char         m_write_termination;
        bool         m_write_termination_set;

        // VISA handles
        ViSession m_resourceManagerHandle;
        ViSession m_instrumentHandle;

        // Logging
        LogLevel m_logLevel;

        // Error Checking
        bool m_autoErrorCheckEnabled;

      public:
        // --- Constructors and Destructor ---
        /**
     * @brief Default constructor. Creates a disconnected interface object.
     */
        VisaInterface();

        /**
     * @brief Constructs and connects with resource name only.
     */
        explicit VisaInterface(const std::string& resourceName);

        /**
     * @brief Constructs and connects with timeout and read termination.
     */
        explicit VisaInterface(const std::string& resourceName, unsigned int timeout_ms, char read_termination);

        /**
         * @brief Destructor. Disconnects from the instrument if connected.
         */
        virtual ~VisaInterface();

        // --- Rule of Five: Move semantics enabled, copy semantics disabled ---
        VisaInterface(const VisaInterface&) = delete;
        VisaInterface& operator=(const VisaInterface&) = delete;

        /**
         * @brief Move constructor.
         *
         * Transfers ownership of the VISA session from another `VisaInterface`
         * object. The other object is left in a disconnected, but valid, state.
         *
         * @param other The object to move from.
         */
        VisaInterface(VisaInterface&& other) noexcept;

        /**
         * @brief Move assignment operator.
         *
         * Transfers ownership of the VISA session from another `VisaInterface`
         * object. The other object is left in a disconnected, but valid, state.
         *
         * @param other The object to move from.
         * @return A reference to this object.
         */
        VisaInterface& operator=(VisaInterface&& other) noexcept;

        // --- Configuration ---
        /**
         * @brief Sets the VISA resource name for the instrument.
         *
         * This can only be done when the interface is disconnected.
         *
         * @param resourceName The VISA resource string (e.g., "GPIB0::1::INSTR").
         * @throws ConnectionException if the interface is already connected.
         */
        virtual void setResource(const std::string& resourceName);

        /**
         * @brief Sets the communication timeout for VISA operations.
         *
         * This value is applied to the instrument immediately if connected, or
         * during the next `connect()` call.
         *
         * @param timeout_ms The timeout in milliseconds.
         */
        virtual void setTimeout(unsigned int timeout_ms);

        /**
         * @brief Configures the character used to terminate read operations.
         *
         * This value is applied to the instrument immediately if connected, or
         * during the next `connect()` call.
         *
         * @param term_char The termination character.
         * @param enable If true, read termination is enabled; otherwise, it's
         * disabled.
         */
        virtual void setReadTermination(char term_char, bool enable = true);
        /**
         * @brief Configures the character to be appended to every write operation.
         *
         * @param term_char The termination character to append to writes.
         */
        virtual void setWriteTermination(char term_char);

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
         * A resource name must have been set via `setResource()` or the constructor
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
        virtual std::string read(size_t bufferSize = 2048);

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
        virtual std::vector<uint8_t> readBinary(size_t bufferSize = 4096);

        /**
     * @brief Performs a query: writes a command and reads the response.
     *
     * @param command The SCPI query string to send (e.g., "*IDN?").
     * @param bufferSize The maximum number of bytes to expect in the response.
     * @param delay_ms An optional delay in milliseconds to wait between the
     * write and read operations.
     * @return The string response from the instrument.
     * @throws ConnectionException if the interface is not connected.
     * @throws TimeoutException if the read operation times out.
     * @throws CommandException on other VISA communication errors.
     */
        virtual std::string query(const std::string& command, size_t bufferSize = 2048, unsigned int delay_ms = 0);

        /**
     * @brief Performs a query asynchronously.
     *
     * @param command The SCPI query string to send.
     * @param bufferSize The maximum number of bytes for the response.
     * @param delay_ms Optional delay between write and read.
     * @return A `std::future<std::string>` that will hold the instrument's
     * response.
     * @throws ConnectionException if the interface is not connected.
     */
        virtual std::future<std::string> queryAsync(const std::string& command, size_t bufferSize = 2048, unsigned int delay_ms = 0);

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
