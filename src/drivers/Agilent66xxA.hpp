#ifndef CVISA_DRIVER_AGILENT_66XXA_HPP
#define CVISA_DRIVER_AGILENT_66XXA_HPP

#include "../core/SCPIBase.hpp"
#include "../core/SCPICommand.hpp"

#include <map>
#include <string>

namespace cvisa {
    namespace drivers {

        /**
         * @class Agilent66xxA
         * @brief An instrument driver for the Agilent/Keysight 66xxA series of power
         * supplies.
         *
         * This driver supports the following models:
         * - Keysight 664xA
         * - Keysight 665xA
         * - Keysight 667xA
         * - Keysight 668xA
         * - Keysight 669xA
         *
         * It defines its command set as a public nested struct of static methods
         * that return SCPICommand objects.
         */
        class Agilent66xxA : public SCPIBase {
          public:
            /**
             * @brief Default constructor. Creates a disconnected driver.
             */
            Agilent66xxA() : SCPIBase() { m_description = "Agilent/Keysight 66xxA Series Power Supply"; }

            /**
             * @brief Constructs and connects with resource name only.
             */
            explicit Agilent66xxA(const std::string& resourceName) : SCPIBase(resourceName) { m_description = "Agilent/Keysight 66xxA Series Power Supply"; }

            /**
             * @brief Constructs and connects with timeout and read termination.
             */
            explicit Agilent66xxA(const std::string& resourceName, unsigned int timeout_ms, char read_termination)
                : SCPIBase(resourceName, timeout_ms, read_termination) {
                m_description = "Agilent/Keysight 66xxA Series Power Supply";
            }

            // --- Output Subsystem ---
            /**
             * @brief Sets the immediate output voltage level.
             * @param voltage The desired voltage in Volts.
             */
            void setVoltage(double voltage);

            /**
             * @brief Queries the programmed immediate output voltage level.
             * @return The programmed voltage in Volts.
             */
            double getVoltageSetting();

            /**
             * @brief Returns the voltage measured at the sense terminals.
             * @return The measured voltage in Volts.
             */
            double measureVoltage();

            /**
             * @brief Sets the immediate output current level.
             * @param current The desired current in Amperes.
             */
            void setCurrent(double current);

            /**
             * @brief Queries the programmed immediate output current level.
             * @return The programmed current in Amperes.
             */
            double getCurrentSetting();

            /**
             * @brief Returns the current measured at the sense terminals.
             * @return The measured current in Amperes.
             */
            double measureCurrent();

            /**
             * @brief Enables or disables the power supply output.
             * @param enabled True to enable the output, false to disable.
             */
            void setOutput(bool enabled);

            /**
             * @brief Queries the current state of the output.
             * @return True if the output is enabled, false otherwise.
             */
            bool isOutputEnabled();

            /**
             * @brief Clears any tripped protection features (OV, OC, OT, or RI).
             */
            void clearProtection();

            // --- Over-Voltage Protection ---
            /**
             * @brief Sets the overvoltage protection (OVP) level.
             * @param level The OVP level in Volts.
             */
            void setOverVoltageProtection(double level);

            /**
             * @brief Queries the programmed OVP level.
             * @return The OVP level in Volts.
             */
            double getOverVoltageProtection();

            // --- Over-Current Protection ---
            /**
             * @brief Enables or disables the overcurrent protection (OCP) function.
             * @param enabled True to enable OCP, false to disable.
             */
            void setOverCurrentProtection(bool enabled);

            /**
             * @brief Queries the state of the OCP function.
             * @return True if OCP is enabled, false otherwise.
             */
            bool isOverCurrentProtectionEnabled();

            // --- Display Subsystem ---
            /**
             * @brief Enables or disables the front panel display.
             * @param enabled True to enable the display, false to disable.
             */
            void setDisplayEnabled(bool enabled);

            /**
             * @brief Queries the state of the display.
             * @return True if the display is enabled, false otherwise.
             */
            bool isDisplayEnabled();

            /**
             * @brief Sends a character string to be displayed on the front panel.
             * @param text The text to display.
             */
            void displayText(const std::string& text);

            /**
             * @brief Queries the last programmed text string.
             * @return The displayed text.
             */
            std::string getDisplayText();

            // --- Trigger Subsystem ---
            /**
             * @brief Enables the trigger subsystem for a single action.
             */
            void initiate();

            /**
             * @brief Cancels any trigger actions presently in process.
             */
            void abort();

            /**
             * @brief Selects the trigger source to be the GPIB bus.
             */
            void setTriggerSourceBus();

            /**
             * @brief Generates a trigger signal.
             */
            void trigger();

            /**
             * @brief Sets the pending triggered voltage level.
             * @param voltage The triggered voltage level in Volts.
             */
            void setTriggeredVoltage(double voltage);

            /**
             * @brief Queries the pending triggered voltage level.
             * @return The triggered voltage level in Volts.
             */
            double getTriggeredVoltage();

            /**
             * @brief Sets the pending triggered current level.
             * @param current The triggered current level in Amperes.
             */
            void setTriggeredCurrent(double current);

            /**
             * @brief Queries the pending triggered current level.
             * @return The triggered current level in Amperes.
             */
            double getTriggeredCurrent();

            // --- Command Definitions ---
            struct Commands {
                // --- Output Commands ---
                static SCPICommand SET_VOLTAGE() {
                    return SCPICommand("SOURCE:VOLTAGE:LEVEL:IMMEDIATE:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0, "Set output voltage.");
                }
                static SCPICommand GET_VOLTAGE_SET() {
                    return SCPICommand("SOURCE:VOLTAGE:LEVEL:IMMEDIATE:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get output voltage setting.");
                }
                static SCPICommand MEAS_VOLTAGE() { return SCPICommand("MEASURE:VOLTAGE:DC?", CommandType::QUERY, ResponseType::DOUBLE, 50, "Measure voltage."); }
                static SCPICommand SET_CURRENT() {
                    return SCPICommand("SOURCE:CURRENT:LEVEL:IMMEDIATE:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0, "Set output current.");
                }
                static SCPICommand GET_CURRENT_SET() {
                    return SCPICommand("SOURCE:CURRENT:LEVEL:IMMEDIATE:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get output current setting.");
                }
                static SCPICommand MEAS_CURRENT() { return SCPICommand("MEASURE:CURRENT:DC?", CommandType::QUERY, ResponseType::DOUBLE, 50, "Measure current."); }
                static SCPICommand SET_OUTPUT() { return SCPICommand("OUTPUT:STATE %s", CommandType::WRITE, ResponseType::NONE, 0, "Set output state."); }
                static SCPICommand GET_OUTPUT_STATE() { return SCPICommand("OUTPUT:STATE?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get output state."); }
                static SCPICommand CLEAR_PROTECTION() {
                    return SCPICommand("OUTPUT:PROTECTION:CLEAR", CommandType::WRITE, ResponseType::NONE, 0, "Clear tripped protection.");
                }

                // --- Over-Voltage Protection ---
                static SCPICommand SET_OVP() { return SCPICommand("SOURCE:VOLTAGE:PROTECTION:LEVEL %f", CommandType::WRITE, ResponseType::NONE, 0, "Set OVP level."); }
                static SCPICommand GET_OVP() { return SCPICommand("SOURCE:VOLTAGE:PROTECTION:LEVEL?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get OVP level."); }

                // --- Over-Current Protection ---
                static SCPICommand SET_OCP() { return SCPICommand("SOURCE:CURRENT:PROTECTION:STATE %s", CommandType::WRITE, ResponseType::NONE, 0, "Set OCP state."); }
                static SCPICommand GET_OCP() { return SCPICommand("SOURCE:CURRENT:PROTECTION:STATE?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get OCP state."); }

                // --- Display Commands ---
                static SCPICommand SET_DISPLAY_ENABLED() {
                    return SCPICommand("DISPLAY:WINDOW:STATE %s", CommandType::WRITE, ResponseType::NONE, 0, "Set display state.");
                }
                static SCPICommand GET_DISPLAY_ENABLED() {
                    return SCPICommand("DISPLAY:WINDOW:STATE?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get display state.");
                }
                static SCPICommand DISPLAY_TEXT() { return SCPICommand("DISPLAY:WINDOW:TEXT:DATA \"%s\"", CommandType::WRITE, ResponseType::NONE, 0, "Display text."); }
                static SCPICommand GET_DISPLAY_TEXT() {
                    return SCPICommand("DISPLAY:WINDOW:TEXT:DATA?", CommandType::QUERY, ResponseType::STRING, 0, "Get displayed text.");
                }

                // --- Trigger Commands ---
                static SCPICommand INITIATE() { return SCPICommand("INITIATE:IMMEDIATE", CommandType::WRITE, ResponseType::NONE, 0, "Initiate trigger system."); }
                static SCPICommand ABORT() { return SCPICommand("ABORT", CommandType::WRITE, ResponseType::NONE, 0, "Abort trigger action."); }
                static SCPICommand SET_TRIGGER_SOURCE_BUS() {
                    return SCPICommand("TRIGGER:SOURCE BUS", CommandType::WRITE, ResponseType::NONE, 0, "Set trigger source to bus.");
                }
                static SCPICommand TRIGGER() { return SCPICommand("TRIGGER:IMMEDIATE", CommandType::WRITE, ResponseType::NONE, 0, "Generate a trigger."); }
                static SCPICommand SET_TRIGGERED_VOLTAGE() {
                    return SCPICommand("SOURCE:VOLTAGE:LEVEL:TRIGGERED:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0, "Set triggered voltage level.");
                }
                static SCPICommand GET_TRIGGERED_VOLTAGE() {
                    return SCPICommand("SOURCE:VOLTAGE:LEVEL:TRIGGERED:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get triggered voltage level.");
                }
                static SCPICommand SET_TRIGGERED_CURRENT() {
                    return SCPICommand("SOURCE:CURRENT:LEVEL:TRIGGERED:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0, "Set triggered current level.");
                }
                static SCPICommand GET_TRIGGERED_CURRENT() {
                    return SCPICommand("SOURCE:CURRENT:LEVEL:TRIGGERED:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get triggered current level.");
                }
            };
        };

        // --- Specialized Driver Aliases ---
        class Keysight664xA : public Agilent66xxA {};
        class Keysight665xA : public Agilent66xxA {};
        class Keysight667xA : public Agilent66xxA {};
        class Keysight668xA : public Agilent66xxA {};
        class Keysight669xA : public Agilent66xxA {};

        class HP664xA : public Agilent66xxA {};
        class HP665xA : public Agilent66xxA {};
        class HP667xA : public Agilent66xxA {};
        class HP668xA : public Agilent66xxA {};
        class HP669xA : public Agilent66xxA {};

    }    // namespace drivers
}    // namespace cvisa

#endif    // CVISA_DRIVER_AGILENT_66XXA_HPP
