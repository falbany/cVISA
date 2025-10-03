#include "Agilent66xxA.hpp"
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

// --- Constructor ---
Agilent66xxA::Agilent66xxA(VisaInstrument& instrument)
    : InstrumentDriver(instrument) {
    // To make this driver truly robust, one might add an IDN check here.
    // For example:
    // std::string idn = m_instrument.getIdentification();
    // if (idn.find("AGILENT") == std::string::npos || idn.find("66") == std::string::npos) {
    //     throw std::runtime_error("Instrument is not a recognized Agilent 66xxA series model.");
    // }
}

// --- Helper for parsing responses ---
namespace {
double parse_double(const std::string& response, const std::string& context) {
    try {
        return std::stod(response);
    } catch (const std::invalid_argument&) {
        throw CommandException("Failed to parse double from instrument response for " + context + ". Response: " + response);
    }
}
} // namespace

// --- Voltage Controls ---
void Agilent66xxA::setVoltage(double voltage) {
    m_instrument.write("VOLT " + std::to_string(voltage));
}

double Agilent66xxA::getVoltageSetting() {
    std::string response = m_instrument.query("VOLT?");
    return parse_double(response, "getVoltageSetting");
}

double Agilent66xxA::measureVoltage() {
    std::string response = m_instrument.query("MEAS:VOLT?");
    return parse_double(response, "measureVoltage");
}

// --- Current Controls ---
void Agilent66xxA::setCurrent(double current) {
    m_instrument.write("CURR " + std::to_string(current));
}

double Agilent66xxA::getCurrentSetting() {
    std::string response = m_instrument.query("CURR?");
    return parse_double(response, "getCurrentSetting");
}

double Agilent66xxA::measureCurrent() {
    std::string response = m_instrument.query("MEAS:CURR?");
    return parse_double(response, "measureCurrent");
}

// --- Output Controls ---
void Agilent66xxA::setOutput(bool enabled) {
    m_instrument.write(enabled ? "OUTP ON" : "OUTP OFF");
}

bool Agilent66xxA::isOutputEnabled() {
    std::string response = m_instrument.query("OUTP?");
    // The 66xxA series returns "1" for ON and "0" for OFF.
    return response.find('1') != std::string::npos;
}

} // namespace drivers
} // namespace cvisa