#include <iostream>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds

// Core VISA wrapper includes
#include "VisaInstrument.hpp"
#include "exceptions.hpp"

// NEW: Include the specific Agilent 66xxA instrument driver
#include "drivers/Agilent66xxA.hpp"

void print_separator() {
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    // --- IMPORTANT ---
    // Replace this with the VISA resource string of your Agilent 66xxA power supply.
    const std::string resource_address = "GPIB0::5::INSTR"; // Example for a GPIB-connected instrument

    std::cout << "Attempting to connect to Agilent 66xxA at: " << resource_address << std::endl;

    try {
        // --- 1. Establish the low-level VISA connection ---
        cvisa::VisaInstrument instrument(resource_address, 5000, '\n');
        std::cout << "Low-level VISA connection successful." << std::endl;
        print_separator();

        // --- 2. Instantiate the specific high-level driver ---
        // We now use the Agilent66xxA driver for hardware-specific control.
        cvisa::drivers::Agilent66xxA psu(instrument);
        std::cout << "Agilent 66xxA driver initialized." << std::endl;

        // Use a low-level command via the base class to get the ID
        std::string idn = instrument.getIdentification();
        std::cout << "Instrument ID: " << idn << std::endl;
        print_separator();

        // --- 3. Use the driver's specific, high-level methods ---
        std::cout << "Configuring power supply..." << std::endl;
        psu.setVoltage(12.0); // Set output to 12.0 Volts
        psu.setCurrent(1.0);  // Set current limit to 1.0 Amp

        // Query the settings to confirm they were received by the instrument
        double v_set = psu.getVoltageSetting();
        double i_set = psu.getCurrentSetting();
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "-> Voltage setting confirmed: " << v_set << " V" << std::endl;
        std::cout << "-> Current limit confirmed: " << i_set << " A" << std::endl;

        psu.setOutput(true); // Turn the output on
        std::cout << "-> Output enabled." << std::endl;
        print_separator();

        // --- 4. Read back measured values from the instrument ---
        // This demonstrates the key advantage of a specific driver:
        // distinguishing between a setting (VOLT?) and a real measurement (MEAS:VOLT?).
        std::cout << "Reading back measured values..." << std::endl;

        // Add a small delay for the instrument to stabilize its readings
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Measured Voltage: " << psu.measureVoltage() << " V" << std::endl;
        std::cout << "Measured Current: " << psu.measureCurrent() << " A" << std::endl;
        std::cout << "Is output enabled? " << (psu.isOutputEnabled() ? "Yes" : "No") << std::endl;
        print_separator();

        // --- 5. Clean up ---
        std::cout << "Disabling output." << std::endl;
        psu.setOutput(false);
        std::cout << "Is output enabled? " << (psu.isOutputEnabled() ? "Yes" : "No") << std::endl;

    } catch (const cvisa::ConnectionException& e) {
        std::cerr << "[Connection Error] " << e.what() << std::endl;
        return 1;
    } catch (const cvisa::CommandException& e) {
        std::cerr << "[Command Error] " << e.what() << std::endl;
        return 1;
    } catch (const cvisa::VisaException& e) {
        std::cerr << "[VISA Error] " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nProgram finished successfully." << std::endl;
    return 0;
}