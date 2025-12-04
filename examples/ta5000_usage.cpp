#include <iostream>
#include <string>
#include <vector>

#include "drivers/ThermalAirTA5000.hpp"

int main() {
    // This is a simulated example.
    // Replace "GPIB0::1::INSTR" with your instrument's actual VISA resource
    // name.
    std::string resourceName = "GPIB0::1::INSTR";
    cvisa::drivers::ThermalAirTA5000 ta5000;

    std::cout << "--- cvisa TA-5000 Example ---" << std::endl;
    std::cout << "Description: " << ta5000.getDescription() << std::endl;

    try {
        // --- Connection ---
        // The driver will automatically connect when the resource name is set.
        // The destructor will automatically disconnect.
        std::cout << "\nConnecting to " << resourceName << "..." << std::endl;
        ta5000.connect(resourceName);

        // --- Basic Operations ---
        std::cout << "Instrument ID: " << ta5000.getIdentification()
                  << std::endl;

        ta5000.reset();
        std::cout << "Instrument has been reset." << std::endl;

        ta5000.setFlowOn();
        std::cout << "Main air flow is ON." << std::endl;

        // --- Temperature Control ---
        double setpoint = 50.0;
        std::cout << "\nSetting temperature setpoint to " << setpoint << " C..."
                  << std::endl;
        ta5000.setSetpoint(setpoint);

        double actualSetpoint = ta5000.getSetpoint();
        std::cout << "Current setpoint is: " << actualSetpoint << " C"
                  << std::endl;

        double currentTemp = ta5000.getTemperature();
        std::cout << "Current temperature is: " << currentTemp << " C"
                  << std::endl;

        ta5000.setFlowOff();
        std::cout << "\nMain air flow is OFF." << std::endl;

    } catch (const cvisa::VisaException& e) {
        std::cerr << "A VISA error occurred: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    std::cout << "\nExample finished." << std::endl;

    return 0;
}
