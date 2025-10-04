#include "PowerSupply.hpp"
#include "../exceptions.hpp"
#include <map>
#include <string>

namespace cvisa {
namespace drivers {

// Define the command set as data, following the declarative pattern.
const std::map<std::string, CommandSpec> PowerSupply::s_commandRegistry = {
    {"set_voltage", {"VOLT %f", CommandType::WRITE}},
    {"set_current", {"CURR %f", CommandType::WRITE}},
    {"get_voltage", {"VOLT?", CommandType::QUERY}},
    {"get_current", {"CURR?", CommandType::QUERY}},
    {"set_output",  {"OUTP %d", CommandType::WRITE}}, // Use %d for 0 or 1
    {"get_output",  {"OUTP?", CommandType::QUERY}}
};

// Helper to look up a command spec from the registry.
const CommandSpec& PowerSupply::getSpec(const std::string& commandName) const {
    auto it = s_commandRegistry.find(commandName);
    if (it == s_commandRegistry.end()) {
        throw std::invalid_argument("Command not found in PowerSupply registry: " + commandName);
    }
    return it->second;
}

// --- High-Level Methods ---
// Refactored to use the executeCommand helper.

void PowerSupply::setVoltage(double voltage) {
    executeCommand(getSpec("set_voltage"), voltage);
}

void PowerSupply::setCurrent(double current) {
    executeCommand(getSpec("set_current"), current);
}

double PowerSupply::getVoltage() {
    std::string response = executeCommand(getSpec("get_voltage"));
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException("Failed to parse voltage from instrument response: " + response);
    }
}

double PowerSupply::getCurrent() {
    std::string response = executeCommand(getSpec("get_current"));
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException("Failed to parse current from instrument response: " + response);
    }
}

void PowerSupply::setOutput(bool enabled) {
    executeCommand(getSpec("set_output"), enabled ? 1 : 0);
}

bool PowerSupply::isOutputEnabled() {
    std::string response = executeCommand(getSpec("get_output"));
    // Check for "1" or "ON" for broader compatibility.
    return (response.find('1') != std::string::npos || response.find("ON") != std::string::npos);
}

} // namespace drivers
} // namespace cvisa