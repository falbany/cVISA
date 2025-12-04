#include "ThermalAirTA5000.hpp"

namespace cvisa {
namespace drivers {

double ThermalAirTA5000::getTemperature() {
    return queryAndParse<double>(Commands::getTemperature());
}

double ThermalAirTA5000::getAirTemperature() {
    return queryAndParse<double>(Commands::getAirTemperature());
}

double ThermalAirTA5000::getDutTemperature() {
    return queryAndParse<double>(Commands::getDutTemperature());
}

void ThermalAirTA5000::setSetpoint(double temperature) {
    executeCommand(Commands::setSetpoint(), temperature);
}

double ThermalAirTA5000::getSetpoint() {
    return queryAndParse<double>(Commands::getSetpoint());
}

void ThermalAirTA5000::setSoakTime(int seconds) {
    executeCommand(Commands::setSoakTime(), seconds);
}

int ThermalAirTA5000::getSoakTime() {
    return queryAndParse<int>(Commands::getSoakTime());
}

void ThermalAirTA5000::setTemperatureWindow(double window) {
    executeCommand(Commands::setTemperatureWindow(), window);
}

double ThermalAirTA5000::getTemperatureWindow() {
    return queryAndParse<double>(Commands::getTemperatureWindow());
}

void ThermalAirTA5000::setHeadUp() { executeCommand(Commands::setHeadUp()); }

void ThermalAirTA5000::setHeadDown() {
    executeCommand(Commands::setHeadDown());
}

int ThermalAirTA5000::getHeadState() {
    return queryAndParse<int>(Commands::getHeadState());
}

void ThermalAirTA5000::setFlowOn() { executeCommand(Commands::setFlowOn()); }

void ThermalAirTA5000::setFlowOff() { executeCommand(Commands::setFlowOff()); }

void ThermalAirTA5000::setFlowRate(int scfm) {
    executeCommand(Commands::setFlowRate(), scfm);
}

int ThermalAirTA5000::getFlowRateSetting() {
    return queryAndParse<int>(Commands::getFlowRateSetting());
}

int ThermalAirTA5000::getFlowRateMeasured() {
    return queryAndParse<int>(Commands::getFlowRateMeasured());
}

void ThermalAirTA5000::setDutControlModeOn() {
    executeCommand(Commands::setDutControlModeOn());
}

void ThermalAirTA5000::setDutControlModeOff() {
    executeCommand(Commands::setDutControlModeOff());
}

int ThermalAirTA5000::getDutControlMode() {
    return queryAndParse<int>(Commands::getDutControlMode());
}

void ThermalAirTA5000::setDutSensorType(int type) {
    executeCommand(Commands::setDutSensorType(), type);
}

int ThermalAirTA5000::getDutSensorType() {
    return queryAndParse<int>(Commands::getDutSensorType());
}

void ThermalAirTA5000::setTrickleFlowOn() {
    executeCommand(Commands::setTrickleFlowOn());
}

void ThermalAirTA5000::setTrickleFlowOff() {
    executeCommand(Commands::setTrickleFlowOff());
}

int ThermalAirTA5000::getTrickleFlowState() {
    return queryAndParse<int>(Commands::getTrickleFlowState());
}

void ThermalAirTA5000::setLowerTemperatureLimit(double limit) {
    executeCommand(Commands::setLowerTemperatureLimit(), limit);
}

void ThermalAirTA5000::setUpperTemperatureLimit(double limit) {
    executeCommand(Commands::setUpperTemperatureLimit(), limit);
}

int ThermalAirTA5000::getErrorState() {
    return queryAndParse<int>(Commands::getErrorState());
}

}  // namespace drivers
}  // namespace cvisa
