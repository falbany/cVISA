#ifndef CVISA_COMMAND_HPP
#define CVISA_COMMAND_HPP

#include <string>

namespace cvisa {

/**
 * @enum CommandType
 * @brief Defines the type of an SCPI command, indicating whether it expects a
 *        response.
 */
enum class CommandType {
    WRITE,  // A command that only sends data (e.g., "OUTP ON").
    QUERY   // A command that expects a response (e.g., "VOLT?").
};

/**
 * @enum ResponseType
 * @brief Defines the expected data type of a query response.
 */
enum class ResponseType {
    NONE,     // For WRITE commands that have no response.
    STRING,   // The raw string response.
    DOUBLE,   // A floating-point number.
    INTEGER,  // An integer.
    BOOLEAN   // A boolean value (e.g., "0" or "1").
};

/**
 * @struct CommandSpec
 * @brief A structure to hold the declarative definition of an SCPI command.
 *
 * This struct separates the definition of a command—its string template
 * and its fundamental type—from its execution. This allows drivers to define
 * their command sets as data, making them easier to manage and extend.
 */
struct CommandSpec {
    const char* command;  // The SCPI command string template (e.g., "VOLT %f").
    CommandType type;     // The type of the command (WRITE or QUERY).
    ResponseType responseType;  // The expected type of the response.
    unsigned int
        delay_ms;  // Optional delay in ms to wait after a write, before a read.
    std::string description;  // A human-readable description of the command.

    // C++11 constructor to provide default values.
    CommandSpec(const char* cmd, CommandType t,
                ResponseType rt = ResponseType::NONE, unsigned int delay = 0,
                const std::string& desc = "")
        : command(cmd),
          type(t),
          responseType(rt),
          delay_ms(delay),
          description(desc) {}
};

/**
 * @struct CommonCommands
 * @brief A struct containing static methods that return CommandSpec objects for
 * common SCPI commands.
 */
struct CommonCommands {
    static CommandSpec getIdentification() {
        return CommandSpec("*IDN?", CommandType::QUERY, ResponseType::STRING, 0,
                           "Get identification string.");
    }
    static CommandSpec reset() {
        return CommandSpec("*RST", CommandType::WRITE, ResponseType::NONE, 0,
                           "Perform a system reset.");
    }
    static CommandSpec clearStatus() {
        return CommandSpec("*CLS", CommandType::WRITE, ResponseType::NONE, 0,
                           "Clear status registers.");
    }
    static CommandSpec selfTest() {
        return CommandSpec("*TST?", CommandType::QUERY, ResponseType::INTEGER,
                           0, "Initiate a self-test.");
    }
    static CommandSpec operationComplete() {
        return CommandSpec("*OPC?", CommandType::QUERY, ResponseType::INTEGER,
                           0, "Operation complete query.");
    }
    static CommandSpec waitToContinue() {
        return CommandSpec("*WAI", CommandType::WRITE, ResponseType::NONE, 0,
                           "Wait for operation complete.");
    }
    static CommandSpec getStatusByte() {
        return CommandSpec("*STB?", CommandType::QUERY, ResponseType::INTEGER,
                           0, "Get status byte.");
    }
    static CommandSpec getEventStatusRegister() {
        return CommandSpec("*ESR?", CommandType::QUERY, ResponseType::INTEGER,
                           0, "Get event status register.");
    }
    static CommandSpec setEventStatusEnable() {
        return CommandSpec("*ESE %d", CommandType::WRITE, ResponseType::NONE, 0,
                           "Set event status enable.");
    }
    static CommandSpec getEventStatusEnable() {
        return CommandSpec("*ESE?", CommandType::QUERY, ResponseType::INTEGER,
                           0, "Get event status enable.");
    }
    static CommandSpec setServiceRequestEnable() {
        return CommandSpec("*SRE %d", CommandType::WRITE, ResponseType::NONE, 0,
                           "Set service request enable.");
    }
    static CommandSpec getServiceRequestEnable() {
        return CommandSpec("*SRE?", CommandType::QUERY, ResponseType::INTEGER,
                           0, "Get service request enable.");
    }
};

}  // namespace cvisa

#endif  // CVISA_COMMAND_HPP
