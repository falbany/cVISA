#ifndef CVISA_SIMULATIONS_HPP
#define CVISA_SIMULATIONS_HPP

#include "SimulatedVISABackend.hpp"

namespace cvisa {
namespace simulations {

    /**
     * @brief Create a simulated Keysight/Agilent 6640A/6641A Power Supply
     * 
     * @return SimulatedDevice configured with 6640A/6641A dialogues
     */
    inline SimulatedDevice createKeysight6640A() {
        SimulatedDevice device("keysight_6640a");
        
        // IEEE-488.2 Common Commands
        device.addDialogue("*IDN?", "Keysight Technologies,6641A,SN00000001,1.0-0.0");
        device.addDialogue("*RST");
        device.addDialogue("*CLS");
        device.addDialogue("*OPC");
        device.addDialogue("*OPC?", "1");
        device.addDialogue("*TST?", "0");
        
        // Output Control
        device.addDialogue("OUTPut 1");
        device.addDialogue("OUTPut 0");
        device.addDialogue("OUTPut?", "1");
        
        // Voltage Control
        device.addDialogue("VOLTage?", "5.000");
        device.addDialogue("MEASure:VOLTage?", "4.987");
        device.addDialogue("VOLTage 5.0");
        
        // Current Control
        device.addDialogue("CURRent?", "1.000");
        device.addDialogue("MEASure:CURRent?", "0.987");
        device.addDialogue("CURRent 1.5");
        
        // Protection
        device.addDialogue("VOLTage:PROTection?", "6.000");
        device.addDialogue("VOLTage:PROTection 6.5");
        device.addDialogue("CURRent:PROTection:STATe 0");
        device.addDialogue("CURRent:PROTection:STATe 1");
        device.addDialogue("CURRent:PROTection:STATe?", "1");
        device.addDialogue("OUTPut:PROTection:CLEar");
        
        return device;
    }
    
    /**
     * @brief Create a simulated HP/Agilent 66311B DC Power Module
     * 
     * @return SimulatedDevice configured with 66311B dialogues
     */
    inline SimulatedDevice createAgilent66311B() {
        SimulatedDevice device("agilent_66311b");
        
        // IEEE-488.2 Common Commands
        device.addDialogue("*IDN?", "Agilent Technologies,66311B,SN00000002,1.0");
        device.addDialogue("*RST");
        device.addDialogue("*CLS");
        device.addDialogue("*OPC?", "1");
        
        // Output Control
        device.addDialogue("OUTPut 1");
        device.addDialogue("OUTPut 0");
        device.addDialogue("OUTPut?", "0");
        
        // Voltage
        device.addDialogue("VOLTage?", "12.000");
        device.addDialogue("MEASure:VOLTage?", "11.950");
        
        // Current
        device.addDialogue("CURRent?", "5.000");
        device.addDialogue("MEASure:CURRent?", "4.987");
        
        return device;
    }
    
    /**
     * @brief Create a simulated Generic SCPI Instrument
     * 
     * Useful for testing basic SCPI functionality
     * 
     * @return SimulatedDevice configured with basic SCPI commands
     */
    inline SimulatedDevice createGenericSCPIDevice() {
        SimulatedDevice device("generic_scpi");
        
        // Identification
        device.addDialogue("*IDN?", "Generic Instrument,Model-123,12345,1.0");
        
        // Status and Control
        device.addDialogue("*RST");
        device.addDialogue("*CLS");
        device.addDialogue("*OPC?", "1");
        device.addDialogue("*ESR?", "0");
        device.addDialogue("*STB?", "0");
        
        // System Commands
        device.addDialogue("SYSTem:ERRor?", "0,No error");
        device.addDialogue("SYSTem:VERSion?", "1999.0");
        
        // Status Register
        device.addDialogue("STATus:QUEue?", "0,No error");
        
        return device;
    }
    
    /**
     * @brief Register multiple simulated devices into a backend
     * 
     * @param backend The SimulatedVISABackend to register devices into
     * @param deviceConfig Map of resource names to devices
     */
    inline void registerDevices(SimulatedVISABackend* backend,
                               const std::map<std::string, SimulatedDevice>& deviceConfig) {
        if (!backend) return;
        for (const auto& entry : deviceConfig) {
            backend->registerDevice(entry.first, entry.second);
        }
    }
    
    /**
     * @brief Create a pre-configured backend with common Keysight instruments
     * 
     * @return unique_ptr to SimulatedVISABackend with 6640A/6641A on various interfaces
     */
    inline std::unique_ptr<SimulatedVISABackend> createKeysightSimulation() {
        auto backend = std::make_unique<SimulatedVISABackend>();
        auto device = createKeysight6640A();
        
        // Register on multiple interfaces
        backend->registerDevice("GPIB0::5::INSTR", device);
        backend->registerDevice("GPIB0::6::INSTR", device);
        backend->registerDevice("TCPIP0::192.168.1.100::inst0::INSTR", device);
        backend->registerDevice("TCPIP0::SIM::inst0::INSTR", device);
        backend->registerDevice("USB0::0x2A8D::0x0001::SN00000001::INSTR", device);
        
        return backend;
    }

}} // namespace cvisa::simulations

#endif // CVISA_SIMULATIONS_HPP
