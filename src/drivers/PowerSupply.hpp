#ifndef CVISA_DRIVER_POWER_SUPPLY_HPP
#define CVISA_DRIVER_POWER_SUPPLY_HPP

#include <map>
#include <string>

#include "../core/Command.hpp"
#include "../core/InstrumentDriver.hpp"

namespace cvisa {
namespace drivers {

/**
 * @class PowerSupply
 * @brief An example instrument driver for a generic SCPI-controlled power
 * supply.
 *
 * This class demonstrates how to build a high-level driver on top of the
 * InstrumentDriver base. It abstracts away the specific SCPI commands for
 * controlling a power supply into clean, readable methods.
 */
class PowerSupply : public InstrumentDriver {
     public:
    /**
     * @brief Default constructor. Creates a disconnected driver.
     */
    PowerSupply() : InstrumentDriver() {}

    /**
     * @brief Constructs and connects with resource name only.
     */
    explicit PowerSupply(const std::string& resourceName)
        : InstrumentDriver(resourceName) {}

    /**
     * @brief Constructs and connects with timeout and read termination.
     */
    explicit PowerSupply(const std::string& resourceName,
                         unsigned int timeout_ms, char read_termination)
        : InstrumentDriver(resourceName, timeout_ms, read_termination) {}

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
        static CommandSpec SET_VOLTAGE() {
            return CommandSpec("VOLT %f", CommandType::WRITE);
        }
        static CommandSpec GET_VOLTAGE() {
            return CommandSpec("VOLT?", CommandType::QUERY,
                               ResponseType::DOUBLE);
        }
        static CommandSpec SET_CURRENT() {
            return CommandSpec("CURR %f", CommandType::WRITE);
        }
        static CommandSpec GET_CURRENT() {
            return CommandSpec("CURR?", CommandType::QUERY,
                               ResponseType::DOUBLE);
        }
        static CommandSpec SET_OUTPUT() {
            return CommandSpec("OUTP %d", CommandType::WRITE);
        }
        static CommandSpec GET_OUTPUT() {
            return CommandSpec("OUTP?", CommandType::QUERY,
                               ResponseType::BOOLEAN);
        }
    };
};

}  // namespace drivers
}  // namespace cvisa

#endif  // CVISA_DRIVER_POWER_SUPPLY_HPP
