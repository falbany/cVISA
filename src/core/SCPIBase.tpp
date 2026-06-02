#ifndef CVISA_SCPIBASE_TPP
#define CVISA_SCPIBASE_TPP

#include "SCPIBase.hpp"

namespace cvisa {
    namespace drivers {

        template <typename... Args>
        std::string SCPIBase::formatCommand(const char* cmd_format, Args... args) {
            int size = std::snprintf(nullptr, 0, cmd_format, args...);
            if (size < 0) {
                throw std::runtime_error("Error during command formatting: snprintf failed.");
            }
            std::vector<char> buffer(size + 1);
            std::snprintf(buffer.data(), buffer.size(), cmd_format, args...);
            return std::string(buffer.data());
        }

        template <typename... Args>
        std::string SCPIBase::executeCommand(const SCPICommand& spec, Args... args) {
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

        template <typename... Args>
        std::future<std::string> SCPIBase::executeCommandAsync(const SCPICommand& spec, Args... args) {
            if (spec.type != CommandType::QUERY) {
                throw std::logic_error(
                    "executeCommandAsync can only be used with QUERY "
                    "commands.");
            }
            std::string command = formatCommand(spec.command, args...);
            return queryAsync(command, 2048, spec.delay_ms);
        }

        template <typename T, typename... Args>
        T SCPIBase::queryAndParse(const SCPICommand& spec, Args... args) {
            std::string response = executeCommand(spec, args...);
            return parseResponse<T>(response);
        }

        template <typename T>
        T SCPIBase::parseResponse(const std::string& response) {
            return parseResponse(type_tag<T>(), response);
        }

    }    // namespace drivers
}    // namespace cvisa

#endif    // CVISA_SCPIBASE_TPP
