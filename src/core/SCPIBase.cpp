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

        std::string SCPIBase::IDN_Query() { return trim(query(SCPICommons::IDN_Query())); }

        void SCPIBase::RST() { write(SCPICommons::RST()); }

        void SCPIBase::CLS() { write(SCPICommons::CLS()); }

        void SCPIBase::WAI() { write(SCPICommons::WAI()); }

        bool SCPIBase::isOperationComplete() { return query<int>(SCPICommons::OPC_Query()) == 1; }

        int SCPIBase::runSelfTest() { return query<int>(SCPICommons::TST_Query()); }

        uint8_t SCPIBase::STB_Query() { return query<uint8_t>(SCPICommons::STB_Query()); }

        uint8_t SCPIBase::ESR_Query() { return query<uint8_t>(SCPICommons::ESR_Query()); }

        void SCPIBase::ESE_Set(uint8_t mask) { write(SCPICommons::ESE_Set(), mask); }

        uint8_t SCPIBase::ESE_Query() { return query<uint8_t>(SCPICommons::ESE_Query()); }

        void SCPIBase::SRE_Set(uint8_t mask) { write(SCPICommons::SRE_Set(), mask); }

        uint8_t SCPIBase::SRE_Query() { return query<uint8_t>(SCPICommons::SRE_Query()); }

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
