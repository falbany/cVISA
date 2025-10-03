#ifndef CVISA_INSTRUMENT_DRIVER_HPP
#define CVISA_INSTRUMENT_DRIVER_HPP

#include "VisaInstrument.hpp"

namespace cvisa {
namespace drivers {

/**
 * @class InstrumentDriver
 * @brief An abstract base class for creating instrument-specific drivers.
 *
 * This class provides the basic structure for building high-level abstractions
 * on top of the generic VisaInstrument. It holds a reference to the underlying
 * communication object, allowing derived classes to implement instrument-specific
 * logic (e.g., `setVoltage`, `getFrequency`) by calling the appropriate
 * SCPI commands through the VisaInstrument.
 */
class InstrumentDriver {
public:
    /**
     * @brief Constructs the driver and associates it with a VISA instrument.
     * @param instrument A connected VisaInstrument object.
     */
    explicit InstrumentDriver(VisaInstrument& instrument)
        : m_instrument(instrument) {}

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~InstrumentDriver() = default;

    // --- Deleted copy/move semantics ---
    // Drivers are tied to a specific instrument session and should not be
    // copied or moved.
    InstrumentDriver(const InstrumentDriver&) = delete;
    InstrumentDriver& operator=(const InstrumentDriver&) = delete;
    InstrumentDriver(InstrumentDriver&&) = delete;
    InstrumentDriver& operator=(InstrumentDriver&&) = delete;

protected:
    // Protected member to give derived classes direct access to the
    // underlying VISA communication object.
    VisaInstrument& m_instrument;
};

} // namespace drivers
} // namespace cvisa

#endif // CVISA_INSTRUMENT_DRIVER_HPP