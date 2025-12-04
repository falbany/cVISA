#ifndef CVISA_DRIVER_THERMAL_AIR_TA5000_HPP
#define CVISA_DRIVER_THERMAL_AIR_TA5000_HPP

#include "../core/Command.hpp"
#include "../core/InstrumentDriver.hpp"

#include <string>

namespace cvisa {
    namespace drivers {

        /**
 * @class ThermalAirTA5000
 * @brief An instrument driver for the MPI Thermal TA-5000 thermal air stream
 * system.
 *
 * This driver provides a high-level C++ interface for controlling the TA-5000,
 * which is used for temperature testing and characterization of electronic
 * components over a range of -80°C to +225°C.
 */
        class ThermalAirTA5000 : public InstrumentDriver {
          public:
            /**
     * @brief Default constructor. Creates a disconnected driver.
     */
            ThermalAirTA5000() : InstrumentDriver("MPI Thermal TA-5000") {}

            /**
     * @brief Constructs and connects with a VISA resource name.
     * @param resourceName The VISA resource name (e.g., "GPIB0::12::INSTR").
     */
            explicit ThermalAirTA5000(const std::string& resourceName) : InstrumentDriver(resourceName, "MPI Thermal TA-5000") {}

            /**
     * @brief Constructs and connects with full VISA parameters.
     * @param resourceName The VISA resource name.
     * @param timeout_ms The communication timeout in milliseconds.
     * @param read_termination The character to terminate reads.
     */
            explicit ThermalAirTA5000(const std::string& resourceName, unsigned int timeout_ms, char read_termination)
                : InstrumentDriver(resourceName, timeout_ms, read_termination, "MPI Thermal TA-5000") {}

            // Public API
            /**
     * @brief Reads the main temperature.
     * @return The temperature in degrees Celsius.
     */
            double getTemperature();

            /**
     * @brief Reads the air temperature.
     * @return The air temperature in degrees Celsius.
     */
            double getAirTemperature();

            /**
     * @brief Reads the DUT temperature.
     * @return The DUT temperature in degrees Celsius.
     */
            double getDutTemperature();

            /**
     * @brief Sets the temperature setpoint.
     * @param temperature The desired temperature in degrees Celsius.
     */
            void setSetpoint(double temperature);

            /**
     * @brief Reads the current temperature setpoint.
     * @return The setpoint in degrees Celsius.
     */
            double getSetpoint();

            /**
     * @brief Sets the soak time.
     * @param seconds The soak time in seconds.
     */
            void setSoakTime(int seconds);

            /**
     * @brief Reads the soak time.
     * @return The soak time in seconds.
     */
            int getSoakTime();

            /**
     * @brief Sets the temperature window.
     * @param window The temperature window in degrees Celsius.
     */
            void setTemperatureWindow(double window);

            /**
     * @brief Reads the temperature window.
     * @return The temperature window in degrees Celsius.
     */
            double getTemperatureWindow();

            /**
     * @brief Puts the thermal head up.
     */
            void setHeadUp();

            /**
     * @brief Puts the thermal head down.
     */
            void setHeadDown();

            /**
     * @brief Reads the up/down state of the test head.
     * @return 1 for up, 0 for down.
     */
            int getHeadState();

            /**
     * @brief Turns the main nozzle air flow ON.
     */
            void setFlowOn();

            /**
     * @brief Turns the main nozzle air flow OFF.
     */
            void setFlowOff();

            /**
     * @brief Sets the main nozzle air flow rate.
     * @param scfm The flow rate in scfm (4-25).
     */
            void setFlowRate(int scfm);

            /**
     * @brief Reads the desired main nozzle air flow rate setting.
     * @return The flow rate setting in scfm.
     */
            int getFlowRateSetting();

            /**
     * @brief Reads the measured main nozzle air flow rate.
     * @return The measured flow rate in scfm.
     */
            int getFlowRateMeasured();

            /**
     * @brief Reads the measured main nozzle flow rate in liters/min.
     * @return The measured flow rate in l/min.
     */
            double getFlowRateLitersPerMin();

            /**
     * @brief Turns DUT control mode ON.
     */
            void setDutControlModeOn();

            /**
     * @brief Turns AIR control mode ON (by turning DUT mode OFF).
     */
            void setDutControlModeOff();

            /**
     * @brief Reads the DUT mode ON/OFF state.
     * @return 1 for ON, 0 for OFF.
     */
            int getDutControlMode();

            /**
     * @brief Sets the DUT sensor type.
     * @param type The sensor type (0-4).
     */
            void setDutSensorType(int type);

            /**
     * @brief Reads the DUT sensor type.
     * @return The sensor type (0-4).
     */
            int getDutSensorType();

            /**
     * @brief Turns trickle flow ON.
     */
            void setTrickleFlowOn();

            /**
     * @brief Turns trickle flow OFF.
     */
            void setTrickleFlowOff();

            /**
     * @brief Reads the setting of trickle flow.
     * @return 1 for ON, 0 for OFF.
     */
            int getTrickleFlowState();

            /**
     * @brief Sets the lower air temperature limit.
     * @param limit The lower limit in degrees Celsius.
     */
            void setLowerTemperatureLimit(double limit);

            /**
     * @brief Gets the lower air temperature limit.
     * @return The lower limit in degrees Celsius.
     */
            double getLowerTemperatureLimit();

            /**
     * @brief Sets the upper air temperature limit.
     * @param limit The upper limit in degrees Celsius.
     */
            void setUpperTemperatureLimit(int limit);

            /**
     * @brief Gets the upper air temperature limit.
     * @return The upper limit in degrees Celsius.
     */
            int getUpperTemperatureLimit();

            /**
     * @brief Reads the system error state.
     * @return A bit-masked integer representing the error state.
     */
            int getErrorState();

            /**
     * @brief Sets the air-to-DUT maximum temperature difference.
     * @param difference The maximum difference in degrees Celsius (10-300).
     */
            void setAirToDutMaxDifference(int difference);

            /**
     * @brief Reads the air-to-DUT maximum temperature difference.
     * @return The maximum difference in degrees Celsius.
     */
            int getAirToDutMaxDifference();

            /**
     * @brief Reads the auxiliary condition data.
     * @return A bit-masked integer representing the auxiliary status.
     */
            int getAuxiliaryCondition();

            /**
     * @brief Turns the compressor on.
     */
            void setCompressorOn();

            /**
     * @brief Turns the compressor off.
     */
            void setCompressorOff();

            /**
     * @brief Reads the compressor on/off state.
     * @return 1 for ON, 0 for OFF.
     */
            int getCompressorState();

            /**
     * @brief Sets the cycle count.
     * @param count The number of cycles (1-999).
     */
            void setCycleCount(int count);

            /**
     * @brief Reads the cycle count.
     * @return The number of cycles.
     */
            int getCycleCount();

            /**
     * @brief Starts the temperature cycling function.
     */
            void startCycling();

            /**
     * @brief Stops the temperature cycling function.
     */
            void stopCycling();

            /**
     * @brief Reads the current cycling start/stop state.
     * @return 1 for started, 0 for stopped.
     */
            int getCyclingState();

            /**
     * @brief Sets the DUT auto tune mode.
     * @param mode 0=off, 1=on, 2=hold.
     */
            void setDutAutoTuneMode(int mode);

            /**
     * @brief Reads the DUT auto tune mode.
     * @return The auto tune mode (0, 1, or 2).
     */
            int getDutAutoTuneMode();

            /**
     * @brief Locks the test head in its current position.
     */
            void lockHead();

            /**
     * @brief Unlocks the test head.
     */
            void unlockHead();

            /**
     * @brief Steps to the next setpoint during temperature cycling.
     */
            void nextSetpoint();

            /**
     * @brief Sets the ramp rate.
     * @param rate The ramp rate in degrees Celsius per minute.
     */
            void setRampRate(double rate);

            /**
     * @brief Reads the ramp rate.
     * @return The ramp rate in degrees Celsius per minute.
     */
            double getRampRate();

            /**
     * @brief Reads the dynamic temperature setpoint.
     * @return The dynamic setpoint in degrees Celsius.
     */
            double getDynamicSetpoint();

            /**
     * @brief Selects a setpoint to be the current setpoint.
     * @param setpointIndex 0=hot, 1=ambient, 2=cold.
     */
            void selectSetpoint(int setpointIndex);

            /**
     * @brief Reads the current setpoint number.
     * @return The current setpoint number.
     */
            int getSelectedSetpoint();

            /**
     * @brief Reads the temperature event condition register.
     * @return A bit-masked integer.
     */
            int getTemperatureEventCondition();

            /**
     * @brief Sets the maximum allowable test time.
     * @param ms The maximum time in milliseconds.
     */
            void setMaxTestTime(int ms);

            /**
     * @brief Reads the maximum allowable test time.
     * @return The maximum time in milliseconds.
     */
            int getMaxTestTime();

            struct Commands {
                static CommandSpec getTemperature() {
                    return CommandSpec("TEMP?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Read main temperature.");
                }
                static CommandSpec getAirTemperature() {
                    return CommandSpec("TMPA?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Read air temperature.");
                }
                static CommandSpec getDutTemperature() {
                    return CommandSpec("TMPD?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Read DUT temperature.");
                }
                static CommandSpec setSetpoint() {
                    return CommandSpec("SETP %f", CommandType::WRITE, ResponseType::NONE, 0, "Set temperature setpoint.");
                }
                static CommandSpec getSetpoint() {
                    return CommandSpec("SETP?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Read temperature setpoint.");
                }
                static CommandSpec setSoakTime() { return CommandSpec("SOAK %d", CommandType::WRITE, ResponseType::NONE, 0, "Set soak time."); }
                static CommandSpec getSoakTime() { return CommandSpec("SOAK?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read soak time."); }
                static CommandSpec setTemperatureWindow() {
                    return CommandSpec("WNDW %f", CommandType::WRITE, ResponseType::NONE, 0, "Set temperature window.");
                }
                static CommandSpec getTemperatureWindow() {
                    return CommandSpec("WNDW?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Read temperature window.");
                }
                static CommandSpec setHeadDown() {
                    return CommandSpec("HEAD 1", CommandType::WRITE, ResponseType::NONE, 0, "Put thermal head down.");
                }
                static CommandSpec setHeadUp() { return CommandSpec("HEAD 0", CommandType::WRITE, ResponseType::NONE, 0, "Put thermal head up."); }
                static CommandSpec getHeadState() { return CommandSpec("HEAD?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read head state."); }
                static CommandSpec setFlowOn() { return CommandSpec("FLOW 1", CommandType::WRITE, ResponseType::NONE, 0, "Turn air flow ON."); }
                static CommandSpec setFlowOff() { return CommandSpec("FLOW 0", CommandType::WRITE, ResponseType::NONE, 0, "Turn air flow OFF."); }
                static CommandSpec setFlowRate() { return CommandSpec("FLSE %d", CommandType::WRITE, ResponseType::NONE, 0, "Set air flow rate."); }
                static CommandSpec getFlowRateSetting() {
                    return CommandSpec("FLSE?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read air flow rate setting.");
                }
                static CommandSpec getFlowRateMeasured() {
                    return CommandSpec("FLWR?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read measured air flow rate.");
                }
                static CommandSpec getFlowRateLitersPerMin() {
                    return CommandSpec("FLRL?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Read measured flow rate in l/min.");
                }
                static CommandSpec setDutControlModeOn() {
                    return CommandSpec("DUTM 1", CommandType::WRITE, ResponseType::NONE, 0, "Turn DUT control mode ON.");
                }
                static CommandSpec setDutControlModeOff() {
                    return CommandSpec("DUTM 0", CommandType::WRITE, ResponseType::NONE, 0, "Turn AIR control mode ON.");
                }
                static CommandSpec getDutControlMode() {
                    return CommandSpec("DUTM?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read DUT mode state.");
                }
                static CommandSpec setDutSensorType() {
                    return CommandSpec("DSNS %d", CommandType::WRITE, ResponseType::NONE, 0, "Set DUT sensor type.");
                }
                static CommandSpec getDutSensorType() {
                    return CommandSpec("DSNS?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read DUT sensor type.");
                }
                static CommandSpec setTrickleFlowOn() {
                    return CommandSpec("TRKL 1", CommandType::WRITE, ResponseType::NONE, 0, "Turn trickle flow ON.");
                }
                static CommandSpec setTrickleFlowOff() {
                    return CommandSpec("TRKL 0", CommandType::WRITE, ResponseType::NONE, 0, "Turn trickle flow OFF.");
                }
                static CommandSpec getTrickleFlowState() {
                    return CommandSpec("TRKL?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read trickle flow setting.");
                }
                static CommandSpec setLowerTemperatureLimit() {
                    return CommandSpec("LLIM %f", CommandType::WRITE, ResponseType::NONE, 0, "Set lower air temperature limit.");
                }
                static CommandSpec getLowerTemperatureLimit() {
                    return CommandSpec("LLIM?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get lower air temperature limit.");
                }
                static CommandSpec setUpperTemperatureLimit() {
                    return CommandSpec("ULIM %d", CommandType::WRITE, ResponseType::NONE, 0, "Set upper air temperature limit.");
                }
                static CommandSpec getUpperTemperatureLimit() {
                    return CommandSpec("ULIM?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get upper air temperature limit.");
                }
                static CommandSpec getErrorState() {
                    return CommandSpec("EROR?", CommandType::QUERY, ResponseType::INTEGER, 0, "Read system error state.");
                }
                static CommandSpec setAirToDutMaxDifference() {
                    return CommandSpec("ADMD %d", CommandType::WRITE, ResponseType::NONE, 0, "Set air-to-DUT max difference.");
                }
                static CommandSpec getAirToDutMaxDifference() {
                    return CommandSpec("ADMD?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get air-to-DUT max difference.");
                }
                static CommandSpec getAuxiliaryCondition() {
                    return CommandSpec("AUXC?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get auxiliary condition data.");
                }
                static CommandSpec setCompressorOn() {
                    return CommandSpec("COOL 1", CommandType::WRITE, ResponseType::NONE, 0, "Turn compressor on.");
                }
                static CommandSpec setCompressorOff() {
                    return CommandSpec("COOL 0", CommandType::WRITE, ResponseType::NONE, 0, "Turn compressor off.");
                }
                static CommandSpec getCompressorState() {
                    return CommandSpec("COOL?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get compressor state.");
                }
                static CommandSpec setCycleCount() { return CommandSpec("CYCC %d", CommandType::WRITE, ResponseType::NONE, 0, "Set cycle count."); }
                static CommandSpec getCycleCount() { return CommandSpec("CYCC?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get cycle count."); }
                static CommandSpec startCycling() { return CommandSpec("CYCL 1", CommandType::WRITE, ResponseType::NONE, 0, "Start cycling."); }
                static CommandSpec stopCycling() { return CommandSpec("CYCL 0", CommandType::WRITE, ResponseType::NONE, 0, "Stop cycling."); }
                static CommandSpec getCyclingState() {
                    return CommandSpec("CYCP?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get cycling state.");
                }
                static CommandSpec setDutAutoTuneMode() {
                    return CommandSpec("DUTN %d", CommandType::WRITE, ResponseType::NONE, 0, "Set DUT auto tune mode.");
                }
                static CommandSpec getDutAutoTuneMode() {
                    return CommandSpec("DUTN?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get DUT auto tune mode.");
                }
                static CommandSpec lockHead() { return CommandSpec("HDLK 1", CommandType::WRITE, ResponseType::NONE, 0, "Lock test head."); }
                static CommandSpec unlockHead() { return CommandSpec("HDLK 0", CommandType::WRITE, ResponseType::NONE, 0, "Unlock test head."); }
                static CommandSpec nextSetpoint() { return CommandSpec("NEXT", CommandType::WRITE, ResponseType::NONE, 0, "Step to next setpoint."); }
                static CommandSpec setRampRate() { return CommandSpec("RAMP %f", CommandType::WRITE, ResponseType::NONE, 0, "Set ramp rate."); }
                static CommandSpec getRampRate() { return CommandSpec("RAMP?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get ramp rate."); }
                static CommandSpec getDynamicSetpoint() {
                    return CommandSpec("SETD?", CommandType::QUERY, ResponseType::DOUBLE, 0, "Get dynamic setpoint.");
                }
                static CommandSpec selectSetpoint() { return CommandSpec("SETN %d", CommandType::WRITE, ResponseType::NONE, 0, "Select setpoint."); }
                static CommandSpec getSelectedSetpoint() {
                    return CommandSpec("SETN?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get selected setpoint.");
                }
                static CommandSpec getTemperatureEventCondition() {
                    return CommandSpec("TECR?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get temperature event condition.");
                }
                static CommandSpec setMaxTestTime() {
                    return CommandSpec("TTIM %d", CommandType::WRITE, ResponseType::NONE, 0, "Set max test time.");
                }
                static CommandSpec getMaxTestTime() {
                    return CommandSpec("TTIM?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get max test time.");
                }
            };
        };

    }    // namespace drivers
}    // namespace cvisa

#endif    // CVISA_DRIVER_THERMAL_AIR_TA5000_HPP
