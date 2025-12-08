#include "SCPIBase.hpp"

#include "Exceptions.hpp"

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

        std::string SCPIBase::IDN_Query() { return trim(executeCommand(SCPICommons::IDN_Query())); }

        void SCPIBase::RST() { executeCommand(SCPICommons::RST()); }

        void SCPIBase::CLS() { executeCommand(SCPICommons::CLS()); }

        void SCPIBase::WAI() { executeCommand(SCPICommons::WAI()); }

        bool SCPIBase::isOperationComplete() { return trim(executeCommand(SCPICommons::OPC_Query())) == "1"; }

        int SCPIBase::runSelfTest() {
            std::string response = trim(executeCommand(SCPICommons::TST_Query()));
            try {
                return std::stoi(response);
            } catch (const std::exception& e) {
                throw CommandException("Invalid response from self-test query: " + response);
            }
        }

        uint8_t SCPIBase::STB_Query() {
            std::string response = trim(executeCommand(SCPICommons::STB_Query()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for STB_Query: " + response);
            }
        }

        uint8_t SCPIBase::ESR_Query() {
            std::string response = trim(executeCommand(SCPICommons::ESR_Query()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for ESR_Query: " + response);
            }
        }

        void SCPIBase::ESE_Set(uint8_t mask) { executeCommand(SCPICommons::ESE_Set(), mask); }

        uint8_t SCPIBase::ESE_Query() {
            std::string response = trim(executeCommand(SCPICommons::ESE_Query()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for ESE_Query: " + response);
            }
        }

        void SCPIBase::SRE_Set(uint8_t mask) { executeCommand(SCPICommons::SRE_Set(), mask); }

        uint8_t SCPIBase::SRE_Query() {
            std::string response = trim(executeCommand(SCPICommons::SRE_Query()));
            try {
                return static_cast<uint8_t>(std::stoi(response));
            } catch (const std::exception& e) {
                throw CommandException("Invalid response for SRE_Query: " + response);
            }
        }

        void SCPIBase::readErrorQueue() {
            std::string response = query("SYST:ERR?");
            // SCPI standard: "+0,\"No error\"" means no error.
            // Anything else is an error. We check for the leading '+0'
            if (response.find("+0") != 0) {
                throw InstrumentException("Instrument error: " + trim(response));
            }
        }

        void SCPIBase::executeCommandChain(const std::vector<SCPICommand>& commands, const std::string& delimiter) {
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
                readErrorQueue();
            }
        }

    }    // namespace drivers
}    // namespace cvisa
