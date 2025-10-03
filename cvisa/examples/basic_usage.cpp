#include <iostream>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision

// Core VISA wrapper includes
#include "VisaInstrument.hpp"
#include "exceptions.hpp"

// NEW: Include the specific instrument driver
#include "drivers/PowerSupply.hpp"

void print_separator() {
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    // --- IMPORTANT ---
    // Replace this with the VISA resource string of your power supply.
    const std::string resource_address = "TCPIP0::192.168.1.10::INSTR";

    std::cout << "Attempting to connect to: " << resource_address << std::endl;

    try {
        // --- 1. Establish the low-level VISA connection ---
        // We still create the core VisaInstrument object first.
        // We'll set a 5-second timeout and a newline termination character.
        cvisa::VisaInstrument instrument(resource_address, 5000, '\n');
        std::cout << "Low-level VISA connection successful." << std::endl;
        print_separator();

        // --- 2. Instantiate the high-level driver ---
        // Pass the connected instrument object to the driver's constructor.
        // All subsequent interactions will be through the `psu` object.
        cvisa::drivers::PowerSupply psu(instrument);
        std::cout << "PowerSupply driver initialized." << std::endl;

        // The driver can still access low-level commands if needed.
        std::string idn = psu.getIdentification();
        std::cout << "Instrument ID: " << idn << std::endl;
        print_separator();

        // --- 3. Use the driver's high-level methods ---
        // This is much cleaner than writing SCPI strings manually.

        std::cout << "Configuring power supply..." << std::endl;
        psu.setVoltage(5.0);  // Set output to 5.0 Volts
        psu.setCurrent(1.5);  // Set current limit to 1.5 Amps
        std::cout << "-> Voltage set to 5.0 V" << std::endl;
        std::cout << "-> Current limit set to 1.5 A" << std::endl;

        psu.setOutput(true); // Turn the output on
        std::cout << "-> Output enabled." << std::endl;
        print_separator();

        // --- 4. Read back values from the instrument ---
        std::cout << "Reading back measured values..." << std::endl;

        // Add a small delay for the instrument to stabilize its readings
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Use `std::fixed` and `std::setprecision` for clean output formatting.
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Measured Voltage: " << psu.getVoltage() << " V" << std::endl;
        std::cout << "Measured Current: " << psu.getCurrent() << " A" << std::endl;
        std::cout << "Is output enabled? " << (psu.isOutputEnabled() ? "Yes" : "No") << std::endl;
        print_separator();

        // --- 5. Clean up ---
        std::cout << "Disabling output." << std::endl;
        psu.setOutput(false); // Turn the output off
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