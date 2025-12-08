#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include "SCPICommand.hpp"
#include "VISACom.hpp"
#include "Exceptions.hpp"
#include <type_traits>

#include <cstdio>
#include <future>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace cvisa {
    namespace drivers {

        /**
         * @class SCPIBase
         * @brief An abstract base class for creating instrument-specific drivers.
         *
         * This class inherits from `VISACom` to combine low-level VISA I/O
         * capabilities with a high-level command execution engine. It is designed to be
         * the foundation for all specific instrument drivers.
         *
         * Key features provided by this class include:
         * - A powerful, data-driven command execution engine (`executeCommand`,
         *   `queryAndParse`).
         * - Automatic response parsing into C++ types (`double`, `int`, `bool`,
         * `std::string`).
         * - Implementations for common SCPI commands (e.g., `*IDN_Query?`, `*RST`).
         * - An optional automatic instrument error-checking mechanism.
         * - Asynchronous query support using `std::future`.
         *
         * To create a new driver, inherit from this class and define the instrument's
         * specific command set in a nested `Commands` struct.
         */
        class SCPIBase : public VISACom {
          public:
            /**
             * @brief Default constructor. Creates a disconnected driver with a default description.
             */
            SCPIBase() : VISACom(), m_description("Undefined Instrument Driver Name") {}

            /**
             * @brief Constructs and connects with resource name only.
             * @param resourceName The VISA resource string (e.g., "GPIB0::1::INSTR").
             * @param description A human-readable description of the instrument.
             */
            explicit SCPIBase(const std::string& resourceName) : VISACom(resourceName), m_description("Undefined Instrument Driver Name") {}

            /**
             * @brief Constructs and connects with timeout and read termination.
             * @param resourceName The VISA resource string.
             * @param timeout_ms VISA communication timeout in milliseconds.
             * @param read_termination The character used to terminate read operations.
             * @param description A human-readable description of the instrument.
             */
            explicit SCPIBase(const std::string& resourceName, unsigned int timeout_ms, char read_termination)
                : VISACom(resourceName, timeout_ms, read_termination), m_description("Undefined Instrument Driver Name") {}

            virtual ~SCPIBase() = default;

            // Disable copy/move operations for drivers to prevent slicing and resource
            // issues.
            SCPIBase(const SCPIBase&)            = delete;
            SCPIBase& operator=(const SCPIBase&) = delete;
            SCPIBase(SCPIBase&&)                 = delete;
            SCPIBase& operator=(SCPIBase&&)      = delete;

            /**
             * @brief Set the instrument's description.
             * @param description A human-readable description of the instrument.
             */
            void setDescription(const std::string& description) { m_description = description; }

            /**
             * @brief Returns the instrument's description.
             * @return A std::string containing the description.
             */
            std::string getDescription() const { return m_description; }

            // --- Common SCPI Commands ---
            /**
             * @brief Queries the instrument's identification string (*IDN_Query?).
             * @return The identification string.
             */
            std::string IDN_Query();

            /**
             * @brief Resets the instrument to its factory default state (*RST).
             */
            void RST();

            /**
             * @brief Clears the instrument's status registers (*CLS).
             */
            void CLS();

            /**
             * @brief Blocks until all pending operations are complete (*WAI).
             */
            void WAI();

            /**
             * @brief Queries if the operation is complete (*OPC?).
             * @return True if the operation is complete, false otherwise.
             */
            bool isOperationComplete();

            /**
             * @brief Runs the instrument's self-test routine (*TST?).
             * @return An integer representing the self-test result (0 typically means
             * success).
             */
            int runSelfTest();

            /**
             * @brief Queries the instrument's status byte (*STB?).
             * @return The status byte as a `uint8_t`.
             */
            uint8_t STB_Query();

            /**
             * @brief Queries the event status register (*ESR?).
             * @return The event status register as a `uint8_t`.
             */
            uint8_t ESR_Query();

            /**
             * @brief Sets the event status enable register (*ESE).
             * @param mask The bitmask to set.
             */
            void ESE_Set(uint8_t mask);

            /**
             * @brief Queries the event status enable register (*ESE?).
             * @return The event status enable register as a `uint8_t`.
             */
            uint8_t ESE_Query();

            /**
             * @brief Sets the service request enable register (*SRE).
             * @param mask The bitmask to set.
             */
            void SRE_Set(uint8_t mask);

            /**
             * @brief Queries the service request enable register (*SRE?).
             * @return The service request enable register as a `uint8_t`.
             */
            uint8_t SRE_Query();

            /**
             * @brief Executes a chain of commands as a single string.
             *
             * This method is for chaining `WRITE` commands that do not require
             * arguments. The commands are concatenated with a delimiter and sent as a
             * single write. It will throw an exception if any command is a `QUERY` or
             * contains format specifiers.
             *
             * @param commands A vector of `SCPICommand` objects to chain.
             * @param delimiter The delimiter to use between commands (default: ";").
             */
            void executeCommandChain(const std::vector<SCPICommand>& commands, const std::string& delimiter = ";");

          protected:
            std::string m_description;    // A description of the instrument.

            /**
             * @brief Safely formats a command string with variadic arguments.
             * @tparam Args The types of the format arguments.
             * @param cmd_format The command string template (e.g., "VOLT %f").
             * @param args The arguments to format into the command string.
             * @return The formatted command string.
             */
            template <typename... Args>
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
             * @brief Executes a command, dispatching to `write` or `query`.
             *
             * This is the core command execution engine. It formats the command, sends
             * it to the instrument, and retrieves a response for queries.
             *
             * @tparam Args The types of the format arguments.
             * @param spec The `SCPICommand` object defining the command.
             * @param args The arguments to format into the command string.
             * @return The instrument's string response for `QUERY` commands, or an
             * empty string for `WRITE` commands.
             */
            template <typename... Args>
            std::string executeCommand(const SCPICommand& spec, Args... args) {
                std::string command = formatCommand(spec.command, args...);
                Logger::log(m_logLevel, LogLevel::INFO, m_resourceName, "Executing command: " + command);

                std::string response;
                if (spec.type == CommandType::WRITE) {
                    write(command);
                } else {
                    response = query(command, 2048, spec.delay_ms);
                }

                if (m_autoErrorCheckEnabled) {
                    readErrorQueue();
                }

                return response;
            }

            /**
             * @brief Executes an asynchronous `QUERY` command.
             * @tparam Args The types of the format arguments.
             * @param spec The `SCPICommand` for the `QUERY` command.
             * @param args The arguments to format into the command string.
             * @return A `std::future<std::string>` that will contain the instrument's
             * response.
             */
            template <typename... Args>
            std::future<std::string> executeCommandAsync(const SCPICommand& spec, Args... args) {
                if (spec.type != CommandType::QUERY) {
                    throw std::logic_error(
                        "executeCommandAsync can only be used with QUERY "
                        "commands.");
                }
                std::string command = formatCommand(spec.command, args...);
                return queryAsync(command, 2048, spec.delay_ms);
            }

            /**
             * @brief Checks the instrument's error queue for errors (SYST:ERR?).
             * @throws InstrumentException if the instrument reports an error.
             */
            void readErrorQueue();

            /**
             * @brief Executes a query and parses the response into the specified type.
             *
             * This is a high-level helper that combines `executeCommand` with automatic
             * type parsing.
             *
             * @tparam T The desired return type (`double`, `int`, `bool`, or
             * `std::string`).
             * @tparam Args The types of the format arguments.
             * @param spec The `SCPICommand` for the `QUERY` command.
             * @param args The arguments to format into the command string.
             * @return The parsed response value.
             */
            template <typename T, typename... Args>
            T queryAndParse(const SCPICommand& spec, Args... args) {
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

            std::string parseResponse(type_tag<std::string>, const std::string& response) { return response; }

            double parseResponse(type_tag<double>, const std::string& response) {
                try {
                    return std::stod(response);
                } catch (const std::invalid_argument& e) {
                    throw CommandException("Failed to parse double from instrument response: \"" + response + "\"");
                }
            }

            int parseResponse(type_tag<int>, const std::string& response) {
                try {
                    return std::stoi(response);
                } catch (const std::invalid_argument& e) {
                    throw CommandException("Failed to parse int from instrument response: \"" + response + "\"");
                }
            }

            bool parseResponse(type_tag<bool>, const std::string& response) {
                return response.find('1') != std::string::npos || response.find("ON") != std::string::npos;
            }
        };

    }    // namespace drivers
}    // namespace cvisa

#endif    // CVISA_INSTRUMENT_DRIVER_HPP
