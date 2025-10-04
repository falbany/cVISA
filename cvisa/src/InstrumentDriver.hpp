#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include "VisaInterface.hpp"
#include "Command.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <cstdio>
#include <map>
#include <future>
#include <optional>

namespace cvisa {
namespace drivers {

/**
 * @class InstrumentDriver
 * @brief An abstract base class for creating instrument-specific drivers.
 *
 * This class inherits from VisaInterface, combining the low-level I/O
 * capabilities with a high-level command execution engine.
 */
class InstrumentDriver : public VisaInterface {
public:
    /**
     * @brief Constructs the InstrumentDriver.
     * @param resourceName If provided, the constructor will connect to the instrument.
     *                     If omitted, the object is created disconnected.
     * @param timeout_ms Optional timeout in milliseconds.
     * @param read_termination Optional read termination character.
     * @param write_termination Optional write termination character.
     */
    explicit InstrumentDriver(std::optional<std::string> resourceName = std::nullopt,
                              std::optional<unsigned int> timeout_ms = std::nullopt,
                              std::optional<char> read_termination = std::nullopt,
                              std::optional<char> write_termination = std::nullopt)
        : VisaInterface(resourceName, timeout_ms, read_termination, write_termination) {}

    virtual ~InstrumentDriver() = default;

    // Disable copy/move operations for drivers to prevent slicing and resource issues.
    InstrumentDriver(const InstrumentDriver&) = delete;
    InstrumentDriver& operator=(const InstrumentDriver&) = delete;
    InstrumentDriver(InstrumentDriver&&) = delete;
    InstrumentDriver& operator=(InstrumentDriver&&) = delete;

    // --- Common SCPI Commands ---
    // These methods are implemented in InstrumentDriver.cpp
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
     */
    template<typename... Args>
    std::string formatCommand(const char* cmd_format, Args... args) {
        int size = std::snprintf(nullptr, 0, cmd_format, args...);
        if (size < 0) {
            throw std::runtime_error("Error during command formatting: snprintf failed.");
        }
        std::vector<char> buffer(size + 1);
        std::snprintf(buffer.data(), buffer.size(), cmd_format, args...);
        return std::string(buffer.data());
    }

    /**
     * @brief Executes a command with arguments, dispatching to write or query.
     */
    template<typename... Args>
    std::string executeCommand(const CommandSpec& spec, Args... args) {
        std::string command = formatCommand(spec.command, args...);
        if (spec.type == CommandType::WRITE) {
            write(command);
            return "";
        }
        return query(command, 2048, spec.delay_ms);
    }

    /**
     * @brief Executes a command without arguments.
     */
    std::string executeCommand(const CommandSpec& spec) {
        if (spec.type == CommandType::WRITE) {
            write(spec.command);
            return "";
        }
        return query(spec.command, 2048, spec.delay_ms);
    }

    /**
     * @brief Executes an asynchronous QUERY command with arguments.
     */
    template<typename... Args>
    std::future<std::string> executeCommandAsync(const CommandSpec& spec, Args... args) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error("executeCommandAsync can only be used with QUERY commands.");
        }
        std::string command = formatCommand(spec.command, args...);
        return queryAsync(command, 2048, spec.delay_ms);
    }

    /**
     * @brief Executes an asynchronous QUERY command without arguments.
     */
    std::future<std::string> executeCommandAsync(const CommandSpec& spec) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error("executeCommandAsync can only be used with QUERY commands.");
        }
        return queryAsync(spec.command, 2048, spec.delay_ms);
    }
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_INSTRUMENT_DRIVER_HPP