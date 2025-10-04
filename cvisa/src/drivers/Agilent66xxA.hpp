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
class Agilent66xxA : public InstrumentDriver {
public:
    /**
     * @brief Default constructor. Creates a disconnected driver.
     */
    Agilent66xxA() : InstrumentDriver() {}

    /**
     * @brief Constructs and connects with resource name only.
     */
    explicit Agilent66xxA(const std::string& resourceName) : InstrumentDriver(resourceName) {}

    /**
     * @brief Constructs and connects with timeout and read termination.
     */
    explicit Agilent66xxA(const std::string& resourceName, unsigned int timeout_ms, char read_termination)
        : InstrumentDriver(resourceName, timeout_ms, read_termination) {}


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