#ifndef CVISA_SIMULATION_CONFIG_HPP
#define CVISA_SIMULATION_CONFIG_HPP

#include "SimulatedVISABackend.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace cvisa {
namespace simulation {

    /**
     * @struct SimulationConfig
     * @brief Represents a simulation configuration loaded from YAML/JSON.
     */
    struct SimulationConfig {
        std::string spec_version;           ///< Configuration format version
        std::string device_name;            ///< Human-readable device name
        std::string device_model;           ///< Device model string
        std::map<std::string, std::string> end_of_message;  ///< EOM per interface type
        std::vector<Dialogue> dialogues;    ///< SCPI command-response pairs
    };

    /**
     * @brief Parse a JSON/YAML simulation configuration file.
     * 
     * @param filepath Path to the simulation config file
     * @return SimulationConfig parsed from the file
     * @throws std::runtime_error if file cannot be parsed
     */
    inline SimulationConfig loadConfig(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open simulation config file: " + filepath);
        }
        
        nlohmann::json j;
        try {
            j = nlohmann::json::parse(file);
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error(
                "Failed to parse simulation config file '" + filepath + 
                "': " + std::string(e.what())
            );
        }
        
        SimulationConfig config;
        
        // Parse spec version
        if (j.contains("spec")) {
            config.spec_version = j["spec"].get<std::string>();
        } else {
            config.spec_version = "1.0";  // Default
        }
        
        // Parse device information
        if (j.contains("device")) {
            const auto& device = j["device"];
            if (device.contains("name")) {
                config.device_name = device["name"].get<std::string>();
            }
            if (device.contains("model")) {
                config.device_model = device["model"].get<std::string>();
            }
            if (device.contains("eom")) {
                for (const auto& [key, value] : device["eom"].items()) {
                    config.end_of_message[key] = value.get<std::string>();
                }
            }
        }
        
        // Parse dialogues
        if (j.contains("dialogues")) {
            const auto& dialogues = j["dialogues"];
            for (const auto& dialogue : dialogues) {
                Dialogue d;
                
                if (dialogue.contains("q")) {
                    d.query = dialogue["q"].get<std::string>();
                }
                
                if (dialogue.contains("r")) {
                    d.response = dialogue["r"].get<std::string>();
                    d.hasResponse = !d.response.empty();
                } else {
                    d.hasResponse = false;
                }
                
                config.dialogues.push_back(d);
            }
        }
        
        return config;
    }

    /**
     * @brief Create a SimulatedDevice from a SimulationConfig.
     * 
     * @param config The parsed simulation configuration
     * @return SimulatedDevice populated with dialogues from config
     */
    inline SimulatedDevice configToDevice(const SimulationConfig& config) {
        SimulatedDevice device(config.device_name);
        
        for (const auto& dialogue : config.dialogues) {
            device.addDialogue(dialogue.query, dialogue.response);
        }
        
        return device;
    }

    /**
     * @brief Load a simulation config and create a SimulatedDevice.
     * 
     * @param filepath Path to the simulation config file
     * @return SimulatedDevice populated from the file
     */
    inline SimulatedDevice loadDevice(const std::string& filepath) {
        SimulationConfig config = loadConfig(filepath);
        return configToDevice(config);
    }

    /**
     * @brief Register a simulation device from a YAML file with a backend.
     * 
     * @param backend The SimulatedVISABackend to register the device with
     * @param filepath Path to the simulation config file
     * @param resourceName VISA resource string to register the device under
     */
    inline void loadAndRegister(SimulatedVISABackend* backend,
                               const std::string& filepath,
                               const std::string& resourceName) {
        if (!backend) {
            throw std::runtime_error("SimulatedVISABackend pointer is null");
        }
        
        SimulatedDevice device = loadDevice(filepath);
        backend->registerDevice(resourceName, device);
    }

    /**
     * @brief Register multiple resources for a simulation device from a YAML file.
     * 
     * @param backend The SimulatedVISABackend to register devices with
     * @param filepath Path to the simulation config file
     * @param resourceNames Vector of VISA resource strings to register the device under
     */
    inline void loadAndRegister(SimulatedVISABackend* backend,
                               const std::string& filepath,
                               const std::vector<std::string>& resourceNames) {
        if (!backend) {
            throw std::runtime_error("SimulatedVISABackend pointer is null");
        }
        
        SimulatedDevice device = loadDevice(filepath);
        
        for (const auto& resourceName : resourceNames) {
            backend->registerDevice(resourceName, device);
        }
    }

    /**
     * @brief Load all simulation configs from a directory and register them.
     * 
     * @param backend The SimulatedVISABackend to register devices with
     * @param configDir Directory containing YAML simulation config files
     * @param resourceNameMap Map from model name to resource strings
     */
    inline void loadSimulationDirectory(SimulatedVISABackend* backend,
                                       const std::string& configDir,
                                       const std::map<std::string, std::vector<std::string>>& resourceNameMap) {
        if (!backend) {
            throw std::runtime_error("SimulatedVISABackend pointer is null");
        }
        
        // Simple directory iteration (in production, use std::filesystem)
        // For now, manually iterate through known config files
        struct ConfigFile {
            std::string basename;
            std::string filename;
        };
        
        std::vector<ConfigFile> configs = {
            {"agilent66xxA", "agilent66xxA.yaml"},
            {"thermalair_ta5000", "thermalair_ta5000.yaml"}
        };
        
        for (const auto& config : configs) {
            auto it = resourceNameMap.find(config.basename);
            if (it != resourceNameMap.end()) {
                std::string filepath = configDir + "/" + config.filename;
                loadAndRegister(backend, filepath, it->second);
            }
        }
    }

} // namespace simulation
} // namespace cvisa

#endif // CVISA_SIMULATION_CONFIG_HPP
