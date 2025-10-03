#ifndef CVISA_DRIVER_AGILENT_66XXA_HPP
#define CVISA_DRIVER_AGILENT_66XXA_HPP

#include "../InstrumentDriver.hpp"
#include <string>

namespace cvisa {
namespace drivers {

/**
 * @class Agilent66xxA
 * @brief An instrument driver for the Agilent 66xxA series of power supplies.
 *
 * This driver implements the specific SCPI command set for the Agilent 66xxA
 * family of programmable power supplies. It provides a clear distinction
 * between setting a value, querying the setting, and measuring the actual
 * output, which is crucial for this type of instrument.
 */
class Agilent66xxA : public InstrumentDriver {
public:
    /**
     * @brief Constructs the Agilent66xxA driver.
     * @param instrument A connected VisaInstrument object.
     */
    explicit Agilent66xxA(VisaInstrument& instrument);

    // --- Voltage Controls ---
    void setVoltage(double voltage);
    double getVoltageSetting();
    double measureVoltage();

    // --- Current Controls ---
    void setCurrent(double current);
    double getCurrentSetting();
    double measureCurrent();

    // --- Output Controls ---
    void setOutput(bool enabled);
    bool isOutputEnabled();
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_DRIVER_AGILENT_66XXA_HPP