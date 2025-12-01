#include "Agilent66xxA.hpp"

#include <stdexcept>
#include <string>

#include "../exceptions.hpp"

namespace cvisa {
namespace drivers {

// --- Public API ---
// All methods now use the static constexpr command definitions.

void Agilent66xxA::setVoltage(double voltage) {
    executeCommand(Commands::SET_VOLTAGE, voltage);
}

double Agilent66xxA::getVoltageSetting() {
    return queryAndParse<double>(Commands::GET_VOLTAGE_SET);
}

double Agilent66xxA::measureVoltage() {
    return queryAndParse<double>(Commands::MEAS_VOLTAGE);
}

void Agilent66xxA::setCurrent(double current) {
    executeCommand(Commands::SET_CURRENT, current);
}

double Agilent66xxA::getCurrentSetting() {
    return queryAndParse<double>(Commands::GET_CURRENT_SET);
}

double Agilent66xxA::measureCurrent() {
    return queryAndParse<double>(Commands::MEAS_CURRENT);
}

void Agilent66xxA::setOutput(bool enabled) {
    executeCommand(Commands::SET_OUTPUT, enabled ? "ON" : "OFF");
}

bool Agilent66xxA::isOutputEnabled() {
    return queryAndParse<bool>(Commands::GET_OUTPUT_STATE);
}

}  // namespace drivers
}  // namespace cvisa
