#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include "IVisaIo.hpp"
#include "Command.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <cstdio>
#include <map>
#include <future>

namespace cvisa {
namespace drivers {

/**
 * @class InstrumentDriver
 * @brief An abstract base class for creating instrument-specific drivers.
 *
 * This class provides protected helper functions for command execution and a
 * public interface for common SCPI commands. It depends on the IVisaIo
 * interface, allowing it to be decoupled from the concrete communication layer.
 */
class InstrumentDriver {
public:
    // Constructor takes a reference to the abstract I/O interface.
    explicit InstrumentDriver(IVisaIo& interface)
        : m_interface(interface) {}

    virtual ~InstrumentDriver() = default;

    InstrumentDriver(const InstrumentDriver&) = delete;
    InstrumentDriver& operator=(const InstrumentDriver&) = delete;
    InstrumentDriver(InstrumentDriver&&) = delete;
    InstrumentDriver& operator=(InstrumentDriver&&) = delete;

    // --- Common SCPI Commands ---
    std::string getIdentification();
    void reset();
    void clearStatus();
    void waitToContinue();
    bool isOperationComplete();
    int runSelfTest();
    uint8_t getStatusByte();
    uint8_t getEventStatusRegister();
    void setEventStatusEnable(uint8_t mask);
    uint8_t getEventStatusEnable();
    void setServiceRequestEnable(uint8_t mask);
    uint8_t getServiceRequestEnable();

protected:
    // --- Command Registry for Common Commands ---
    static const std::map<std::string, CommandSpec> s_common_command_registry;

    /**
     * @brief Safely formats a command string using a dynamically-sized buffer.
     *
     * This function uses snprintf to determine the required buffer size, allocates
     * it, and then formats the string, preventing buffer overflows.
     *
     * @param cmd_format The C-style format string.
     * @param args The arguments to format.
     * @return The formatted command string.
     * @throws std::runtime_error if formatting fails.
     */
    template<typename... Args>
    std::string formatCommand(const char* cmd_format, Args... args) {
        // Determine required size. The size is the number of characters that would have been written,
        // not including the terminating null character.
        int size = std::snprintf(nullptr, 0, cmd_format, args...);
        if (size < 0) {
            throw std::runtime_error("Error during command formatting: snprintf failed to calculate size.");
        }

        // Create a buffer of the correct size.
        std::vector<char> buffer(size + 1); // +1 for the null terminator.

        // Format the command into the buffer.
        std::snprintf(buffer.data(), buffer.size(), cmd_format, args...);

        return std::string(buffer.data());
    }

    /**
     * @brief Executes a command with arguments, dispatching to write or query.
     *
     * This is the primary command execution helper. It formats the command
     * string and then calls the appropriate VISA I/O function based on the
     * CommandSpec's type. For WRITE commands, it returns an empty string.
     *
     * @param spec The command specification.
     * @param args The arguments to format into the command string.
     * @return The instrument's response for QUERY commands; empty for WRITEs.
     */
    template<typename... Args>
    std::string executeCommand(const CommandSpec& spec, Args... args) {
        std::string command = formatCommand(spec.command, args...);
        if (spec.type == CommandType::WRITE) {
            m_interface.write(command);
            return "";
        }
        // Pass the delay from the spec to the query function.
        return m_interface.query(command, 2048, spec.delay_ms);
    }

    /**
     * @brief Executes a command without arguments.
     *
     * @param spec The command specification.
     * @return The instrument's response for QUERY commands; empty for WRITEs.
     */
    std::string executeCommand(const CommandSpec& spec) {
        if (spec.type == CommandType::WRITE) {
            m_interface.write(spec.command);
            return "";
        }
        return m_interface.query(spec.command, 2048, spec.delay_ms);
    }

    /**
     * @brief Executes an asynchronous QUERY command with arguments.
     *
     * This helper formats a command string and calls the asynchronous query
     * function on the VISA I/O interface. It is intended for non-blocking
     * operations.
     *
     * @param spec The command specification. Must be of type QUERY.
     * @param args The arguments to format into the command string.
     * @return A std::future<std::string> that will contain the instrument's response.
     * @throws std::logic_error if called on a WRITE command.
     */
    template<typename... Args>
    std::future<std::string> executeCommandAsync(const CommandSpec& spec, Args... args) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error("executeCommandAsync can only be used with QUERY commands.");
        }
        std::string command = formatCommand(spec.command, args...);
        // Pass the delay from the spec to the async query function.
        return m_interface.queryAsync(command, 2048, spec.delay_ms);
    }

    /**
     * @brief Executes an asynchronous QUERY command without arguments.
     *
     * @param spec The command specification. Must be of type QUERY.
     * @return A std::future<std::string> that will contain the instrument's response.
     * @throws std::logic_error if called on a WRITE command.
     */
    std::future<std::string> executeCommandAsync(const CommandSpec& spec) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error("executeCommandAsync can only be used with QUERY commands.");
        }
        return m_interface.queryAsync(spec.command, 2048, spec.delay_ms);
    }

    // The driver communicates through the abstract I/O interface.
    IVisaIo& m_interface;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_INSTRUMENT_DRIVER_HPP