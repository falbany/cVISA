#include "drivers/ThermalAirTA5000.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    // This is a simulated example.
    // Replace "GPIB0::1::INSTR" with your instrument's actual VISA resource
    // name.
    std::string                      resourceName = "GPIB0::1::INSTR";
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
        std::cout << "Instrument ID: " << ta5000.IDN_Query() << std::endl;

        ta5000.RST();
        std::cout << "Instrument has been reset." << std::endl;

        ta5000.setCompressorOn();
        std::cout << "Compressor is ON." << std::endl;

        ta5000.setFlowOn();
        std::cout << "Main air flow is ON." << std::endl;

        // --- Temperature Control ---
        double setpoint  = 50.0;
        double ramp_rate = 10.0;

        std::cout << "\nSetting ramp rate to " << ramp_rate << " C/min..." << std::endl;
        ta5000.setRampRate(ramp_rate);

        std::cout << "Setting temperature setpoint to " << setpoint << " C..." << std::endl;
        ta5000.setSetpoint(setpoint);

        double actualSetpoint = ta5000.getSetpoint();
        std::cout << "Current setpoint is: " << actualSetpoint << " C" << std::endl;

        double currentTemp = ta5000.getTemperature();
        std::cout << "Current temperature is: " << currentTemp << " C" << std::endl;

        // --- Soak and Window ---
        std::cout << "\nConfiguring soak time and temperature window..." << std::endl;
        ta5000.setSoakTime(30);    // 30 seconds
        ta5000.setWindow(2.5);     // 2.5 C
        std::cout << "Soak time set to: " << ta5000.getSoakTime() << " s" << std::endl;
        std::cout << "Window set to: " << ta5000.getWindow() << " C" << std::endl;

        // --- Control Mode ---
        std::cout << "\nSetting control mode..." << std::endl;
        ta5000.setDutControlMode(true);
        std::cout << "Control mode is now: " << (ta5000.isDutControlModeEnabled() ? "DUT" : "Air") << std::endl;
        ta5000.setDutControlMode(false);
        std::cout << "Control mode is now: " << (ta5000.isDutControlModeEnabled() ? "DUT" : "Air") << std::endl;

        // --- Airflow Control ---
        std::cout << "\nConfiguring airflow..." << std::endl;
        ta5000.setFlowRate(15);    // 15 scfm
        std::cout << "Flow rate setting: " << ta5000.getFlowRateSetting() << " scfm" << std::endl;
        std::cout << "Measured flow rate: " << ta5000.measureFlowRate() << " scfm" << std::endl;

        // --- System Limits ---
        std::cout << "\nSetting temperature limits..." << std::endl;
        ta5000.setLowerTempLimit(-55.0);
        ta5000.setUpperTempLimit(125.0);
        std::cout << "Limits set. Note: Getter functions for limits are not available on TA-5000." << std::endl;

        // --- Error Checking ---
        std::cout << "\nChecking for errors..." << std::endl;
        int errorState = ta5000.getErrorState();
        if (errorState == 0) {
            std::cout << "No system errors detected." << std::endl;
        } else {
            std::cout << "System error state: " << errorState << std::endl;
        }

        // --- Shutdown ---
        ta5000.setFlowOff();
        std::cout << "\nMain air flow is OFF." << std::endl;

        ta5000.setCompressorOff();
        std::cout << "Compressor is OFF." << std::endl;

    } catch (const cvisa::VisaException& e) {
        std::cerr << "A VISA error occurred: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    std::cout << "\nExample finished." << std::endl;

    return 0;
}
