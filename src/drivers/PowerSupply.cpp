#include "PowerSupply.hpp"

#include <map>
#include <string>

#include "../exceptions.hpp"

namespace cvisa {
namespace drivers {

// --- High-Level Methods ---
// Refactored to use the executeCommand helper.

void PowerSupply::setVoltage(double voltage) {
    executeCommand(Commands::SET_VOLTAGE, voltage);
}

void PowerSupply::setCurrent(double current) {
    executeCommand(Commands::SET_CURRENT, current);
}

double PowerSupply::getVoltage() {
    std::string response = executeCommand(Commands::GET_VOLTAGE);
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException(
            "Failed to parse voltage from instrument response: " + response);
    }
}

double PowerSupply::getCurrent() {
    std::string response = executeCommand(Commands::GET_CURRENT);
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException(
            "Failed to parse current from instrument response: " + response);
    }
}

void PowerSupply::setOutput(bool enabled) {
    executeCommand(Commands::SET_OUTPUT, enabled ? 1 : 0);
}

bool PowerSupply::isOutputEnabled() {
    std::string response = executeCommand(Commands::GET_OUTPUT);
    // Check for "1" or "ON" for broader compatibility.
    return (response.find('1') != std::string::npos ||
            response.find("ON") != std::string::npos);
}

}  // namespace drivers
}  // namespace cvisa
