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
 * @brief An instrument driver for the Agilent 66xxA series of power supplies.
 *
 * This driver defines its command set as a public nested struct of static
 * methods that return CommandSpec objects. This provides compile-time safety
 * and enables IDE autocompletion for available commands in a C++11 compliant
 * way.
 */
        class Agilent66xxA : public InstrumentDriver {
          public:
            /**
     * @brief Default constructor. Creates a disconnected driver.
     */
            Agilent66xxA() : InstrumentDriver("Agilent 66xxA Series Power Supply") {}

            /**
     * @brief Constructs and connects with resource name only.
     */
            explicit Agilent66xxA(const std::string& resourceName) : InstrumentDriver(resourceName, "Agilent 66xxA Series Power Supply") {}

            /**
     * @brief Constructs and connects with timeout and read termination.
     */
            explicit Agilent66xxA(const std::string& resourceName, unsigned int timeout_ms, char read_termination)
                : InstrumentDriver(resourceName, timeout_ms, read_termination, "Agilent 66xxA Series Power Supply") {}

            // --- Public API ---
            void   setVoltage(double voltage);
            double getVoltageSetting();
            double measureVoltage();

            void   setCurrent(double current);
            double getCurrentSetting();
            double measureCurrent();

            void setOutput(bool enabled);
            bool isOutputEnabled();

            // --- Command Definitions ---
            struct Commands {
                static CommandSpec SET_VOLTAGE() { return CommandSpec("VOLT %f", CommandType::WRITE, ResponseType::NONE, 0, "Set output voltage."); }
                static CommandSpec GET_VOLTAGE_SET() {
                    return CommandSpec("VOLT?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get output voltage setting.");
                }
                static CommandSpec MEAS_VOLTAGE() {
                    return CommandSpec("MEAS:VOLT?", CommandType::QUERY, ResponseType::DOUBLE, 50, "Measure voltage.");
                }
                static CommandSpec SET_CURRENT() { return CommandSpec("CURR %f", CommandType::WRITE, ResponseType::NONE, 0, "Set output current."); }
                static CommandSpec GET_CURRENT_SET() {
                    return CommandSpec("CURR?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get output current setting.");
                }
                static CommandSpec MEAS_CURRENT() {
                    return CommandSpec("MEAS:CURR?", CommandType::QUERY, ResponseType::DOUBLE, 50, "Measure current.");
                }
                static CommandSpec SET_OUTPUT() { return CommandSpec("OUTP %s", CommandType::WRITE, ResponseType::NONE, 0, "Set output state."); }
                static CommandSpec GET_OUTPUT_STATE() {
                    return CommandSpec("OUTP?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get output state.");
                }
            };
        };

    }    // namespace drivers
}    // namespace cvisa

#endif    // CVISA_DRIVER_AGILENT_66XXA_HPP
