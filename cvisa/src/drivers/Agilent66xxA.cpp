#include "Agilent66xxA.hpp"
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

// --- Data-driven Command Definitions ---
// The command registry is now simplified, as delay is no longer a declarative property.
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
Agilent66xxA::Agilent66xxA(VisaInterface& interface)
    : InstrumentDriver(interface) {}

// --- Private Spec Lookup Helper ---
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
// The public methods now call the appropriate helper (`executeWrite` or `executeQuery`)
// from the base class, passing the delay as a parameter where needed.

void Agilent66xxA::setVoltage(double voltage) {
    executeWrite(getSpec("set_voltage"), voltage);
}

double Agilent66xxA::getVoltageSetting() {
    std::string response = executeQuery(getSpec("get_voltage_set"));
    return parse_double(response, "getVoltageSetting");
}

double Agilent66xxA::measureVoltage() {
    // Pass the required 50ms delay for an ADC measurement to the executeQuery helper.
    std::string response = executeQuery(getSpec("meas_voltage"), 50);
    return parse_double(response, "measureVoltage");
}

void Agilent66xxA::setCurrent(double current) {
    executeWrite(getSpec("set_current"), current);
}

double Agilent66xxA::getCurrentSetting() {
    std::string response = executeQuery(getSpec("get_current_set"));
    return parse_double(response, "getCurrentSetting");
}

double Agilent66xxA::measureCurrent() {
    // Pass the required 50ms delay for an ADC measurement to the executeQuery helper.
    std::string response = executeQuery(getSpec("meas_current"), 50);
    return parse_double(response, "measureCurrent");
}

void Agilent66xxA::setOutput(bool enabled) {
    executeWrite(getSpec("set_output"), enabled ? "ON" : "OFF");
}

bool Agilent66xxA::isOutputEnabled() {
    std::string response = executeQuery(getSpec("get_output_state"));
    return response.find('1') != std::string::npos;
}

} // namespace drivers
} // namespace cvisa