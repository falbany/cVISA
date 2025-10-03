#include <iostream>
#include <string>
#include <optional>

// Include the header directly. The include path is set by CMake's
// target_include_directories, so we don't need "src/".
#include "VisaInstrument.hpp"
#include "exceptions.hpp"

void print_separator() {
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    // --- IMPORTANT ---
    // Replace this with the actual VISA resource string of your instrument.
    // Examples:
    // - TCPIP Socket: "TCPIP0::192.168.1.10::5025::SOCKET"
    // - VXI-11 (LXI): "TCPIP0::192.168.1.10::INSTR"
    // - USB: "USB0::0x1234::0x5678::SERIAL123::INSTR"
    // - GPIB: "GPIB0::10::INSTR"
    const std::string resource_address = "TCPIP0::192.168.1.10::INSTR";

    std::cout << "Attempting to connect to: " << resource_address << std::endl;

    try {
        // --- 1. Demonstrate the new constructor ---
        // Create the VisaInstrument object, providing a 5-second timeout and
        // setting the newline character ('\n') as the read termination character.
        // The constructor now handles setting these attributes.
        cvisa::VisaInstrument instrument(resource_address, 5000, '\n');
        std::cout << "Connection successful. Timeout and read termination set in constructor." << std::endl;
        print_separator();

        // --- 2. Use a standard convenience method ---
        std::string idn = instrument.getIdentification();
        std::cout << "Instrument Identification: " << idn << std::endl;
        print_separator();

        // --- 3. Demonstrate new SCPI convenience methods ---
        instrument.reset(); // Send *RST
        std::cout << "Instrument reset." << std::endl;

        // Check if the operation is complete. Useful after long operations.
        if (instrument.isOperationComplete()) {
            std::cout << "Operation complete check (*OPC?): Passed" << std::endl;
        } else {
            std::cout << "Operation complete check (*OPC?): Failed" << std::endl;
        }

        // Run a self-test and check the result.
        int test_result = instrument.runSelfTest();
        std::cout << "Self-test result (*TST?): " << test_result << (test_result == 0 ? " (Passed)" : " (Failed)") << std::endl;

        instrument.clearStatus(); // Send *CLS
        std::cout << "Instrument status cleared." << std::endl;

        // Get the status byte.
        uint8_t stb = instrument.getStatusByte();
        std::cout << "Status Byte (*STB?): " << static_cast<int>(stb) << std::endl;
        print_separator();

        // --- 4. Demonstrate query with a delay ---
        // Some instruments need a moment to process a command before responding.
        // Here, we wait 100ms between writing the command and reading the response.
        std::cout << "Performing query with 100ms delay..." << std::endl;
        std::string esr_value = instrument.query("*ESR?", 256, 100);
        std::cout << "Event Status Register (*ESR?) value: " << esr_value << std::endl;
        print_separator();


    } catch (const cvisa::ConnectionException& e) {
        std::cerr << "[Connection Error] Failed to connect to the instrument." << std::endl;
        std::cerr << "Details: " << e.what() << std::endl;
        std::cerr << "Please check the following:\n"
                  << "1. The instrument is powered on and connected to the network/USB.\n"
                  << "2. The VISA resource address is correct.\n"
                  << "3. A VISA driver (e.g., NI-VISA, Keysight VISA) is installed.\n"
                  << "4. No other application is locking the resource." << std::endl;
        return 1;
    } catch (const cvisa::CommandException& e) {
        std::cerr << "[Command Error] An error occurred while communicating." << std::endl;
        std::cerr << "Details: " << e.what() << std::endl;
        return 1;
    } catch (const cvisa::VisaException& e) {
        std::cerr << "[VISA Error] A generic VISA error occurred." << std::endl;
        std::cerr << "Details: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "A standard C++ error occurred: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nProgram finished successfully." << std::endl;
    return 0;
}