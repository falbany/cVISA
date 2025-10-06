#include "InstrumentDriver.hpp"

#include <algorithm>  // For std::find_if_not
#include <string>

#include "exceptions.hpp"

namespace {
// Helper to trim leading/trailing whitespace
std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, (end - start + 1));
}
}  // namespace

namespace cvisa {
namespace drivers {

// --- Command Registry for Common SCPI Commands ---
const std::map<std::string, CommandSpec>
    InstrumentDriver::s_common_command_registry = {
        {"get_idn", {"*IDN?", CommandType::QUERY}},
        {"reset", {"*RST", CommandType::WRITE}},
        {"clear_status", {"*CLS", CommandType::WRITE}},
        {"wait", {"*WAI", CommandType::WRITE}},
        {"op_complete_q", {"*OPC?", CommandType::QUERY}},
        {"self_test_q", {"*TST?", CommandType::QUERY}},
        {"status_byte_q", {"*STB?", CommandType::QUERY}},
        {"event_status_q", {"*ESR?", CommandType::QUERY}},
        {"event_enable", {"*ESE %d", CommandType::WRITE}},
        {"event_enable_q", {"*ESE?", CommandType::QUERY}},
        {"service_req_en", {"*SRE %d", CommandType::WRITE}},
        {"service_req_en_q", {"*SRE?", CommandType::QUERY}}};

// --- Common SCPI Command Implementations ---

std::string InstrumentDriver::getIdentification() {
    return trim(executeCommand(s_common_command_registry.at("get_idn")));
}

void InstrumentDriver::reset() {
    executeCommand(s_common_command_registry.at("reset"));
}

void InstrumentDriver::clearStatus() {
    executeCommand(s_common_command_registry.at("clear_status"));
}

void InstrumentDriver::waitToContinue() {
    executeCommand(s_common_command_registry.at("wait"));
}

bool InstrumentDriver::isOperationComplete() {
    return trim(executeCommand(
               s_common_command_registry.at("op_complete_q"))) == "1";
}

int InstrumentDriver::runSelfTest() {
    std::string response =
        trim(executeCommand(s_common_command_registry.at("self_test_q")));
    try {
        return std::stoi(response);
    } catch (const std::exception& e) {
        throw CommandException("Invalid response from self-test query: " +
                               response);
    }
}

uint8_t InstrumentDriver::getStatusByte() {
    std::string response =
        trim(executeCommand(s_common_command_registry.at("status_byte_q")));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getStatusByte: " +
                               response);
    }
}

uint8_t InstrumentDriver::getEventStatusRegister() {
    std::string response =
        trim(executeCommand(s_common_command_registry.at("event_status_q")));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getEventStatusRegister: " +
                               response);
    }
}

void InstrumentDriver::setEventStatusEnable(uint8_t mask) {
    executeCommand(s_common_command_registry.at("event_enable"), mask);
}

uint8_t InstrumentDriver::getEventStatusEnable() {
    std::string response =
        trim(executeCommand(s_common_command_registry.at("event_enable_q")));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException("Invalid response for getEventStatusEnable: " +
                               response);
    }
}

void InstrumentDriver::setServiceRequestEnable(uint8_t mask) {
    executeCommand(s_common_command_registry.at("service_req_en"), mask);
}

uint8_t InstrumentDriver::getServiceRequestEnable() {
    std::string response =
        trim(executeCommand(s_common_command_registry.at("service_req_en_q")));
    try {
        return static_cast<uint8_t>(std::stoi(response));
    } catch (const std::exception& e) {
        throw CommandException(
            "Invalid response for getServiceRequestEnable: " + response);
    }
}

}  // namespace drivers
}  // namespace cvisa