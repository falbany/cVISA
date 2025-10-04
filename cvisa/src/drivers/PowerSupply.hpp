#ifndef CVISA_DRIVER_POWER_SUPPLY_HPP
#define CVISA_DRIVER_POWER_SUPPLY_HPP

#include "../InstrumentDriver.hpp"
#include "../Command.hpp"
#include <string>
#include <map>

namespace cvisa {
namespace drivers {

/**
 * @class PowerSupply
 * @brief An example instrument driver for a generic SCPI-controlled power supply.
 *
 * This class demonstrates how to build a high-level driver on top of the
 * InstrumentDriver base. It abstracts away the specific SCPI commands for
 * controlling a power supply into clean, readable methods.
 */
class PowerSupply : public InstrumentDriver {
public:
    /**
     * @brief Constructs the PowerSupply driver.
     * @param interface A connected I/O interface object.
     */
    explicit PowerSupply(IVisaIo& interface);

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

private:
    // The static command registry for the PowerSupply driver.
    static const std::map<std::string, CommandSpec> s_commandRegistry;

    // Helper to look up a command spec from the registry.
    const CommandSpec& getSpec(const std::string& commandName) const;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_DRIVER_POWER_SUPPLY_HPP