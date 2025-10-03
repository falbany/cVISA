#include "Agilent66xxA.hpp"
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

// --- Data-driven Command Definitions ---
// The command registry remains defined here, specific to this driver.
// The format specifiers are now standard C-style for snprintf.
const std::map<std::string, CommandSpec> Agilent66xxA::s_commandRegistry = {
    {"set_voltage",     {"VOLT %f",    CommandType::WRITE}},
    {"get_voltage_set", {"VOLT?",      CommandType::QUERY}},
    {"meas_voltage",    {"MEAS:VOLT?", CommandType::QUERY}},
    {"set_current",     {"CURR %f",    CommandType::WRITE}},
    {"get_current_set", {"CURR?",      CommandType::QUERY}},
    {"meas_current",    {"MEAS:CURR?", CommandType::QUERY}},
    {"set_output",      {"OUTP %s",    CommandType::WRITE}},
    {"get_output_state",{"OUTP?",      CommandType::QUERY}}
};

// --- Constructor ---
Agilent66xxA::Agilent66xxA(VisaInstrument& instrument)
    : InstrumentDriver(instrument) {}

// --- Private Spec Lookup Helper ---
// Finds the command specification in the registry. Throws if not found.
const CommandSpec& Agilent66xxA::getSpec(const std::string& commandName) const {
    auto it = s_commandRegistry.find(commandName);
    if (it == s_commandRegistry.end()) {
        throw std::invalid_argument("Command not found in registry: " + commandName);
    }
    return it->second;
}

// --- Helper for parsing string responses to double ---
namespace {
double parse_double(const std::string& response, const std::string& context) {
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException("Failed to parse double from instrument response for " + context + ". Response: " + response);
    }
}
} // namespace

// --- Refactored Public API ---
// Public methods now look up the command spec and pass it to the base class's
// executeCommand method. The logic is cleaner and avoids code duplication.

void Agilent66xxA::setVoltage(double voltage) {
    executeCommand(getSpec("set_voltage"), voltage);
}

double Agilent66xxA::getVoltageSetting() {
    std::string response = executeCommand(getSpec("get_voltage_set"));
    return parse_double(response, "getVoltageSetting");
}

double Agilent66xxA::measureVoltage() {
    std::string response = executeCommand(getSpec("meas_voltage"));
    return parse_double(response, "measureVoltage");
}

void Agilent66xxA::setCurrent(double current) {
    executeCommand(getSpec("set_current"), current);
}

double Agilent66xxA::getCurrentSetting() {
    std::string response = executeCommand(getSpec("get_current_set"));
    return parse_double(response, "getCurrentSetting");
}

double Agilent66xxA::measureCurrent() {
    std::string response = executeCommand(getSpec("meas_current"));
    return parse_double(response, "measureCurrent");
}

void Agilent66xxA::setOutput(bool enabled) {
    executeCommand(getSpec("set_output"), enabled ? "ON" : "OFF");
}

bool Agilent66xxA::isOutputEnabled() {
    std::string response = executeCommand(getSpec("get_output_state"));
    return response.find('1') != std::string::npos;
}

} // namespace drivers
} // namespace cvisa