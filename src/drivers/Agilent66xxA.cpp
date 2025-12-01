#include "Agilent66xxA.hpp"

#include <stdexcept>
#include <string>

#include "../exceptions.hpp"

namespace cvisa {
namespace drivers {

// --- Helper for parsing string responses to double ---
namespace {
double parse_double(const std::string& response, const std::string& context) {
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException(
            "Failed to parse double from instrument response for " + context +
            ". Response: " + response);
    }
}
}  // namespace

// --- Public API ---
// All methods now use the static constexpr command definitions.

void Agilent66xxA::setVoltage(double voltage) {
    executeCommand(Commands::SET_VOLTAGE, voltage);
}

double Agilent66xxA::getVoltageSetting() {
    std::string response = executeCommand(Commands::GET_VOLTAGE_SET);
    return parse_double(response, "getVoltageSetting");
}

double Agilent66xxA::measureVoltage() {
    std::string response = executeCommand(Commands::MEAS_VOLTAGE);
    return parse_double(response, "measureVoltage");
}

void Agilent66xxA::setCurrent(double current) {
    executeCommand(Commands::SET_CURRENT, current);
}

double Agilent66xxA::getCurrentSetting() {
    std::string response = executeCommand(Commands::GET_CURRENT_SET);
    return parse_double(response, "getCurrentSetting");
}

double Agilent66xxA::measureCurrent() {
    std::string response = executeCommand(Commands::MEAS_CURRENT);
    return parse_double(response, "measureCurrent");
}

void Agilent66xxA::setOutput(bool enabled) {
    executeCommand(Commands::SET_OUTPUT, enabled ? "ON" : "OFF");
}

bool Agilent66xxA::isOutputEnabled() {
    std::string response = executeCommand(Commands::GET_OUTPUT_STATE);
    return response.find('1') != std::string::npos;
}

}  // namespace drivers
}  // namespace cvisa
