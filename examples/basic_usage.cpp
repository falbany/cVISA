#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>  // Required for std::stringstream
#include <string>
#include <thread>
#include <vector>

// Core cvisa includes
#include "VisaInterface.hpp"  // Needed for findResources and logging
#include "drivers/Agilent66xxA.hpp"
#include "exceptions.hpp"

void print_separator() {
    std::cout << "----------------------------------------" << std::endl;
}

/**
 * @brief Demonstrates the simple, constructor-based (RAII) connection
 * workflow.
 */
void run_raii_example(const std::string& resource_address) {
    std::cout << "--- Running RAII (Constructor-based) Example ---"
              << std::endl;
    // 1. Instantiate the driver directly with the resource string.
    // This single step creates the object and opens the VISA session.
    // The default log level is WARNING.
    cvisa::drivers::Agilent66xxA psu(resource_address, 5000, '\n');

    // --- Demonstrate Logging ---
    // Set the verbosity to DEBUG to see detailed logs for all subsequent
    // operations on this specific instance.
    psu.setVerbose(cvisa::LogLevel::DEBUG);
    std::cout << "\nLog level for this instance set to DEBUG.\n" << std::endl;

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
    std::cout << "-> Voltage set to " << psu.getVoltageSetting() << " V"
              << std::endl;
    std::cout << "-> Current set to " << psu.getCurrentSetting() << " A"
              << std::endl;
    std::cout << "-> Output enabled." << std::endl;
    print_separator();

    // 4. Clean up. The destructor will automatically disconnect when `psu` goes
    // out of scope.
    std::cout << "Disabling output." << std::endl;
    psu.setOutput(false);
    std::cout << "RAII example finished. Destructor will now disconnect."
              << std::endl;
}

/**
 * @brief Demonstrates the manual connection workflow for more control.
 */
void run_manual_example(const std::string& resource_address) {
    std::cout << "\n--- Running Manual Connection Example ---" << std::endl;
    // 1. Create a disconnected driver instance.
    cvisa::drivers::Agilent66xxA psu;
    std::cout << "Driver created in a disconnected state." << std::endl;

    // --- Demonstrate Logging ---
    // Set a different verbosity for this instance.
    psu.setVerbose(cvisa::LogLevel::INFO);
    std::cout << "\nLog level for this instance set to INFO.\n" << std::endl;

    // 2. Set the resource and configuration, then connect manually.
    psu.setResource(resource_address);
    psu.setTimeout(5000);
    psu.setReadTermination('\n');
    std::cout << "Resource set to: " << resource_address << std::endl;

    std::cout << "Attempting to connect manually..." << std::endl;
    psu.connect();
    std::cout << "Manual connection successful: " << std::boolalpha
              << psu.isConnected() << std::endl;
    print_separator();

    // 3. Use the driver's high-level methods.
    std::cout << "Instrument ID: " << psu.getIdentification() << std::endl;
    psu.setOutput(true);
    std::cout << "Output enabled." << std::endl;
    print_separator();

    // 4. Manually disconnect from the instrument.
    std::cout << "Attempting to disconnect manually..." << std::endl;
    psu.disconnect();
    std::cout << "Manual disconnection successful: " << std::boolalpha
              << !psu.isConnected() << std::endl;
    std::cout << "Manual example finished." << std::endl;
}

int main() {
    // --- Demonstrate logging to a string stream ---
    std::stringstream log_stream;
    cvisa::Logger::setOutputStream(&log_stream);
    std::cout << "Log output has been redirected to an in-memory string stream."
              << std::endl;
    print_separator();

    try {
        // --- Discover connected VISA instruments ---
        std::cout << "Finding connected VISA instruments..." << std::endl;
        const auto resources = cvisa::VisaInterface::findResources();

        if (resources.empty()) {
            std::cerr << "No VISA instruments found. Please check connections "
                         "and VISA installation."
                      << std::endl;
            // Restore default logger before exiting
            cvisa::Logger::setOutputStream(&std::cerr);
            return 1;
        }

        std::cout << "Found " << resources.size()
                  << " instrument(s):" << std::endl;
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
        // Restore default logger before exiting
        cvisa::Logger::setOutputStream(&std::cerr);
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        // Restore default logger before exiting
        cvisa::Logger::setOutputStream(&std::cerr);
        return 1;
    }

    // --- Print captured logs ---
    print_separator();
    std::cout << "--- Captured Logs ---" << std::endl;
    std::cout << log_stream.str();
    std::cout << "---------------------" << std::endl;

    // Restore the default logger
    cvisa::Logger::setOutputStream(&std::cerr);

    std::cout << "\nProgram finished successfully." << std::endl;
    return 0;
}