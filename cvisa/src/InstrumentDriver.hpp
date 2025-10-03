#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include "VisaInterface.hpp" // Changed from VisaInstrument.hpp
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
 * to centralize the logic for formatting and executing SCPI commands via the
 * underlying VisaInterface.
 */
class InstrumentDriver {
public:
    // Constructor now takes a VisaInterface reference
    explicit InstrumentDriver(VisaInterface& interface)
        : m_interface(interface) {}

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
        m_interface.write(buffer); // Use m_interface
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
        return m_interface.query(buffer, 2048, delay_ms); // Use m_interface
    }

    // Overload for queries that don't require formatting or delays
    std::string executeQuery(const CommandSpec& spec) {
        if (spec.type != CommandType::QUERY) {
            throw std::logic_error("Attempted to call executeQuery on a WRITE command.");
        }
        return m_interface.query(spec.command); // Use m_interface
    }

    // Renamed from m_instrument to m_interface for clarity
    VisaInterface& m_interface;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_INSTRUMENT_DRIVER_HPP