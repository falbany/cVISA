#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

// Core cvisa includes
#include "exceptions.hpp"
#include "VisaInterface.hpp" // Needed for findResources

// Include the specific Agilent 66xxA instrument driver
#include "drivers/Agilent66xxA.hpp"

void print_separator() {
    std::cout << "----------------------------------------" << std::endl;
}

/**
 * @brief Demonstrates the simple, constructor-based (RAII) connection workflow.
 */
void run_raii_example(const std::string& resource_address) {
    std::cout << "--- Running RAII (Constructor-based) Example ---" << std::endl;
    // 1. Instantiate the driver directly with the resource string.
    // This single step creates the object and opens the VISA session.
    cvisa::drivers::Agilent66xxA psu(resource_address, 5000, '\n');
    std::cout << "Driver initialized and connection successful." << std::endl;
    print_separator();

    // 2. Use the driver's high-level methods.
    std::cout << "Instrument ID: " << psu.getIdentification() << std::endl;
    print_separator();

    // 3. Configure the power supply.
    std::cout << "Configuring power supply..." << std::endl;
    psu.setVoltage(5.0);
    psu.setCurrent(0.5);
    psu.setOutput(true);
    std::cout << "-> Voltage set to " << psu.getVoltageSetting() << " V" << std::endl;
    std::cout << "-> Current set to " << psu.getCurrentSetting() << " A" << std::endl;
    std::cout << "-> Output enabled." << std::endl;
    print_separator();

    // 4. Clean up. The destructor will automatically disconnect when `psu` goes out of scope.
    std::cout << "Disabling output." << std::endl;
    psu.setOutput(false);
    std::cout << "RAII example finished. Destructor will now disconnect." << std::endl;
}

/**
 * @brief Demonstrates the manual connection workflow for more control.
 */
void run_manual_example(const std::string& resource_address) {
    std::cout << "\n--- Running Manual Connection Example ---" << std::endl;
    // 1. Create a disconnected driver instance using the default constructor.
    cvisa::drivers::Agilent66xxA psu;
    std::cout << "Driver created in a disconnected state." << std::endl;

    // 2. Set the resource and configuration, then connect manually.
    psu.setRessource(resource_address);
    psu.setTimeout(5000);
    psu.setReadTermination('\n');
    std::cout << "Resource set to: " << resource_address << std::endl;

    std::cout << "Attempting to connect manually..." << std::endl;
    psu.connect();
    std::cout << "Manual connection successful: " << std::boolalpha << psu.isConnected() << std::endl;
    print_separator();

    // 3. Use the driver's high-level methods.
    std::cout << "Instrument ID: " << psu.getIdentification() << std::endl;
    psu.setOutput(true);
    std::cout << "Output enabled." << std::endl;
    print_separator();

    // 4. Manually disconnect from the instrument.
    std::cout << "Attempting to disconnect manually..." << std::endl;
    psu.disconnect();
    std::cout << "Manual disconnection successful: " << std::boolalpha << !psu.isConnected() << std::endl;
    std::cout << "Manual example finished." << std::endl;
}

int main() {
    try {
        // --- Discover connected VISA instruments ---
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

        const std::string resource_address = resources[0];

        // Run the two different examples to demonstrate both workflows
        run_raii_example(resource_address);
        run_manual_example(resource_address);

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