#include "InstrumentDriver.hpp"

#include "exceptions.hpp"

#include <algorithm>    // For std::find_if_not
#include <string>

namespace {
    // Helper to trim leading/trailing whitespace
    std::string trim(const std::string& s) {
        auto start = s.find_first_not_of(" \t\n\r\f\v");
        if (start == std::string::npos) return "";
        auto end = s.find_last_not_of(" \t\n\r\f\v");
        return s.substr(start, (end - start + 1));
    }
}    // namespace

namespace cvisa {
    namespace drivers {

        // --- Common SCPI Command Implementations ---

        std::string InstrumentDriver::getIdentification() { return trim(executeCommand(CommonCommands::getIdentification())); }

        void InstrumentDriver::reset() { executeCommand(CommonCommands::reset()); }

        void InstrumentDriver::clearStatus() { executeCommand(CommonCommands::clearStatus()); }

        void InstrumentDriver::waitToContinue() { executeCommand(CommonCommands::waitToContinue()); }

        bool InstrumentDriver::isOperationComplete() { return trim(executeCommand(CommonCommands::operationComplete())) == "1"; }

        int InstrumentDriver::runSelfTest() {
            std::string response = trim(executeCommand(CommonCommands::selfTest()));
            try {
                return std::stoi(response);
            } catch (const std::exception& e) {
                throw CommandException("Invalid response from self-test query: " + response);
            }
        }

        uint8_t InstrumentDriver::getStatusByte() {
            std::string response = trim(executeCommand(CommonCommands::getStatusByte()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for getStatusByte: " + response);
            }
        }

        uint8_t InstrumentDriver::getEventStatusRegister() {
            std::string response = trim(executeCommand(CommonCommands::getEventStatusRegister()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for getEventStatusRegister: " + response);
            }
        }

        void InstrumentDriver::setEventStatusEnable(uint8_t mask) { executeCommand(CommonCommands::setEventStatusEnable(), mask); }

        uint8_t InstrumentDriver::getEventStatusEnable() {
            std::string response = trim(executeCommand(CommonCommands::getEventStatusEnable()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for getEventStatusEnable: " + response);
            }
        }

        void InstrumentDriver::setServiceRequestEnable(uint8_t mask) { executeCommand(CommonCommands::setServiceRequestEnable(), mask); }

        uint8_t InstrumentDriver::getServiceRequestEnable() {
            std::string response = trim(executeCommand(CommonCommands::getServiceRequestEnable()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for getServiceRequestEnable: " + response);
            }
        }

        void InstrumentDriver::checkInstrumentError() {
            std::string response = query("SYST:ERR?");
            // SCPI standard: "+0,\"No error\"" means no error.
            // Anything else is an error. We check for the leading '+0'
            if (response.find("+0") != 0) {
                throw InstrumentException("Instrument error: " + trim(response));
            }
        }

        void InstrumentDriver::executeCommandChain(const std::vector<CommandSpec>& commands, const std::string& delimiter) {
            if (commands.empty()) {
                return;    // Nothing to do
            }

            std::string chained_command;
            for (size_t i = 0; i < commands.size(); ++i) {
                const auto& spec = commands[i];

                // Safety checks
                if (spec.type != CommandType::WRITE) {
                    throw std::logic_error("executeCommandChain only supports WRITE commands.");
                }
                if (std::string(spec.command).find('%') != std::string::npos) {
                    throw std::logic_error(
                        "executeCommandChain does not support commands with format "
                        "specifiers.");
                }

                chained_command += spec.command;
                if (i < commands.size() - 1) {
                    chained_command += delimiter;
                }
            }

            Logger::log(m_logLevel, LogLevel::INFO, m_resourceName, "Executing command chain: " + chained_command);

            write(chained_command);

            if (m_autoErrorCheckEnabled) {
                checkInstrumentError();
            }
        }

    }    // namespace drivers
}    // namespace cvisa
