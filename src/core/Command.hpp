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

    // C++11 constructor to provide default values.
    CommandSpec(const char* cmd, CommandType t,
                ResponseType rt = ResponseType::NONE, unsigned int delay = 0)
        : command(cmd), type(t), responseType(rt), delay_ms(delay) {}
};

}  // namespace cvisa

#endif  // CVISA_COMMAND_HPP
