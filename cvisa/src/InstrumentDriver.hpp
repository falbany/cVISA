#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include "VisaInstrument.hpp"
#include "Command.hpp" // Include CommandSpec for the helper function
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

/**
 * @class InstrumentDriver
 * @brief An abstract base class for creating instrument-specific drivers.
 *
 * This class provides the basic structure for building high-level abstractions
 * on top of the generic VisaInstrument. It now also provides a protected helper
 * function, `executeCommand`, to centralize the logic of formatting and
 * executing SCPI commands, promoting code reuse across all derived drivers.
 */
class InstrumentDriver {
public:
    explicit InstrumentDriver(VisaInstrument& instrument)
        : m_instrument(instrument) {}

    virtual ~InstrumentDriver() = default;

    // Drivers are tied to a specific instrument session and are non-copyable/movable.
    InstrumentDriver(const InstrumentDriver&) = delete;
    InstrumentDriver& operator=(const InstrumentDriver&) = delete;
    InstrumentDriver(InstrumentDriver&&) = delete;
    InstrumentDriver& operator=(InstrumentDriver&&) = delete;

protected:
    /**
     * @brief Formats and executes a command based on its specification.
     * @tparam Args Variadic arguments for formatting the command string.
     * @param spec The CommandSpec defining the command to execute.
     * @param args The arguments to be formatted into the command string.
     * @return The response from the instrument for QUERY commands.
     */
    template<typename... Args>
    std::string executeCommand(const CommandSpec& spec, Args... args) {
        // Use a C-style buffer for robust and safe formatting
        char buffer[256];
        snprintf(buffer, sizeof(buffer), spec.command, args...);
        std::string final_command = buffer;

        // Execute based on the command type
        if (spec.type == CommandType::WRITE) {
            m_instrument.write(final_command);
            return ""; // No response for write commands
        }
        if (spec.type == CommandType::QUERY) {
            return m_instrument.query(final_command);
        }

        // This should be unreachable if the CommandSpec is valid
        throw std::logic_error("Unknown command type in CommandSpec.");
    }

    // Protected member for direct VISA access by derived classes.
    VisaInstrument& m_instrument;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_INSTRUMENT_DRIVER_HPP