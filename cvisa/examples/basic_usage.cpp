#include <iostream>
#include <string>

// Include the header directly. The include path is set by CMake's
// target_include_directories, so we don't need "src/".
#include "VisaInstrument.hpp"
#include "exceptions.hpp"

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
        // Create the VisaInstrument object.
        // The constructor handles opening the connection (RAII).
        cvisa::VisaInstrument scope(resource_address);

        // Set a communication timeout (e.g., 5000 ms)
        scope.setTimeout(5000);
        std::cout << "Connection successful. Timeout set to 5000 ms." << std::endl;

        // Use a convenience SCPI method to get the identification string.
        std::string idn = scope.getIdentification(); // Equivalent to scope.query("*IDN?")
        std::cout << "Instrument Identification: " << idn << std::endl;

        // Reset the instrument to a known state.
        scope.reset(); // Sends "*RST"
        std::cout << "Instrument has been reset." << std::endl;

        // Use a low-level query to get a specific setting.
        // The command will depend on the specific instrument.
        // This example command is for a generic oscilloscope.
        // std::string timebase = scope.query(":TIMebase:RANGe?");
        // std::cout << "Current timebase range: " << timebase;

        // Clear the instrument's status registers.
        scope.clearStatus(); // Sends "*CLS"
        std::cout << "Instrument status cleared." << std::endl;

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
        std::cerr << "[Command Error] An error occurred while communicating with the instrument." << std::endl;
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