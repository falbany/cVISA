#ifndef CVISA_DRIVER_THERMAL_AIR_TA5000_HPP
#define CVISA_DRIVER_THERMAL_AIR_TA5000_HPP

#include <string>

#include "../core/Command.hpp"
#include "../core/InstrumentDriver.hpp"

namespace cvisa {
namespace drivers {

class ThermalAirTA5000 : public InstrumentDriver {
     public:
    ThermalAirTA5000() : InstrumentDriver("MPI Thermal TA-5000") {}

    explicit ThermalAirTA5000(const std::string& resourceName)
        : InstrumentDriver(resourceName, "MPI Thermal TA-5000") {}

    explicit ThermalAirTA5000(const std::string& resourceName,
                              unsigned int timeout_ms, char read_termination)
        : InstrumentDriver(resourceName, timeout_ms, read_termination,
                           "MPI Thermal TA-5000") {}

    // Public API
    double getTemperature();
    double getAirTemperature();
    double getDutTemperature();
    void setSetpoint(double temperature);
    double getSetpoint();
    void setSoakTime(int seconds);
    int getSoakTime();
    void setTemperatureWindow(double window);
    double getTemperatureWindow();
    void setHeadUp();
    void setHeadDown();
    int getHeadState();
    void setFlowOn();
    void setFlowOff();
    void setFlowRate(int scfm);
    int getFlowRateSetting();
    int getFlowRateMeasured();
    void setDutControlModeOn();
    void setDutControlModeOff();
    int getDutControlMode();
    void setDutSensorType(int type);
    int getDutSensorType();
    void setTrickleFlowOn();
    void setTrickleFlowOff();
    int getTrickleFlowState();
    void setLowerTemperatureLimit(double limit);
    void setUpperTemperatureLimit(double limit);
    int getErrorState();

    struct Commands {
        static CommandSpec getTemperature() {
            return CommandSpec("TEMP?", CommandType::QUERY,
                               ResponseType::DOUBLE, 0,
                               "Read main temperature.");
        }
        static CommandSpec getAirTemperature() {
            return CommandSpec("TMPA?", CommandType::QUERY,
                               ResponseType::DOUBLE, 0,
                               "Read air temperature.");
        }
        static CommandSpec getDutTemperature() {
            return CommandSpec("TMPD?", CommandType::QUERY,
                               ResponseType::DOUBLE, 0,
                               "Read DUT temperature.");
        }
        static CommandSpec setSetpoint() {
            return CommandSpec("SETP %f", CommandType::WRITE,
                               ResponseType::NONE, 0,
                               "Set temperature setpoint.");
        }
        static CommandSpec getSetpoint() {
            return CommandSpec("SETP?", CommandType::QUERY,
                               ResponseType::DOUBLE, 0,
                               "Read temperature setpoint.");
        }
        static CommandSpec setSoakTime() {
            return CommandSpec("SOAK %d", CommandType::WRITE,
                               ResponseType::NONE, 0, "Set soak time.");
        }
        static CommandSpec getSoakTime() {
            return CommandSpec("SOAK?", CommandType::QUERY,
                               ResponseType::INTEGER, 0, "Read soak time.");
        }
        static CommandSpec setTemperatureWindow() {
            return CommandSpec("WNDW %f", CommandType::WRITE,
                               ResponseType::NONE, 0,
                               "Set temperature window.");
        }
        static CommandSpec getTemperatureWindow() {
            return CommandSpec("WNDW?", CommandType::QUERY,
                               ResponseType::DOUBLE, 0,
                               "Read temperature window.");
        }
        static CommandSpec setHeadDown() {
            return CommandSpec("HEAD 1", CommandType::WRITE, ResponseType::NONE,
                               0, "Put thermal head down.");
        }
        static CommandSpec setHeadUp() {
            return CommandSpec("HEAD 0", CommandType::WRITE, ResponseType::NONE,
                               0, "Put thermal head up.");
        }
        static CommandSpec getHeadState() {
            return CommandSpec("HEAD?", CommandType::QUERY,
                               ResponseType::INTEGER, 0, "Read head state.");
        }
        static CommandSpec setFlowOn() {
            return CommandSpec("FLOW 1", CommandType::WRITE, ResponseType::NONE,
                               0, "Turn air flow ON.");
        }
        static CommandSpec setFlowOff() {
            return CommandSpec("FLOW 0", CommandType::WRITE, ResponseType::NONE,
                               0, "Turn air flow OFF.");
        }
        static CommandSpec setFlowRate() {
            return CommandSpec("FLSE %d", CommandType::WRITE,
                               ResponseType::NONE, 0, "Set air flow rate.");
        }
        static CommandSpec getFlowRateSetting() {
            return CommandSpec("FLSE?", CommandType::QUERY,
                               ResponseType::INTEGER, 0,
                               "Read air flow rate setting.");
        }
        static CommandSpec getFlowRateMeasured() {
            return CommandSpec("FLWR?", CommandType::QUERY,
                               ResponseType::INTEGER, 0,
                               "Read measured air flow rate.");
        }
        static CommandSpec setDutControlModeOn() {
            return CommandSpec("DUTM 1", CommandType::WRITE, ResponseType::NONE,
                               0, "Turn DUT control mode ON.");
        }
        static CommandSpec setDutControlModeOff() {
            return CommandSpec("DUTM 0", CommandType::WRITE, ResponseType::NONE,
                               0, "Turn AIR control mode ON.");
        }
        static CommandSpec getDutControlMode() {
            return CommandSpec("DUTM?", CommandType::QUERY,
                               ResponseType::INTEGER, 0,
                               "Read DUT mode state.");
        }
        static CommandSpec setDutSensorType() {
            return CommandSpec("DSNS %d", CommandType::WRITE,
                               ResponseType::NONE, 0, "Set DUT sensor type.");
        }
        static CommandSpec getDutSensorType() {
            return CommandSpec("DSNS?", CommandType::QUERY,
                               ResponseType::INTEGER, 0,
                               "Read DUT sensor type.");
        }
        static CommandSpec setTrickleFlowOn() {
            return CommandSpec("TRKL 1", CommandType::WRITE, ResponseType::NONE,
                               0, "Turn trickle flow ON.");
        }
        static CommandSpec setTrickleFlowOff() {
            return CommandSpec("TRKL 0", CommandType::WRITE, ResponseType::NONE,
                               0, "Turn trickle flow OFF.");
        }
        static CommandSpec getTrickleFlowState() {
            return CommandSpec("TRKL?", CommandType::QUERY,
                               ResponseType::INTEGER, 0,
                               "Read trickle flow setting.");
        }
        static CommandSpec setLowerTemperatureLimit() {
            return CommandSpec("LLIM %f", CommandType::WRITE,
                               ResponseType::NONE, 0,
                               "Set lower air temperature limit.");
        }
        static CommandSpec setUpperTemperatureLimit() {
            return CommandSpec("ULIM %f", CommandType::WRITE,
                               ResponseType::NONE, 0,
                               "Set upper air temperature limit.");
        }
        static CommandSpec getErrorState() {
            return CommandSpec("EROR?", CommandType::QUERY,
                               ResponseType::INTEGER, 0,
                               "Read system error state.");
        }
    };
};

}  // namespace drivers
}  // namespace cvisa

#endif  // CVISA_DRIVER_THERMAL_AIR_TA5000_HPP
