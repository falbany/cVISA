#include "../src/core/VISACom.hpp"
#include "../src/core/SCPIBase.hpp"
#include "../src/core/SimulatedVISABackend.hpp"
#include "../src/core/Simulations.hpp"
#include <iostream>
#include <memory>

/**
 * @file simulated_device_usage.cpp
 * @brief Example demonstrating how to test SCPI drivers with simulated instruments
 * 
 * This example shows the PyVisa-like simulation capability: test your drivers
 * without real hardware by using simulated devices with predefined SCPI dialogues.
 * 
 * Usage:
 * @code
 * // Compile with: g++ -std=c++11 -I. simulated_device_usage.cpp
 * // Run: ./a.out
 * @endcode
 */

/**
 * @class SimpleAgilentPowerSupply
 * @brief Simplified Agilent power supply driver for demonstration
 * 
 * Shows how drivers can be instantiated with a simulated backend
 * for testing without real hardware.
 */
class SimpleAgilentPowerSupply : public cvisa::drivers::SCPIBase {
public:
    explicit SimpleAgilentPowerSupply(std::shared_ptr<cvisa::IVISABackend> backend = nullptr)
        : SCPIBase(backend) {}
    
    /**
     * @brief Enable/disable output
     */
    void setOutput(bool enable) {
        std::string cmd = enable ? "OUTPut 1" : "OUTPut 0";
        executeCommand(cmd);
    }
    
    /**
     * @brief Get output state
     */
    bool getOutput() {
        std::string response = query("OUTPut?");
        return response.find("1") != std::string::npos;
    }
    
    /**
     * @brief Set voltage (in volts)
     */
    void setVoltage(double voltage) {
        executeCommand("VOLTage " + std::to_string(voltage));
    }
    
    /**
     * @brief Get configured voltage
     */
    double getVoltage() {
        std::string response = query("VOLTage?");
        try {
            return std::stod(response);
        } catch (...) {
            return 0.0;
        }
    }
    
    /**
     * @brief Measure actual output voltage
     */
    double measureVoltage() {
        std::string response = query("MEASure:VOLTage?");
        try {
            return std::stod(response);
        } catch (...) {
            return 0.0;
        }
    }
    
    /**
     * @brief Set current limit (in amps)
     */
    void setCurrent(double current) {
        executeCommand("CURRent " + std::to_string(current));
    }
    
    /**
     * @brief Get current limit
     */
    double getCurrent() {
        std::string response = query("CURRent?");
        try {
            return std::stod(response);
        } catch (...) {
            return 0.0;
        }
    }
    
    /**
     * @brief Measure actual output current
     */
    double measureCurrent() {
        std::string response = query("MEASure:CURRent?");
        try {
            return std::stod(response);
        } catch (...) {
            return 0.0;
        }
    }
    
    /**
     * @brief Get instrument identification
     */
    std::string getIDN() {
        return query("*IDN?");
    }
};

int main() {
    try {
        std::cout << "=== Simulated Device Usage Example ===" << std::endl;
        std::cout << std::endl;
        
        // ========================================
        // Example 1: Using pre-configured backend
        // ========================================
        std::cout << "Example 1: Using Pre-configured Keysight Simulation Backend" << std::endl;
        std::cout << "---" << std::endl;
        
        auto simBackend = cvisa::simulations::createKeysightSimulation();
        
        {
            SimpleAgilentPowerSupply psu(simBackend);
            psu.connect("GPIB0::5::INSTR");
            
            std::cout << "Connected to: GPIB0::5::INSTR" << std::endl;
            std::cout << "IDN: " << psu.getIDN() << std::endl;
            std::cout << "Configured Voltage: " << psu.getVoltage() << " V" << std::endl;
            std::cout << "Measured Voltage: " << psu.measureVoltage() << " V" << std::endl;
            std::cout << "Configured Current: " << psu.getCurrent() << " A" << std::endl;
            std::cout << "Measured Current: " << psu.measureCurrent() << " A" << std::endl;
            
            psu.disconnect();
        }
        
        std::cout << std::endl;
        
        // ========================================
        // Example 2: Building custom simulated backend
        // ========================================
        std::cout << "Example 2: Custom Simulated Device Configuration" << std::endl;
        std::cout << "---" << std::endl;
        
        auto customBackend = std::make_unique<cvisa::SimulatedVISABackend>();
        
        // Create a custom device with specific dialogues
        cvisa::SimulatedDevice customDevice("test_psu");
        customDevice.addDialogue("*IDN?", "Custom Test Supply,PSU-100,12345,2.0");
        customDevice.addDialogue("*RST");
        customDevice.addDialogue("*CLS");
        customDevice.addDialogue("*OPC?", "1");
        customDevice.addDialogue("OUTPut 1");
        customDevice.addDialogue("OUTPut?", "1");
        customDevice.addDialogue("VOLTage?", "12.000");
        customDevice.addDialogue("MEASure:VOLTage?", "11.987");
        customDevice.addDialogue("CURRent?", "3.000");
        customDevice.addDialogue("MEASure:CURRent?", "2.95");
        
        // Register on multiple resource strings
        customBackend->registerDevice("GPIB0::10::INSTR", customDevice);
        customBackend->registerDevice("TCPIP0::192.168.1.50::inst0::INSTR", customDevice);
        
        {
            SimpleAgilentPowerSupply psu(customBackend);
            
            // Test GPIB connection
            psu.connect("GPIB0::10::INSTR");
            std::cout << "Connected to: GPIB0::10::INSTR" << std::endl;
            std::cout << "IDN: " << psu.getIDN() << std::endl;
            std::cout << "Status: Output is " << (psu.getOutput() ? "ON" : "OFF") << std::endl;
            psu.disconnect();
            
            // Test TCPIP connection (same device)
            psu.connect("TCPIP0::192.168.1.50::inst0::INSTR");
            std::cout << std::endl;
            std::cout << "Connected to: TCPIP0::192.168.1.50::inst0::INSTR" << std::endl;
            std::cout << "IDN: " << psu.getIDN() << std::endl;
            std::cout << "Status: Output is " << (psu.getOutput() ? "ON" : "OFF") << std::endl;
            psu.disconnect();
        }
        
        std::cout << std::endl;
        
        // ========================================
        // Example 3: Testing device behavior
        // ========================================
        std::cout << "Example 3: Testing Device Behavior Without Hardware" << std::endl;
        std::cout << "---" << std::endl;
        
        auto testBackend = std::make_unique<cvisa::SimulatedVISABackend>();
        auto testDevice = cvisa::simulations::createKeysight6640A();
        testBackend->registerDevice("GPIB0::1::INSTR", testDevice);
        
        {
            SimpleAgilentPowerSupply psu(testBackend);
            psu.connect("GPIB0::1::INSTR");
            
            std::cout << "Initial voltage setpoint: " << psu.getVoltage() << " V" << std::endl;
            std::cout << "Initial current limit: " << psu.getCurrent() << " A" << std::endl;
            
            // Set new values
            std::cout << std::endl;
            std::cout << "Setting voltage to 10.0V..." << std::endl;
            psu.setVoltage(10.0);
            // Note: In simulation, the response would come from predefined dialogue
            // A real device would change the setpoint
            
            std::cout << "Enabling output..." << std::endl;
            psu.setOutput(true);
            
            std::cout << "Output is now: " << (psu.getOutput() ? "ON" : "OFF") << std::endl;
            
            std::cout << std::endl;
            std::cout << "Simulated measurements:" << std::endl;
            std::cout << "  Output Voltage: " << psu.measureVoltage() << " V" << std::endl;
            std::cout << "  Output Current: " << psu.measureCurrent() << " A" << std::endl;
            
            psu.disconnect();
        }
        
        std::cout << std::endl;
        std::cout << "=== Test Completed Successfully ===" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
