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

        virtual ~VisaInterface();

        // --- Rule of Five: Move semantics enabled, copy semantics disabled ---
        VisaInterface(const VisaInterface&)            = delete;
        VisaInterface& operator=(const VisaInterface&) = delete;
        VisaInterface(VisaInterface&& other) noexcept;
        VisaInterface& operator=(VisaInterface&& other) noexcept;

        // --- Configuration ---
        virtual void setResource(const std::string& resourceName);
        virtual void setTimeout(unsigned int timeout_ms);
        virtual void setReadTermination(char term_char, bool enable = true);
        virtual void setWriteTermination(char term_char);
        virtual void setVerbose(LogLevel level);
        virtual void enableAutoErrorCheck(bool enable);

        // --- Manual Connection Management ---
        void connect();
        void disconnect();
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
        void checkStatus(ViStatus status, const std::string& functionName);
        void applyConfiguration();
    };

}    // namespace cvisa

#endif    // CVISA_VISA_INTERFACE_HPP
