#include "PowerSupply.hpp"
#include "../exceptions.hpp" // Include for CommandException
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

// --- Constructor ---

PowerSupply::PowerSupply(VisaInterface& interface)
    : InstrumentDriver(interface) {
    // Optional: Could add an IDN check here
}


// --- High-Level Methods ---

void PowerSupply::setVoltage(double voltage) {
    m_interface.write("VOLT " + std::to_string(voltage));
}

void PowerSupply::setCurrent(double current) {
    m_interface.write("CURR " + std::to_string(current));
}

double PowerSupply::getVoltage() {
    std::string response = m_interface.query("VOLT?");
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException("Failed to parse voltage from instrument response: " + response);
    }
}

double PowerSupply::getCurrent() {
    std::string response = m_interface.query("CURR?");
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException("Failed to parse current from instrument response: " + response);
    }
}

void PowerSupply::setOutput(bool enabled) {
    m_interface.write(enabled ? "OUTP ON" : "OUTP OFF");
}

bool PowerSupply::isOutputEnabled() {
    std::string response = m_interface.query("OUTP?");
    return (response.find('1') != std::string::npos || response.find("ON") != std::string::npos);
}

} // namespace drivers
} // namespace cvisa