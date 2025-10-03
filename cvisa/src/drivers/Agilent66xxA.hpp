#ifndef CVISA_DRIVER_AGILENT_66XXA_HPP
#define CVISA_DRIVER_AGILENT_66XXA_HPP

#include "../InstrumentDriver.hpp"
#include "../Command.hpp" // Include the new command definition header
#include <string>
#include <map>
#include <stdexcept>

namespace cvisa {
namespace drivers {

/**
 * @class Agilent66xxA
 * @brief An instrument driver for the Agilent 66xxA series of power supplies.
 *
 * This driver implements the specific SCPI command set for the Agilent 66xxA
 * family. It uses a declarative, data-driven approach by defining its
 * command set in a static registry, separating command definitions from their
 * execution logic.
 */
class Agilent66xxA : public InstrumentDriver {
public:
    explicit Agilent66xxA(VisaInstrument& instrument);

    // --- Public API (unchanged) ---
    void setVoltage(double voltage);
    double getVoltageSetting();
    double measureVoltage();

    void setCurrent(double current);
    double getCurrentSetting();
    double measureCurrent();

    void setOutput(bool enabled);
    bool isOutputEnabled();

private:
    // --- Command Execution ---

    /**
     * @brief Formats and executes a command from the registry.
     * @tparam Args Variadic arguments for formatting the command string.
     * @param commandName The key of the command in the registry.
     * @param args The arguments to be formatted into the command string.
     * @return The response from the instrument for QUERY commands.
     */
    template<typename... Args>
    std::string executeCommand(const std::string& commandName, Args... args);

    // --- Data-driven Command Definitions ---

    // The static registry that holds all SCPI command definitions for this driver.
    static const std::map<std::string, CommandSpec> s_commandRegistry;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_DRIVER_AGILENT_66XXA_HPP