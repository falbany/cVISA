#ifndef CVISA_VISA_INSTRUMENT_HPP
#define CVISA_VISA_INSTRUMENT_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <optional> // For optional constructor arguments
#include <cstdint>  // For uint8_t types

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
     * @brief Constructs a VisaInstrument object and opens a session.
     * @param resourceName The VISA resource string (e.g., "TCPIP0::192.168.1.1::INSTR").
     * @param timeout_ms An optional timeout value in milliseconds. If not provided,
     *                   the VISA default is used.
     * @param read_termination An optional character to set as the read termination
     *                         character. If provided, termination on this char is enabled.
     * @param write_termination An optional character to set as the write termination
     *                          character.
     * @throws ConnectionException if the connection fails.
     */
    explicit VisaInstrument(const std::string& resourceName,
                              std::optional<unsigned int> timeout_ms = std::nullopt,
                              std::optional<char> read_termination = std::nullopt,
                              std::optional<char> write_termination = std::nullopt);

    /**
     * @brief Destructor that automatically closes the VISA session.
     */
    ~VisaInstrument();

    // --- Rule of Five: Move semantics enabled, copy semantics disabled ---
    VisaInstrument(const VisaInstrument&) = delete;
    VisaInstrument& operator=(const VisaInstrument&) = delete;
    VisaInstrument(VisaInstrument&& other) noexcept;
    VisaInstrument& operator=(VisaInstrument&& other) noexcept;

    // --- Core I/O Operations ---

    void write(const std::string& command);
    std::string read(size_t bufferSize = 2048);

    /**
     * @brief Performs a query by writing a command and then reading the response.
     * @param command The query command to send (e.g., "*IDN?").
     * @param bufferSize The maximum number of bytes to expect in the response.
     * @param delay_ms An optional delay in milliseconds to wait between write and read.
     * @return The instrument's response string.
     * @throws CommandException on failure.
     */
    std::string query(const std::string& command, size_t bufferSize = 2048, unsigned int delay_ms = 0);

    // --- SCPI Convenience Methods ---

    std::string getIdentification(const std::string& cmd = "*IDN?");
    void reset(const std::string& cmd = "*RST");
    void clearStatus(const std::string& cmd = "*CLS");
    void waitToContinue(const std::string& cmd = "*WAI");
    bool isOperationComplete(const std::string& cmd = "*OPC?");
    int runSelfTest(const std::string& cmd = "*TST?");
    uint8_t getStatusByte(const std::string& cmd = "*STB?");
    uint8_t getEventStatusRegister(const std::string& cmd = "*ESR?");
    void setEventStatusEnable(uint8_t mask, const std::string& cmd_prefix = "*ESE");
    uint8_t getEventStatusEnable(const std::string& cmd = "*ESE?");
    void setServiceRequestEnable(uint8_t mask, const std::string& cmd_prefix = "*SRE");
    uint8_t getServiceRequestEnable(const std::string& cmd = "*SRE?");

    // --- Configuration ---

    void setTimeout(unsigned int timeout_ms);
    void setReadTermination(char term_char, bool enable = true);
    void setWriteTermination(char term_char);


private:
    void checkStatus(ViStatus status, const std::string& functionName);
    void closeConnection();

    ViSession m_resourceManagerHandle = 0;
    ViSession m_instrumentHandle = 0;
};

} // namespace cvisa

#endif // CVISA_VISA_INSTRUMENT_HPP

} // namespace cvisa

#endif // CVISA_VISA_INSTRUMENT_HPP