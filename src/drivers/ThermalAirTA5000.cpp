#include "ThermalAirTA5000.hpp"

namespace cvisa {
    namespace drivers {

        double ThermalAirTA5000::getTemperature() { return queryAndParse<double>(Commands::getTemperature()); }

        double ThermalAirTA5000::getAirTemperature() { return queryAndParse<double>(Commands::getAirTemperature()); }

        double ThermalAirTA5000::getDutTemperature() { return queryAndParse<double>(Commands::getDutTemperature()); }

        void ThermalAirTA5000::setSetpoint(double temperature) { executeCommand(Commands::setSetpoint(), temperature); }

        double ThermalAirTA5000::getSetpoint() { return queryAndParse<double>(Commands::getSetpoint()); }

        void ThermalAirTA5000::setSoakTime(int seconds) { executeCommand(Commands::setSoakTime(), seconds); }

        int ThermalAirTA5000::getSoakTime() { return queryAndParse<int>(Commands::getSoakTime()); }

        void ThermalAirTA5000::setTemperatureWindow(double window) { executeCommand(Commands::setTemperatureWindow(), window); }

        double ThermalAirTA5000::getTemperatureWindow() { return queryAndParse<double>(Commands::getTemperatureWindow()); }

        void ThermalAirTA5000::setHeadUp() { executeCommand(Commands::setHeadUp()); }

        void ThermalAirTA5000::setHeadDown() { executeCommand(Commands::setHeadDown()); }

        int ThermalAirTA5000::getHeadState() { return queryAndParse<int>(Commands::getHeadState()); }

        void ThermalAirTA5000::setFlowOn() { executeCommand(Commands::setFlowOn()); }

        void ThermalAirTA5000::setFlowOff() { executeCommand(Commands::setFlowOff()); }

        void ThermalAirTA5000::setFlowRate(int scfm) { executeCommand(Commands::setFlowRate(), scfm); }

        int ThermalAirTA5000::getFlowRateSetting() { return queryAndParse<int>(Commands::getFlowRateSetting()); }

        int ThermalAirTA5000::getFlowRateMeasured() { return queryAndParse<int>(Commands::getFlowRateMeasured()); }

        double ThermalAirTA5000::getFlowRateLitersPerMin() { return queryAndParse<double>(Commands::getFlowRateLitersPerMin()); }

        void ThermalAirTA5000::setDutControlModeOn() { executeCommand(Commands::setDutControlModeOn()); }

        void ThermalAirTA5000::setDutControlModeOff() { executeCommand(Commands::setDutControlModeOff()); }

        int ThermalAirTA5000::getDutControlMode() { return queryAndParse<int>(Commands::getDutControlMode()); }

        void ThermalAirTA5000::setDutSensorType(int type) { executeCommand(Commands::setDutSensorType(), type); }

        int ThermalAirTA5000::getDutSensorType() { return queryAndParse<int>(Commands::getDutSensorType()); }

        void ThermalAirTA5000::setTrickleFlowOn() { executeCommand(Commands::setTrickleFlowOn()); }

        void ThermalAirTA5000::setTrickleFlowOff() { executeCommand(Commands::setTrickleFlowOff()); }

        int ThermalAirTA5000::getTrickleFlowState() { return queryAndParse<int>(Commands::getTrickleFlowState()); }

        void ThermalAirTA5000::setLowerTemperatureLimit(double limit) { executeCommand(Commands::setLowerTemperatureLimit(), limit); }

        double ThermalAirTA5000::getLowerTemperatureLimit() { return queryAndParse<double>(Commands::getLowerTemperatureLimit()); }

        void ThermalAirTA5000::setUpperTemperatureLimit(int limit) { executeCommand(Commands::setUpperTemperatureLimit(), limit); }

        int ThermalAirTA5000::getUpperTemperatureLimit() { return queryAndParse<int>(Commands::getUpperTemperatureLimit()); }

        int ThermalAirTA5000::getErrorState() { return queryAndParse<int>(Commands::getErrorState()); }

        void ThermalAirTA5000::setAirToDutMaxDifference(int difference) { executeCommand(Commands::setAirToDutMaxDifference(), difference); }

        int ThermalAirTA5000::getAirToDutMaxDifference() { return queryAndParse<int>(Commands::getAirToDutMaxDifference()); }

        int ThermalAirTA5000::getAuxiliaryCondition() { return queryAndParse<int>(Commands::getAuxiliaryCondition()); }

        void ThermalAirTA5000::setCompressorOn() { executeCommand(Commands::setCompressorOn()); }

        void ThermalAirTA5000::setCompressorOff() { executeCommand(Commands::setCompressorOff()); }

        int ThermalAirTA5000::getCompressorState() { return queryAndParse<int>(Commands::getCompressorState()); }

        void ThermalAirTA5000::setCycleCount(int count) { executeCommand(Commands::setCycleCount(), count); }

        int ThermalAirTA5000::getCycleCount() { return queryAndParse<int>(Commands::getCycleCount()); }

        void ThermalAirTA5000::startCycling() { executeCommand(Commands::startCycling()); }

        void ThermalAirTA5000::stopCycling() { executeCommand(Commands::stopCycling()); }

        int ThermalAirTA5000::getCyclingState() { return queryAndParse<int>(Commands::getCyclingState()); }

        void ThermalAirTA5000::setDutAutoTuneMode(int mode) { executeCommand(Commands::setDutAutoTuneMode(), mode); }

        int ThermalAirTA5000::getDutAutoTuneMode() { return queryAndParse<int>(Commands::getDutAutoTuneMode()); }

        void ThermalAirTA5000::lockHead() { executeCommand(Commands::lockHead()); }

        void ThermalAirTA5000::unlockHead() { executeCommand(Commands::unlockHead()); }

        void ThermalAirTA5000::nextSetpoint() { executeCommand(Commands::nextSetpoint()); }

        void ThermalAirTA5000::setRampRate(double rate) { executeCommand(Commands::setRampRate(), rate); }

        double ThermalAirTA5000::getRampRate() { return queryAndParse<double>(Commands::getRampRate()); }

        double ThermalAirTA5000::getDynamicSetpoint() { return queryAndParse<double>(Commands::getDynamicSetpoint()); }

        void ThermalAirTA5000::selectSetpoint(int setpointIndex) { executeCommand(Commands::selectSetpoint(), setpointIndex); }

        int ThermalAirTA5000::getSelectedSetpoint() { return queryAndParse<int>(Commands::getSelectedSetpoint()); }

        int ThermalAirTA5000::getTemperatureEventCondition() { return queryAndParse<int>(Commands::getTemperatureEventCondition()); }

        void ThermalAirTA5000::setMaxTestTime(int ms) { executeCommand(Commands::setMaxTestTime(), ms); }

        int ThermalAirTA5000::getMaxTestTime() { return queryAndParse<int>(Commands::getMaxTestTime()); }

    }    // namespace drivers
}    // namespace cvisa
