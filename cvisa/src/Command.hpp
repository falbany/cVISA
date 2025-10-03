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
    WRITE, // A command that only sends data (e.g., "OUTP ON").
    QUERY  // A command that expects a response (e.g., "VOLT?").
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
    const char* command; // The SCPI command string template (e.g., "VOLT {}").
    CommandType type;    // The type of the command (WRITE or QUERY).
};

} // namespace cvisa

#endif // CVISA_COMMAND_HPP