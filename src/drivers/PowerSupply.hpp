#ifndef CVISA_DRIVER_POWER_SUPPLY_HPP
#define CVISA_DRIVER_POWER_SUPPLY_HPP

#include "../core/SCPIBase.hpp"
#include "../core/SCPICommand.hpp"

#include <map>
#include <string>

namespace cvisa {
    namespace drivers {

        /**
         * @class PowerSupply
         * @brief An example instrument driver for a generic SCPI-controlled power
         * supply.
         *
         * This class demonstrates how to build a high-level driver on top of the
         * SCPIBase base. It abstracts away the specific SCPI commands for
         * controlling a power supply into clean, readable methods.
         */
        class PowerSupply : public SCPIBase {
          public:
            /**
             * @brief Default constructor. Creates a disconnected driver.
             */
            PowerSupply() : SCPIBase() { m_description = "Generic Power Supply"; }

            /**
             * @brief Constructs and connects with resource name only.
             */
            explicit PowerSupply(const std::string& resourceName) : SCPIBase(resourceName) { m_description = "Generic Power Supply"; }

            /**
             * @brief Constructs and connects with timeout and read termination.
             */
            explicit PowerSupply(const std::string& resourceName, unsigned int timeout_ms, char read_termination) : SCPIBase(resourceName, timeout_ms, read_termination) {
                m_description = "Generic Power Supply";
            }

            /**
             * @brief Sets the output voltage.
             * @param voltage The desired voltage level in Volts.
             */
            void setVoltage(double voltage);

            /**
             * @brief Sets the output current limit.
             * @param current The desired current limit in Amperes.
             */
            void setCurrent(double current);

            /**
             * @brief Queries the configured output voltage.
             * @return The measured voltage in Volts.
             */
            double getVoltage();

            /**
             * @brief Queries the measured output current.
             * @return The measured current in Amperes.
             */
            double getCurrent();

            /**
             * @brief Enables or disables the power supply's output.
             * @param enabled Set to true to turn the output on, false to turn it off.
             */
            void setOutput(bool enabled);

            /**
             * @brief Queries the state of the output.
             * @return True if the output is on, false otherwise.
             */
            bool isOutputEnabled();

            // --- Command Definitions ---
            struct Commands {
                static SCPICommand SET_VOLTAGE() { return SCPICommand("VOLT %f", CommandType::WRITE, ResponseType::NONE, 0, "Set output voltage."); }
                static SCPICommand GET_VOLTAGE() { return SCPICommand("VOLT?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get output voltage."); }
                static SCPICommand SET_CURRENT() { return SCPICommand("CURR %f", CommandType::WRITE, ResponseType::NONE, 0, "Set output current."); }
                static SCPICommand GET_CURRENT() { return SCPICommand("CURR?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get output current."); }
                static SCPICommand SET_OUTPUT() { return SCPICommand("OUTP %d", CommandType::WRITE, ResponseType::NONE, 0, "Set output state."); }
                static SCPICommand GET_OUTPUT() { return SCPICommand("OUTP?", CommandType::QUERY, ResponseType::BOOLEAN, 0, "Get output state."); }
            };
        };

    }    // namespace drivers
}    // namespace cvisa

#endif    // CVISA_DRIVER_POWER_SUPPLY_HPP
