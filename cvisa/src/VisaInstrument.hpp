#ifndef CVISA_VISA_INSTRUMENT_HPP
#define CVISA_VISA_INSTRUMENT_HPP

#include <string>
#include <vector>
#include <stdexcept>

// Forward-declare VISA types to avoid including visa.h in a public header.
// This is a good practice to minimize header dependencies.
// The actual visa.h will be included in the .cpp file.
using ViSession = unsigned long;
using ViStatus = long;

namespace cvisa {

/**
 * @class VisaInstrument
 * @brief A C++ RAII wrapper for a VISA instrument session.
 *
 * This class encapsulates a VISA session, providing an object-oriented,
 * exception-safe interface for communicating with measurement instruments.
 * It handles resource management automatically (opening and closing sessions)
 * and provides convenience methods for common SCPI commands.
 */
class VisaInstrument {
public:
    /**
     * @brief Constructs a VisaInstrument object and opens a session to the specified resource.
     * @param resourceName The VISA resource string (e.g., "TCPIP0::192.168.1.1::INSTR").
     * @throws ConnectionException if the connection fails.
     */
    explicit VisaInstrument(const std::string& resourceName);

    /**
     * @brief Destructor that automatically closes the VISA session.
     */
    ~VisaInstrument();

    // --- Rule of Five: Move semantics enabled, copy semantics disabled ---

    /**
     * @brief Deleted copy constructor.
     *
     * A VisaInstrument manages a unique hardware connection and cannot be copied.
     */
    VisaInstrument(const VisaInstrument&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    VisaInstrument& operator=(const VisaInstrument&) = delete;

    /**
     * @brief Move constructor.
     *
     * Transfers ownership of the VISA session from another object.
     * @param other The object to move from.
     */
    VisaInstrument(VisaInstrument&& other) noexcept;

    /**
     * @brief Move assignment operator.
     *
     * Transfers ownership of the VISA session from another object.
     * @param other The object to move from.
     * @return A reference to this object.
     */
    VisaInstrument& operator=(VisaInstrument&& other) noexcept;

    // --- Core I/O Operations ---

    /**
     * @brief Writes a command to the instrument.
     * @param command The string command to send (e.g., "*RST").
     * @throws CommandException on failure.
     */
    void write(const std::string& command);

    /**
     * @brief Reads a response from the instrument.
     * @param bufferSize The maximum number of bytes to read.
     * @return The response string from the instrument.
     * @throws CommandException on failure.
     */
    std::string read(size_t bufferSize = 2048);

    /**
     * @brief Performs a query by writing a command and then reading the response.
     * @param command The query command to send (e.g., "*IDN?").
     * @param bufferSize The maximum number of bytes to expect in the response.
     * @return The instrument's response string.
     * @throws CommandException on failure.
     */
    std::string query(const std::string& command, size_t bufferSize = 2048);

    // --- SCPI Convenience Methods ---

    /**
     * @brief Queries the instrument's identification string (*IDN?).
     * @param cmd The exact SCPI command string to use.
     * @return The identification string.
     */
    std::string getIdentification(const std::string& cmd = "*IDN?");

    /**
     * @brief Resets the instrument to its default settings (*RST).
     * @param cmd The exact SCPI command string to use.
     */
    void reset(const std::string& cmd = "*RST");

    /**
     * @brief Clears the instrument's status byte and error queue (*CLS).
     * @param cmd The exact SCPI command string to use.
     */
    void clearStatus(const std::string& cmd = "*CLS");

    // --- Configuration ---

    /**
     * @brief Sets the I/O timeout for the VISA session.
     * @param timeout_ms The timeout value in milliseconds.
     * @throws VisaException on failure.
     */
    void setTimeout(unsigned int timeout_ms);

private:
    /**
     * @brief Checks the status of a VISA C API call and throws an exception on error.
     * @param status The ViStatus code returned by the VISA function.
     * @param functionName A descriptive name of the function that was called.
     */
    void checkStatus(ViStatus status, const std::string& functionName);

    /**
     * @brief Helper to close the connection and release resources.
     */
    void closeConnection();

    // Opaque handles to the VISA resources.
    ViSession m_resourceManagerHandle = 0;
    ViSession m_instrumentHandle = 0;
};

} // namespace cvisa

#endif // CVISA_VISA_INSTRUMENT_HPP