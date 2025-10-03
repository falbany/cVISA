#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include "VisaInstrument.hpp"
#include "Command.hpp"
#include <string>
#include <stdexcept>

namespace cvisa {
namespace drivers {

/**
 * @class InstrumentDriver
 * @brief An abstract base class for creating instrument-specific drivers.
 *
 * This class provides protected helper functions (`executeWrite`, `executeQuery`)
 * to centralize the logic for formatting and executing SCPI commands.
 */
class InstrumentDriver {
public:
    explicit InstrumentDriver(VisaInstrument& instrument)
        : m_instrument(instrument) {}

    virtual ~InstrumentDriver() = default;

    InstrumentDriver(const InstrumentDriver&) = delete;
    InstrumentDriver& operator=(const InstrumentDriver&) = delete;
    InstrumentDriver(InstrumentDriver&&) = delete;
    InstrumentDriver& operator=(InstrumentDriver&&) = delete;

protected:
    /**
     * @brief Formats and executes a WRITE command.
     */
    template<typename... Args>
    void executeWrite(const CommandSpec& spec, Args... args) {
        if (spec.type != CommandType::WRITE) {
            throw std::logic_error("Attempted to call executeWrite on a QUERY command.");
        }
        char buffer[256];
        snprintf(buffer, sizeof(buffer), spec.command, args...);
        m_instrument.write(buffer);
    }

    /**
     * @brief Formats and executes a QUERY command, passing a delay to the VISA layer.
     */
    template<typename... Args>
    std::string executeQuery(const CommandSpec& spec, unsigned int delay_ms, Args... args) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error("Attempted to call executeQuery on a WRITE command.");
        }
        char buffer[256];
        snprintf(buffer, sizeof(buffer), spec.command, args...);
        return m_instrument.query(buffer, 2048, delay_ms);
    }

    // Overload for queries that don't require formatting or delays
    std::string executeQuery(const CommandSpec& spec) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error("Attempted to call executeQuery on a WRITE command.");
        }
        return m_instrument.query(spec.command);
    }


    VisaInstrument& m_instrument;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_INSTRUMENT_DRIVER_HPP