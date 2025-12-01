#ifndef CVISA_DRIVER_AGILENT_66XXA_HPP
#define CVISA_DRIVER_AGILENT_66XXA_HPP

#include <map>
#include <string>

#include "../Command.hpp"
#include "../InstrumentDriver.hpp"

namespace cvisa {
namespace drivers {

/**
 * @class Agilent66xxA
 * @brief An instrument driver for the Agilent 66xxA series of power supplies.
 *
 * This driver defines its command set as a public nested struct of static
 * constexpr CommandSpec objects. This provides compile-time safety and enables
 * IDE autocompletion for available commands.
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
    explicit Agilent66xxA(const std::string& resourceName)
        : InstrumentDriver(resourceName) {}

    /**
     * @brief Constructs and connects with timeout and read termination.
     */
    explicit Agilent66xxA(const std::string& resourceName,
                          unsigned int timeout_ms, char read_termination)
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

    // --- Command Definitions ---
    struct Commands {
        static constexpr CommandSpec SET_VOLTAGE = {"VOLT %f",
                                                    CommandType::WRITE};
        static constexpr CommandSpec GET_VOLTAGE_SET = {"VOLT?",
                                                        CommandType::QUERY};
        static constexpr CommandSpec MEAS_VOLTAGE = {"MEAS:VOLT?",
                                                     CommandType::QUERY, 50};
        static constexpr CommandSpec SET_CURRENT = {"CURR %f",
                                                    CommandType::WRITE};
        static constexpr CommandSpec GET_CURRENT_SET = {"CURR?",
                                                        CommandType::QUERY};
        static constexpr CommandSpec MEAS_CURRENT = {"MEAS:CURR?",
                                                     CommandType::QUERY, 50};
        static constexpr CommandSpec SET_OUTPUT = {"OUTP %s",
                                                   CommandType::WRITE};
        static constexpr CommandSpec GET_OUTPUT_STATE = {"OUTP?",
                                                         CommandType::QUERY};
    };
};

}  // namespace drivers
}  // namespace cvisa

#endif  // CVISA_DRIVER_AGILENT_66XXA_HPP
