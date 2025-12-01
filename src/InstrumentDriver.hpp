#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include <cstdio>
#include <future>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Command.hpp"
#include "VisaInterface.hpp"

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
     * @brief Default constructor. Creates a disconnected driver.
     */
    InstrumentDriver() : VisaInterface() {}

    /**
     * @brief Constructs and connects with resource name only.
     */
    explicit InstrumentDriver(const std::string& resourceName)
        : VisaInterface(resourceName) {}

    /**
     * @brief Constructs and connects with timeout and read termination.
     */
    explicit InstrumentDriver(const std::string& resourceName,
                              unsigned int timeout_ms, char read_termination)
        : VisaInterface(resourceName, timeout_ms, read_termination) {}

    virtual ~InstrumentDriver() = default;

    // Disable copy/move operations for drivers to prevent slicing and resource
    // issues.
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
     */
    template <typename... Args>
    std::string formatCommand(const char* cmd_format, Args... args) {
        int size = std::snprintf(nullptr, 0, cmd_format, args...);
        if (size < 0) {
            throw std::runtime_error(
                "Error during command formatting: snprintf failed.");
        }
        std::vector<char> buffer(size + 1);
        std::snprintf(buffer.data(), buffer.size(), cmd_format, args...);
        return std::string(buffer.data());
    }

    /**
     * @brief Executes a command, dispatching to write or query.
     *
     * This function can be called with or without format arguments.
     */
    template <typename... Args>
    std::string executeCommand(const CommandSpec& spec, Args... args) {
        std::string command = formatCommand(spec.command, args...);
        Logger::log(m_logLevel, LogLevel::INFO,
                    "Executing command: " + command);
        if (spec.type == CommandType::WRITE) {
            write(command);
            return "";
        }
        return query(command, 2048, spec.delay_ms);
    }

    /**
     * @brief Executes an asynchronous QUERY command.
     *
     * This function can be called with or without format arguments.
     */
    template <typename... Args>
    std::future<std::string> executeCommandAsync(const CommandSpec& spec,
                                                 Args... args) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error(
                "executeCommandAsync can only be used with QUERY commands.");
        }
        std::string command = formatCommand(spec.command, args...);
        return queryAsync(command, 2048, spec.delay_ms);
    }
};

}  // namespace drivers
}  // namespace cvisa

#endif  // CVISA_INSTRUMENT_DRIVER_HPP
