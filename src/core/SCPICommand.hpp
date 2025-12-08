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
        WRITE,    // A command that only sends data (e.g., "OUTP ON").
        QUERY     // A command that expects a response (e.g., "VOLT?").
    };

    /**
     * @enum ResponseType
     * @brief Defines the expected data type of a query response.
     */
    enum class ResponseType {
        NONE,       // For WRITE commands that have no response.
        STRING,     // The raw string response.
        DOUBLE,     // A floating-point number.
        INTEGER,    // An integer.
        BOOLEAN     // A boolean value (e.g., "0" or "1").
    };

    /**
     * @struct SCPICommand
     * @brief A structure to hold the declarative definition of an SCPI command.
     *
     * This struct separates the definition of a command—its string template
     * and its fundamental type—from its execution. This allows drivers to define
     * their command sets as data, making them easier to manage and extend.
     */
    struct SCPICommand {
        const char*  command;         // The SCPI command string template (e.g., "VOLT %f").
        CommandType  type;            // The type of the command (WRITE or QUERY).
        ResponseType responseType;    // The expected type of the response.
        unsigned int delay_ms;        // Optional delay in ms to wait after a write, before a read.
        std::string  description;     // A human-readable description of the command.

        // C++11 constructor to provide default values.
        SCPICommand(const char* cmd, CommandType t, ResponseType rt = ResponseType::NONE, unsigned int delay = 0, const std::string& desc = "")
            : command(cmd), type(t), responseType(rt), delay_ms(delay), description(desc) {}
    };

    /**
     * @struct SCPICommons
     * @brief A struct containing static methods that return SCPICommand objects for
     * common SCPI commands.
     */
    struct SCPICommons {
        // Common System Commands
        static SCPICommand IDN_Query() { return SCPICommand("*IDN?", CommandType::QUERY, ResponseType::STRING, 0, "Get identification string."); }
        static SCPICommand RST() { return SCPICommand("*RST", CommandType::WRITE, ResponseType::NONE, 0, "Perform a system reset."); }
        static SCPICommand CLS() { return SCPICommand("*CLS", CommandType::WRITE, ResponseType::NONE, 0, "Clear status registers."); }

        // Synchronization Commands
        static SCPICommand TST_Query() { return SCPICommand("*TST?", CommandType::QUERY, ResponseType::INTEGER, 0, "Initiate a self-test."); }
        static SCPICommand OPC_Query() { return SCPICommand("*OPC?", CommandType::QUERY, ResponseType::INTEGER, 0, "Operation complete query."); }
        static SCPICommand WAI() { return SCPICommand("*WAI", CommandType::WRITE, ResponseType::NONE, 0, "Wait for operation complete."); }

        // Status Reporting Commands
        static SCPICommand STB_Query() { return SCPICommand("*STB?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get status byte."); }
        static SCPICommand ESR_Query() { return SCPICommand("*ESR?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get event status register."); }
        static SCPICommand ESE_Set() { return SCPICommand("*ESE %d", CommandType::WRITE, ResponseType::NONE, 0, "Set event status enable."); }
        static SCPICommand ESE_Query() { return SCPICommand("*ESE?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get event status enable."); }
        static SCPICommand SRE_Set() { return SCPICommand("*SRE %d", CommandType::WRITE, ResponseType::NONE, 0, "Set service request enable."); }
        static SCPICommand SRE_Query() { return SCPICommand("*SRE?", CommandType::QUERY, ResponseType::INTEGER, 0, "Get service request enable."); }
    };

}    // namespace cvisa

#endif    // CVISA_COMMAND_HPP
