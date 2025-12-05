#include "Agilent66xxA.hpp"

#include "../core/exceptions.hpp"

#include <stdexcept>
#include <string>

namespace cvisa {
    namespace drivers {

        // --- Output Subsystem ---
        void Agilent66xxA::setVoltage(double voltage) { executeCommand(Commands::SET_VOLTAGE(), voltage); }

        double Agilent66xxA::getVoltageSetting() { return queryAndParse<double>(Commands::GET_VOLTAGE_SET()); }

        double Agilent66xxA::measureVoltage() { return queryAndParse<double>(Commands::MEAS_VOLTAGE()); }

        void Agilent66xxA::setCurrent(double current) { executeCommand(Commands::SET_CURRENT(), current); }

        double Agilent66xxA::getCurrentSetting() { return queryAndParse<double>(Commands::GET_CURRENT_SET()); }

        double Agilent66xxA::measureCurrent() { return queryAndParse<double>(Commands::MEAS_CURRENT()); }

        void Agilent66xxA::setOutput(bool enabled) { executeCommand(Commands::SET_OUTPUT(), enabled ? "ON" : "OFF"); }

        bool Agilent66xxA::isOutputEnabled() { return queryAndParse<bool>(Commands::GET_OUTPUT_STATE()); }

        void Agilent66xxA::clearProtection() { executeCommand(Commands::CLEAR_PROTECTION()); }

        // --- Over-Voltage Protection ---
        void Agilent66xxA::setOverVoltageProtection(double level) { executeCommand(Commands::SET_OVP(), level); }

        double Agilent66xxA::getOverVoltageProtection() { return queryAndParse<double>(Commands::GET_OVP()); }

        // --- Over-Current Protection ---
        void Agilent66xxA::setOverCurrentProtection(bool enabled) { executeCommand(Commands::SET_OCP(), enabled ? "ON" : "OFF"); }

        bool Agilent66xxA::isOverCurrentProtectionEnabled() { return queryAndParse<bool>(Commands::GET_OCP()); }

        // --- Display Subsystem ---
        void Agilent66xxA::setDisplayEnabled(bool enabled) { executeCommand(Commands::SET_DISPLAY_ENABLED(), enabled ? "ON" : "OFF"); }

        bool Agilent66xxA::isDisplayEnabled() { return queryAndParse<bool>(Commands::GET_DISPLAY_ENABLED()); }

        void Agilent66xxA::displayText(const std::string& text) { executeCommand(Commands::DISPLAY_TEXT(), text.c_str()); }

        std::string Agilent66xxA::getDisplayText() { return queryAndParse<std::string>(Commands::GET_DISPLAY_TEXT()); }

        // --- Trigger Subsystem ---
        void Agilent66xxA::initiate() { executeCommand(Commands::INITIATE()); }

        void Agilent66xxA::abort() { executeCommand(Commands::ABORT()); }

        void Agilent66xxA::setTriggerSourceBus() { executeCommand(Commands::SET_TRIGGER_SOURCE_BUS()); }

        void Agilent66xxA::trigger() { executeCommand(Commands::TRIGGER()); }

        void Agilent66xxA::setTriggeredVoltage(double voltage) { executeCommand(Commands::SET_TRIGGERED_VOLTAGE(), voltage); }

        double Agilent66xxA::getTriggeredVoltage() { return queryAndParse<double>(Commands::GET_TRIGGERED_VOLTAGE()); }

        void Agilent66xxA::setTriggeredCurrent(double current) { executeCommand(Commands::SET_TRIGGERED_CURRENT(), current); }

        double Agilent66xxA::getTriggeredCurrent() { return queryAndParse<double>(Commands::GET_TRIGGERED_CURRENT()); }

    }    // namespace drivers
}    // namespace cvisa
