#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include <cstdio>
#include <future>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "Command.hpp"
#include "VisaInterface.hpp"
#include "exceptions.hpp"

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
    InstrumentDriver(const std::string& description = "")
        : VisaInterface(), m_description(description) {}

    /**
     * @brief Constructs and connects with resource name only.
     */
    explicit InstrumentDriver(const std::string& resourceName,
                              const std::string& description = "")
        : VisaInterface(resourceName), m_description(description) {}

    /**
     * @brief Constructs and connects with timeout and read termination.
     */
    explicit InstrumentDriver(const std::string& resourceName,
                              unsigned int timeout_ms, char read_termination,
                              const std::string& description = "")
        : VisaInterface(resourceName, timeout_ms, read_termination),
          m_description(description) {}

    virtual ~InstrumentDriver() = default;

    // Disable copy/move operations for drivers to prevent slicing and resource
    // issues.
    InstrumentDriver(const InstrumentDriver&) = delete;
    InstrumentDriver& operator=(const InstrumentDriver&) = delete;
    InstrumentDriver(InstrumentDriver&&) = delete;
    InstrumentDriver& operator=(InstrumentDriver&&) = delete;

    /**
     * @brief Returns the instrument's description.
     */
    std::string getDescription() const { return m_description; }

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
    std::string m_description;  // A description of the instrument.

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
        Logger::log(m_logLevel, LogLevel::INFO, m_resourceName,
                    "Executing command: " + command);

        std::string response;
        if (spec.type == CommandType::WRITE) {
            write(command);
        } else {
            response = query(command, 2048, spec.delay_ms);
        }

        if (m_autoErrorCheckEnabled) {
            checkInstrumentError();
        }

        return response;
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

    /**
     * @brief Checks the instrument's error queue for errors.
     * @throws InstrumentException if the instrument reports an error.
     */
    void checkInstrumentError();

    /**
     * @brief Executes a query and parses the response into the specified type.
     * @tparam T The desired return type (double, int, bool, or std::string).
     */
    template <typename T, typename... Args>
    T queryAndParse(const CommandSpec& spec, Args... args) {
        std::string response = executeCommand(spec, args...);
        return parseResponse<T>(response);
    }

     private:
    // C++11 Tag Dispatching for Type-Safe Parsing
    template <typename T>
    struct type_tag {};

    template <typename T>
    T parseResponse(const std::string& response) {
        return parseResponse(type_tag<T>(), response);
    }

    std::string parseResponse(type_tag<std::string>,
                              const std::string& response) {
        return response;
    }

    double parseResponse(type_tag<double>, const std::string& response) {
        try {
            return std::stod(response);
        } catch (const std::invalid_argument& e) {
            throw CommandException(
                "Failed to parse double from instrument response: \"" +
                response + "\"");
        }
    }

    int parseResponse(type_tag<int>, const std::string& response) {
        try {
            return std::stoi(response);
        } catch (const std::invalid_argument& e) {
            throw CommandException(
                "Failed to parse int from instrument response: \"" + response +
                "\"");
        }
    }

    bool parseResponse(type_tag<bool>, const std::string& response) {
        return response.find('1') != std::string::npos ||
               response.find("ON") != std::string::npos;
    }
};

}  // namespace drivers
}  // namespace cvisa

#endif  // CVISA_INSTRUMENT_DRIVER_HPP
