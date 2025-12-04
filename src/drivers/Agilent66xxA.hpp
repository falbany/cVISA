#ifndef CVISA_DRIVER_AGILENT_66XXA_HPP
#define CVISA_DRIVER_AGILENT_66XXA_HPP

#include "../core/Command.hpp"
#include "../core/InstrumentDriver.hpp"

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
         * that return CommandSpec objects.
         */
        class Agilent6xxA : public InstrumentDriver {
          public:
            /**
             * @brief Default constructor. Creates a disconnected driver.
             */
            Agilent6xxA() : InstrumentDriver("Agilent/Keysight 66xxA Series Power Supply") {}

            /**
             * @brief Constructs and connects with resource name only.
             */
            explicit Agilent6xxA(const std::string& resourceName) : InstrumentDriver(resourceName, "Agilent/Keysight 66xxA Series Power Supply") {}

            /**
             * @brief Constructs and connects with timeout and read termination.
             */
            explicit Agilent6xxA(const std::string& resourceName, unsigned int timeout_ms, char read_termination)
                : InstrumentDriver(resourceName, timeout_ms, read_termination, "Agilent/Keysight 66xxA Series Power Supply") {}

            // --- Output Subsystem ---
            void   setVoltage(double voltage);
            double getVoltageSetting();
            double measureVoltage();
            void   setCurrent(double current);
            double getCurrentSetting();
            double measureCurrent();
            void   setOutput(bool enabled);
            bool   isOutputEnabled();
            void   clearProtection();

            // --- Over-Voltage Protection ---
            void   setOverVoltageProtection(double level);
            double getOverVoltageProtection();

            // --- Over-Current Protection ---
            void setOverCurrentProtection(bool enabled);
            bool isOverCurrentProtectionEnabled();

            // --- Display Subsystem ---
            void        setDisplayEnabled(bool enabled);
            bool        isDisplayEnabled();
            void        displayText(const std::string& text);
            std::string getDisplayText();

            // --- Trigger Subsystem ---
            void   initiate();
            void   abort();
            void   setTriggerSourceBus();
            void   trigger();
            void   setTriggeredVoltage(double voltage);
            double getTriggeredVoltage();
            void   setTriggeredCurrent(double current);
            double getTriggeredCurrent();

            // --- Command Definitions ---
            struct Commands {
                // --- Output Commands ---
                static CommandSpec SET_VOLTAGE() {
                    return CommandSpec("SOURCE:VOLTAGE:LEVEL:IMMEDIATE:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0,
                                       "Set output voltage.");
                }
                static CommandSpec GET_VOLTAGE_SET() {
                    return CommandSpec("SOURCE:VOLTAGE:LEVEL:IMMEDIATE:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0,
                                       "Get output voltage setting.");
                }
                static CommandSpec MEAS_VOLTAGE() {
                    return CommandSpec("MEASURE:VOLTAGE:DC?", CommandType::QUERY, ResponseType::DOUBLE, 50, "Measure voltage.");
                }
                static CommandSpec SET_CURRENT() {
                    return CommandSpec("SOURCE:CURRENT:LEVEL:IMMEDIATE:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0,
                                       "Set output current.");
                }
                static CommandSpec GET_CURRENT_SET() {
                    return CommandSpec("SOURCE:CURRENT:LEVEL:IMMEDIATE:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0,
                                       "Get output current setting.");
                }
                static CommandSpec MEAS_CURRENT() {
                    return CommandSpec("MEASURE:CURRENT:DC?", CommandType::QUERY, ResponseType::DOUBLE, 50, "Measure current.");
                }
                static CommandSpec SET_OUTPUT() {
                    return CommandSpec("OUTPUT:STATE %s", CommandType::WRITE, ResponseType::NONE, 0, "Set output state.");
                }
                static CommandSpec GET_OUTPUT_STATE() {
                    return CommandSpec("OUTPUT:STATE?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get output state.");
                }
                static CommandSpec CLEAR_PROTECTION() {
                    return CommandSpec("OUTPUT:PROTECTION:CLEAR", CommandType::WRITE, ResponseType::NONE, 0, "Clear tripped protection.");
                }

                // --- Over-Voltage Protection ---
                static CommandSpec SET_OVP() {
                    return CommandSpec("SOURCE:VOLTAGE:PROTECTION:LEVEL %f", CommandType::WRITE, ResponseType::NONE, 0, "Set OVP level.");
                }
                static CommandSpec GET_OVP() {
                    return CommandSpec("SOURCE:VOLTAGE:PROTECTION:LEVEL?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get OVP level.");
                }

                // --- Over-Current Protection ---
                static CommandSpec SET_OCP() {
                    return CommandSpec("SOURCE:CURRENT:PROTECTION:STATE %s", CommandType::WRITE, ResponseType::NONE, 0, "Set OCP state.");
                }
                static CommandSpec GET_OCP() {
                    return CommandSpec("SOURCE:CURRENT:PROTECTION:STATE?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get OCP state.");
                }

                // --- Display Commands ---
                static CommandSpec SET_DISPLAY_ENABLED() {
                    return CommandSpec("DISPLAY:WINDOW:STATE %s", CommandType::WRITE, ResponseType::NONE, 0, "Set display state.");
                }
                static CommandSpec GET_DISPLAY_ENABLED() {
                    return CommandSpec("DISPLAY:WINDOW:STATE?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get display state.");
                }
                static CommandSpec DISPLAY_TEXT() {
                    return CommandSpec("DISPLAY:WINDOW:TEXT:DATA \"%s\"", CommandType::WRITE, ResponseType::NONE, 0, "Display text.");
                }
                static CommandSpec GET_DISPLAY_TEXT() {
                    return CommandSpec("DISPLAY:WINDOW:TEXT:DATA?", CommandType::QUERY, ResponseType::STRING, 0, "Get displayed text.");
                }

                // --- Trigger Commands ---
                static CommandSpec INITIATE() {
                    return CommandSpec("INITIATE:IMMEDIATE", CommandType::WRITE, ResponseType::NONE, 0, "Initiate trigger system.");
                }
                static CommandSpec ABORT() { return CommandSpec("ABORT", CommandType::WRITE, ResponseType::NONE, 0, "Abort trigger action."); }
                static CommandSpec SET_TRIGGER_SOURCE_BUS() {
                    return CommandSpec("TRIGGER:SOURCE BUS", CommandType::WRITE, ResponseType::NONE, 0, "Set trigger source to bus.");
                }
                static CommandSpec TRIGGER() {
                    return CommandSpec("TRIGGER:IMMEDIATE", CommandType::WRITE, ResponseType::NONE, 0, "Generate a trigger.");
                }
                static CommandSpec SET_TRIGGERED_VOLTAGE() {
                    return CommandSpec("SOURCE:VOLTAGE:LEVEL:TRIGGERED:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0,
                                       "Set triggered voltage level.");
                }
                static CommandSpec GET_TRIGGERED_VOLTAGE() {
                    return CommandSpec("SOURCE:VOLTAGE:LEVEL:TRIGGERED:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0,
                                       "Get triggered voltage level.");
                }
                static CommandSpec SET_TRIGGERED_CURRENT() {
                    return CommandSpec("SOURCE:CURRENT:LEVEL:TRIGGERED:AMPLITUDE %f", CommandType::WRITE, ResponseType::NONE, 0,
                                       "Set triggered current level.");
                }
                static CommandSpec GET_TRIGGERED_CURRENT() {
                    return CommandSpec("SOURCE:CURRENT:LEVEL:TRIGGERED:AMPLITUDE?", CommandType::QUERY, ResponseType::DOUBLE, 0,
                                       "Get triggered current level.");
                }
            };
        };

    }    // namespace drivers
}    // namespace cvisa

#endif    // CVISA_DRIVER_AGILENT_66XXA_HPP
