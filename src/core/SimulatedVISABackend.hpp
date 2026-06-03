#ifndef CVISA_SIMULATED_VISA_BACKEND_HPP
#define CVISA_SIMULATED_VISA_BACKEND_HPP

#include "IVISABackend.hpp"
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <memory>
#include <algorithm>

namespace cvisa {

    /**
     * @struct Dialogue
     * @brief Represents a single SCPI command-response pair for simulation.
     * 
     * Similar to PyVisa's simulation files, a dialogue defines:
     * - q: The incoming SCPI query/command
     * - r: The expected response (optional for commands)
     */
    struct Dialogue {
        std::string query;              ///< The SCPI command query string
        std::string response;           ///< The expected response (may be empty for commands)
        bool hasResponse;               ///< Whether this dialogue has a response
        
        Dialogue() : hasResponse(false) {}
        Dialogue(const std::string& q, const std::string& r = "") 
            : query(q), response(r), hasResponse(!r.empty()) {}
    };

    /**
     * @class SimulatedDevice
     * @brief Simulates a single SCPI instrument with dialogue matching.
     * 
     * Maintains a list of dialogues and matches incoming commands to provide
     * appropriate responses. Supports both exact matching and pattern matching.
     */
    class SimulatedDevice {
    private:
        std::string deviceName;
        std::vector<Dialogue> dialogues;
        std::map<std::string, std::string> sessionState;  ///< Store session-specific state (e.g., output status)
        
    public:
        SimulatedDevice() = default;
        explicit SimulatedDevice(const std::string& name) : deviceName(name) {}
        
        /**
         * @brief Set the device name.
         */
        void setName(const std::string& name) { deviceName = name; }
        
        /**
         * @brief Get the device name.
         */
        std::string getName() const { return deviceName; }
        
        /**
         * @brief Add a dialogue to the device.
         */
        void addDialogue(const Dialogue& dialogue) {
            dialogues.push_back(dialogue);
        }
        
        /**
         * @brief Add a dialogue with query and response.
         */
        void addDialogue(const std::string& query, const std::string& response = "") {
            dialogues.emplace_back(query, response);
        }
        
        /**
         * @brief Process a SCPI query and return the response.
         * 
         * Matches the query against all dialogues using exact matching and
         * pattern matching. Returns empty string if no match found.
         * 
         * @param query The SCPI command query
         * @return The response string (may be empty)
         */
        std::string processQuery(const std::string& query) {
            // Trim whitespace
            std::string trimmedQuery = query;
            trimmedQuery.erase(0, trimmedQuery.find_first_not_of(" \t\r\n"));
            trimmedQuery.erase(trimmedQuery.find_last_not_of(" \t\r\n") + 1);
            
            // Try exact match first
            for (const auto& dialogue : dialogues) {
                if (dialogue.query == trimmedQuery) {
                    return dialogue.response;
                }
            }
            
            // Try pattern matching (for parameterized commands like "VOLTage 5.0")
            for (const auto& dialogue : dialogues) {
                if (matchPattern(dialogue.query, trimmedQuery)) {
                    return dialogue.response;
                }
            }
            
            // Default fallback
            return "";
        }
        
        /**
         * @brief Get state value stored in the device.
         */
        std::string getState(const std::string& key) const {
            auto it = sessionState.find(key);
            return (it != sessionState.end()) ? it->second : "";
        }
        
        /**
         * @brief Set state value for the device.
         */
        void setState(const std::string& key, const std::string& value) {
            sessionState[key] = value;
        }
        
    private:
        /**
         * @brief Check if a query pattern matches an incoming command.
         * 
         * Simple pattern matching that treats the dialogue pattern as a regex.
         */
        bool matchPattern(const std::string& pattern, const std::string& command) const {
            try {
                // Escape special regex characters except * and ?
                std::string regexPattern = pattern;
                
                // Replace * with .* and ? with .?
                size_t pos = 0;
                while ((pos = regexPattern.find_first_of("*?", pos)) != std::string::npos) {
                    if (regexPattern[pos] == '*') {
                        regexPattern.replace(pos, 1, ".*");
                        pos += 2;
                    } else if (regexPattern[pos] == '?') {
                        regexPattern.replace(pos, 1, ".");
                        pos += 1;
                    }
                }
                
                std::regex rx(regexPattern, std::regex::icase);
                return std::regex_match(command, rx);
            } catch (const std::regex_error&) {
                return false;
            }
        }
    };

    /**
     * @class SimulatedVISABackend
     * @brief Mock VISA backend that simulates instrument responses.
     * 
     * Similar to PyVisa's simulation capability, this backend allows testing
     * of SCPI drivers without real hardware. Instruments are simulated with
     * predefined dialogues (command-response pairs).
     * 
     * The backend tracks:
     * - Session-to-resource mapping (which device is connected to which session)
     * - Last command written (for proper query-response handling)
     * - Device state (for stateful interactions)
     * 
     * Usage:
     * @code
     * auto backend = std::make_unique<SimulatedVISABackend>();
     * 
     * // Create and populate a simulated device
     * SimulatedDevice device("keysight_6640a");
     * device.addDialogue("*IDN?", "Keysight Technologies,6641A,SN00000001,1.0");
     * device.addDialogue("VOLTage?", "5.000");
     * device.addDialogue("MEASure:VOLTage?", "4.987");
     * device.addDialogue("OUTPut 1");      // Command with no response
     * device.addDialogue("OUTPut?", "1");  // Query with response
     * 
     * // Register the device for specific resource strings
     * backend->registerDevice("GPIB0::5::INSTR", device);
     * 
     * // Create a VISACom with the simulated backend
     * VISACom com(backend.get(), false);
     * com.connect("GPIB0::5::INSTR");
     * 
     * // Now commands are simulated!
     * std::string idn = com.query("*IDN?");
     * com.write("OUTPut 1");
     * std::string status = com.query("OUTPut?");
     * @endcode
     */
    class SimulatedVISABackend : public IVISABackend {
    private:
        std::map<std::string, SimulatedDevice> devices;
        std::map<ViSession, std::string> sessionToResource;
        std::map<ViSession, std::string> sessionLastCommand;  ///< Track last written command
        std::map<ViSession, bool> activeSession;
        ViSession nextSessionHandle;
        
    public:
        SimulatedVISABackend() : nextSessionHandle(100) {}
        
        virtual ~SimulatedVISABackend() = default;
        
        /**
         * @brief Register a simulated device for a specific resource string.
         * 
         * @param resourceName VISA resource string (e.g., "GPIB0::5::INSTR")
         * @param device The simulated device
         */
        void registerDevice(const std::string& resourceName, const SimulatedDevice& device) {
            devices[resourceName] = device;
        }
        
        /**
         * @brief Get a registered device.
         */
        SimulatedDevice* getDevice(const std::string& resourceName) {
            auto it = devices.find(resourceName);
            return (it != devices.end()) ? &it->second : nullptr;
        }
        
        /**
         * @brief Get the number of registered devices.
         */
        size_t getDeviceCount() const { return devices.size(); }
        
        /**
         * @brief Check if a resource is registered.
         */
        bool hasResource(const std::string& resourceName) const {
            return devices.find(resourceName) != devices.end();
        }
        
        // --- IVISABackend Implementation ---
        
        ViStatus visaOpenDefaultRM(ViSession* sesn) override {
            if (!sesn) return VI_ERROR_NULL_OBJECT;
            *sesn = 1;  // Default resource manager handle
            activeSession[1] = true;
            return VI_SUCCESS;
        }
        
        ViStatus visaOpen(ViSession sesn, const ViRsrc name, ViAccessMode mode, 
                         ViUInt32 timeout, ViPSession vi) override {
            if (!vi || !name) return VI_ERROR_NULL_OBJECT;
            
            std::string resourceName(name);
            
            // Check if resource is registered
            if (devices.find(resourceName) == devices.end()) {
                return VI_ERROR_RSRC_NFOUND;
            }
            
            // Create a new session handle
            ViSession newHandle = ++nextSessionHandle;
            sessionToResource[newHandle] = resourceName;
            activeSession[newHandle] = true;
            sessionLastCommand[newHandle] = "";
            *vi = newHandle;
            
            return VI_SUCCESS;
        }
        
        ViStatus visaClose(ViObject vi) override {
            ViSession session = (ViSession)vi;
            sessionToResource.erase(session);
            sessionLastCommand.erase(session);
            activeSession[session] = false;
            return VI_SUCCESS;
        }
        
        ViStatus visaSetAttribute(ViObject vi, ViAttr attr, ViAttrState attrState) override {
            // Simulated - just succeed
            return VI_SUCCESS;
        }
        
        ViStatus visaGetAttribute(ViObject vi, ViAttr attr, void* attrState) override {
            // Simulated - just succeed
            return VI_SUCCESS;
        }
        
        ViStatus visaWrite(ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount) override {
            // Store the written command for the subsequent read
            if (buf && count > 0) {
                std::string command(reinterpret_cast<const char*>(buf), count);
                sessionLastCommand[vi] = command;
            }
            
            if (retCount) *retCount = count;
            return VI_SUCCESS;
        }
        
        ViStatus visaRead(ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount) override {
            if (!retCount || !buf) return VI_ERROR_NULL_OBJECT;
            
            auto resourceIt = sessionToResource.find(vi);
            if (resourceIt == sessionToResource.end()) {
                return VI_ERROR_CONN_LOST;
            }
            
            SimulatedDevice* device = getDevice(resourceIt->second);
            if (!device) {
                return VI_ERROR_RSRC_NFOUND;
            }
            
            // Get the last command written to this session
            std::string query = sessionLastCommand[vi];
            
            // Process the query through the device
            std::string response = device->processQuery(query);
            
            // Add terminator if response doesn't already have one
            if (!response.empty() && response.back() != '\n') {
                response += "\n";
            }
            
            // Copy response to buffer
            size_t copyLen = std::min((size_t)count, response.length());
            std::copy(response.begin(), response.begin() + copyLen, buf);
            *retCount = static_cast<ViUInt32>(copyLen);
            
            // Clear the last command after responding
            sessionLastCommand[vi] = "";
            
            return VI_SUCCESS;
        }
        
        ViStatus visaClear(ViSession vi) override {
            return VI_SUCCESS;
        }
        
        ViStatus visaReadSTB(ViSession vi, ViPUInt16 status) override {
            if (status) *status = 0;
            return VI_SUCCESS;
        }
        
        ViStatus visaFindRsrc(ViSession sesn, ViConstRsrc expr, ViPFindList findList,
                             ViPUInt32 retCount, ViRsrc instrDesc) override {
            if (!retCount || !instrDesc) return VI_ERROR_NULL_OBJECT;
            
            *retCount = 0;
            std::string pattern(expr ? expr : "*");
            
            // Simple pattern matching: * matches all resources
            for (const auto& resourcePair : devices) {
                if (pattern == "*" || resourcePair.first.find(pattern) != std::string::npos) {
                    std::copy(resourcePair.first.begin(), resourcePair.first.end(), instrDesc);
                    instrDesc[resourcePair.first.length()] = '\0';
                    *retCount = 1;
                    return VI_SUCCESS;
                }
            }
            
            return VI_ERROR_RSRC_NFOUND;
        }
        
        ViStatus visaFindNext(ViFindList findList, ViRsrc instrDesc) override {
            return VI_ERROR_RSRC_NFOUND;  // Only return one result
        }
        
        ViStatus visaStatusDesc(ViObject vi, ViStatus status, ViChar desc[]) override {
            if (desc) {
                std::string statusStr = "Simulated VISA status: " + std::to_string(status);
                std::copy(statusStr.begin(), statusStr.end(), desc);
                desc[statusStr.length()] = '\0';
            }
            return VI_SUCCESS;
        }
    };

} // namespace cvisa

#endif // CVISA_SIMULATED_VISA_BACKEND_HPP
