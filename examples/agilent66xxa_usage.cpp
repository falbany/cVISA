#include "drivers/Agilent66xxA.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    // This is a simulated example.
    // Replace "GPIB0::2::INSTR" with your instrument's actual VISA resource name.
    std::string                  resourceName = "GPIB0::2::INSTR";
    cvisa::drivers::Agilent66xxA psu;

    std::cout << "--- cvisa Agilent/Keysight 66xxA Example ---" << std::endl;
    std::cout << "Description: " << psu.getDescription() << std::endl;

    try {
        // --- Connection ---
        std::cout << "\nConnecting to " << resourceName << "..." << std::endl;
        psu.connect(resourceName);

        // --- Basic Operations ---
        std::cout << "Instrument ID: " << psu.getIdentification() << std::endl;
        psu.reset();
        std::cout << "Instrument has been reset." << std::endl;

        // --- Display Control ---
        std::cout << "\nControlling display..." << std::endl;
        psu.displayText("Hello!");
        std::cout << "Display text set to: " << psu.getDisplayText() << std::endl;
        psu.setDisplayEnabled(true);
        std::cout << "Display is " << (psu.isDisplayEnabled() ? "ON" : "OFF") << std::endl;

        // --- Protection Settings ---
        std::cout << "\nConfiguring protection..." << std::endl;
        psu.setOverVoltageProtection(6.0);
        std::cout << "OVP set to: " << psu.getOverVoltageProtection() << " V" << std::endl;
        psu.setOverCurrentProtection(true);
        std::cout << "OCP is " << (psu.isOverCurrentProtectionEnabled() ? "ON" : "OFF") << std::endl;

        // --- Output Control ---
        std::cout << "\nSetting output..." << std::endl;
        psu.setVoltage(5.0);
        psu.setCurrent(1.0);
        psu.setOutput(true);
        std::cout << "Voltage set to: " << psu.getVoltageSetting() << " V" << std::endl;
        std::cout << "Current set to: " << psu.getCurrentSetting() << " A" << std::endl;
        std::cout << "Output is " << (psu.isOutputEnabled() ? "ON" : "OFF") << std::endl;

        std::cout << "\nMeasuring output..." << std::endl;
        std::cout << "Measured voltage: " << psu.measureVoltage() << " V" << std::endl;
        std::cout << "Measured current: " << psu.measureCurrent() << " A" << std::endl;

        // --- Trigger System Example ---
        std::cout << "\nConfiguring trigger system..." << std::endl;
        psu.setTriggerSource(cvisa::drivers::Agilent66xxA::TriggerSource::BUS);
        std::cout << "Trigger source set to BUS." << std::endl;
        psu.trigger();
        std::cout << "Software trigger sent." << std::endl;

        // --- Remote Sensing ---
        // Note: Remote sensing requires specific wiring. This just checks the state.
        std::cout << "\nChecking remote sense..." << std::endl;
        std::cout << "Remote sensing is " << (psu.isRemoteSensingEnabled() ? "enabled" : "disabled") << std::endl;

        // --- Error Checking ---
        std::cout << "\nChecking for instrument errors..." << std::endl;
        std::string errors = psu.checkForErrors();
        if (errors.find("+0") != std::string::npos) {
            std::cout << "No errors found on instrument." << std::endl;
        } else {
            std::cout << "Found errors: " << errors << std::endl;
        }

        // --- Shutdown ---
        std::cout << "\nShutting down..." << std::endl;
        psu.setOutput(false);
        std::cout << "Output is " << (psu.isOutputEnabled() ? "ON" : "OFF") << std::endl;

    } catch (const cvisa::VisaException& e) {
        std::cerr << "A VISA error occurred: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    std::cout << "\nExample finished." << std::endl;

    return 0;
}
