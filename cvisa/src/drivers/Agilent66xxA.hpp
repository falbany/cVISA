#ifndef CVISA_DRIVER_AGILENT_66XXA_HPP
#define CVISA_DRIVER_AGILENT_66XXA_HPP

#include "../InstrumentDriver.hpp"
#include "../Command.hpp"
#include <string>
#include <map>

namespace cvisa {
namespace drivers {

/**
 * @class Agilent66xxA
 * @brief An instrument driver for the Agilent 66xxA series of power supplies.
 *
 * This driver uses a declarative, data-driven approach by defining its
 * command set in a static registry. It inherits its command execution logic
 * from the InstrumentDriver base class, promoting code reuse.
 */
#include <optional>

class Agilent66xxA : public InstrumentDriver {
public:
    /**
     * @brief Constructs the driver and opens a VISA session.
     * @param resourceName The VISA resource string.
     * @param timeout_ms Optional timeout in milliseconds.
     * @param read_termination Optional read termination character.
     * @param write_termination Optional write termination character.
     */
    explicit Agilent66xxA(const std::string& resourceName,
                          std::optional<unsigned int> timeout_ms = std::nullopt,
                          std::optional<char> read_termination = std::nullopt,
                          std::optional<char> write_termination = std::nullopt);

    // --- Public API ---
    void setVoltage(double voltage);
    double getVoltageSetting();
    double measureVoltage();

    void setCurrent(double current);
    double getCurrentSetting();
    double measureCurrent();

    void setOutput(bool enabled);
    bool isOutputEnabled();

private:
    // --- Data-driven Command Definitions ---
    static const std::map<std::string, CommandSpec> s_commandRegistry;

    // Helper function to look up a command spec from the registry.
    const CommandSpec& getSpec(const std::string& commandName) const;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_DRIVER_AGILENT_66XXA_HPP