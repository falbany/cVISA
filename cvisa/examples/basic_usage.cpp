#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

// Core VISA wrapper includes
#include "VisaInterface.hpp"
#include "exceptions.hpp"

// Include the specific Agilent 66xxA instrument driver
#include "drivers/Agilent66xxA.hpp"

void print_separator() {
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    try {
        // --- 1. Discover connected VISA instruments ---
        std::cout << "Finding connected VISA instruments..." << std::endl;
        const auto resources = cvisa::VisaInterface::findResources();

        if (resources.empty()) {
            std::cerr << "No VISA instruments found. Please check connections and VISA installation." << std::endl;
            return 1;
        }

        std::cout << "Found " << resources.size() << " instrument(s):" << std::endl;
        for (const auto& resource : resources) {
            std::cout << "  - " << resource << std::endl;
        }
        print_separator();

        // --- 2. Connect to the first discovered instrument ---
        const std::string resource_address = resources[0];
        std::cout << "Attempting to connect to: " << resource_address << std::endl;

        cvisa::VisaInterface interface(resource_address, 5000, '\n');
        std::cout << "Low-level VISA connection successful." << std::endl;
        print_separator();

        // --- 3. Instantiate the specific high-level driver ---
        cvisa::drivers::Agilent66xxA psu(interface);
        std::cout << "Agilent 66xxA driver initialized." << std::endl;

        std::string idn = interface.getIdentification();
        std::cout << "Instrument ID: " << idn << std::endl;
        print_separator();

        // --- 4. Use the driver's specific, high-level methods ---
        std::cout << "Configuring power supply..." << std::endl;
        psu.setVoltage(12.0);
        psu.setCurrent(1.0);

        double v_set = psu.getVoltageSetting();
        double i_set = psu.getCurrentSetting();
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "-> Voltage setting confirmed: " << v_set << " V" << std::endl;
        std::cout << "-> Current limit confirmed: " << i_set << " A" << std::endl;

        psu.setOutput(true);
        std::cout << "-> Output enabled." << std::endl;
        print_separator();

        // --- 5. Read back measured values ---
        std::cout << "Reading back measured values..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Measured Voltage: " << psu.measureVoltage() << " V" << std::endl;
        std::cout << "Measured Current: " << psu.measureCurrent() << " A" << std::endl;
        std::cout << "Is output enabled? " << (psu.isOutputEnabled() ? "Yes" : "No") << std::endl;
        print_separator();

        // --- 6. Clean up ---
        std::cout << "Disabling output." << std::endl;
        psu.setOutput(false);
        std::cout << "Is output enabled? " << (psu.isOutputEnabled() ? "Yes" : "No") << std::endl;

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