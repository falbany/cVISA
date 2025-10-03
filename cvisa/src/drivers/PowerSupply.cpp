#include "PowerSupply.hpp"
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

// --- Constructor ---

PowerSupply::PowerSupply(VisaInstrument& instrument)
    : InstrumentDriver(instrument) {
    // Optional: Could add an IDN check here to ensure it's a compatible instrument
}


// --- High-Level Methods ---

void PowerSupply::setVoltage(double voltage) {
    // Example SCPI command: "VOLT 5.0" or "SOURCE:VOLTAGE 5.0"
    // We use a generic version here.
    m_instrument.write("VOLT " + std::to_string(voltage));
}

void PowerSupply::setCurrent(double current) {
    // Example SCPI command: "CURR 1.5" or "SOURCE:CURRENT 1.5"
    m_instrument.write("CURR " + std::to_string(current));
}

double PowerSupply::getVoltage() {
    // Example SCPI command: "VOLT?" or "MEASURE:VOLTAGE?"
    std::string response = m_instrument.query("VOLT?");
    try {
        // Convert the string response to a double
        return std::stod(response);
    } catch (const std::invalid_argument& e) {
        throw CommandException("Failed to parse voltage from instrument response: " + response);
    }
}

double PowerSupply::getCurrent() {
    // Example SCPI command: "CURR?" or "MEASURE:CURRENT?"
    std::string response = m_instrument.query("CURR?");
    try {
        // Convert the string response to a double
        return std::stod(response);
    } catch (const std::invalid_argument& e) {
        throw CommandException("Failed to parse current from instrument response: " + response);
    }
}

void PowerSupply::setOutput(bool enabled) {
    // Example SCPI command: "OUTP ON" or "OUTP OFF"
    m_instrument.write(enabled ? "OUTP ON" : "OUTP OFF");
}

bool PowerSupply::isOutputEnabled() {
    // Example SCPI command: "OUTP?"
    std::string response = m_instrument.query("OUTP?");
    // Instruments might return "1", "ON", "0", or "OFF".
    // A robust implementation would check for all of these.
    return (response.find('1') != std::string::npos || response.find("ON") != std::string::npos);
}

} // namespace drivers
} // namespace cvisa