#include "Agilent66xxA.hpp"
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

// --- Data-driven Command Definitions ---
// The static registry is defined here. It maps a logical name to a specific
// SCPI command string and its type (WRITE or QUERY). This separates the
// command "data" from the execution "logic".
const std::map<std::string, CommandSpec> Agilent66xxA::s_commandRegistry = {
    {"set_voltage",     {"VOLT {}",     CommandType::WRITE}},
    {"get_voltage_set", {"VOLT?",      CommandType::QUERY}},
    {"meas_voltage",    {"MEAS:VOLT?", CommandType::QUERY}},
    {"set_current",     {"CURR {}",     CommandType::WRITE}},
    {"get_current_set", {"CURR?",      CommandType::QUERY}},
    {"meas_current",    {"MEAS:CURR?", CommandType::QUERY}},
    {"set_output",      {"OUTP {}",     CommandType::WRITE}},
    {"get_output_state",{"OUTP?",      CommandType::QUERY}}
};

// --- Constructor ---
Agilent66xxA::Agilent66xxA(VisaInstrument& instrument)
    : InstrumentDriver(instrument) {}

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

// --- Private Command Execution Logic ---
// This templated helper function is the engine for our data-driven approach.
// It finds a command in the registry, formats it with arguments, and executes it.
template<typename... Args>
std::string Agilent66xxA::executeCommand(const std::string& commandName, Args... args) {
    // Find command in the static registry
    auto it = s_commandRegistry.find(commandName);
    if (it == s_commandRegistry.end()) {
        throw std::invalid_argument("Command not found in registry: " + commandName);
    }
    const auto& spec = it->second;

    // Use a C-style buffer for robust formatting
    char buffer[256];
    snprintf(buffer, sizeof(buffer), spec.command, args...);
    std::string final_command = buffer;

    // Execute the command based on its defined type
    if (spec.type == CommandType::WRITE) {
        m_instrument.write(final_command);
        return ""; // Return an empty string for write commands
    }
    if (spec.type == CommandType::QUERY) {
        return m_instrument.query(final_command);
    }

    // This part should be unreachable if the command types are correct
    throw std::logic_error("Unknown command type in registry for command: " + commandName);
}


// --- Refactored Public API ---
// The public methods are now clean, readable one-liners that delegate all
// the work to the command execution engine. This makes the driver's intent
// clear and easy to maintain.

void Agilent66xxA::setVoltage(double voltage) {
    // The format string in the registry is "VOLT {}", which snprintf understands
    // as expecting a single argument.
    executeCommand("set_voltage", voltage);
}

double Agilent66xxA::getVoltageSetting() {
    return parse_double(executeCommand("get_voltage_set"), "getVoltageSetting");
}

double Agilent66xxA::measureVoltage() {
    return parse_double(executeCommand("meas_voltage"), "measureVoltage");
}

void Agilent66xxA::setCurrent(double current) {
    executeCommand("set_current", current);
}

double Agilent66xxA::getCurrentSetting() {
    return parse_double(executeCommand("get_current_set"), "getCurrentSetting");
}

double Agilent66xxA::measureCurrent() {
    return parse_double(executeCommand("meas_current"), "measureCurrent");
}

void Agilent66xxA::setOutput(bool enabled) {
    // For boolean commands, we pass the required string "ON" or "OFF"
    executeCommand("set_output", enabled ? "ON" : "OFF");
}

bool Agilent66xxA::isOutputEnabled() {
    std::string response = executeCommand("get_output_state");
    // The 66xxA series returns "1" for ON and "0" for OFF.
    return response.find('1') != std::string::npos;
}

} // namespace drivers
} // namespace cvisa