#ifndef CVISA_IVISA_IO_HPP
#define CVISA_IVISA_IO_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <future>

namespace cvisa {

/**
 * @class IVisaIo
 * @brief An abstract interface for VISA I/O operations.
 *
 * This pure virtual class defines the contract for any class that provides
 * VISA communication services. It decouples the high-level instrument drivers
 * from the concrete implementation of the VISA communication layer, enabling
 * dependency injection, mocking, and improved testability.
 */
class IVisaIo {
public:
    virtual ~IVisaIo() = default;

    // --- Pure Virtual I/O Operations ---
    virtual void write(const std::string& command) = 0;
    virtual std::string read(size_t bufferSize = 2048) = 0;
    virtual std::string query(const std::string& command, size_t bufferSize = 2048, unsigned int delay_ms = 0) = 0;

    // --- Pure Virtual I/O Operations ---
    virtual std::future<std::string> queryAsync(const std::string& command, size_t bufferSize = 2048, unsigned int delay_ms = 0) = 0;

    // --- Pure Virtual Configuration ---
    virtual void setTimeout(unsigned int timeout_ms) = 0;
    virtual void setReadTermination(char term_char, bool enable = true) = 0;
    virtual void setWriteTermination(char term_char) = 0;
};

} // namespace cvisa

#endif // CVISA_IVISA_IO_HPP