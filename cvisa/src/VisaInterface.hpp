#ifndef CVISA_VISA_INTERFACE_HPP
#define CVISA_VISA_INTERFACE_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <optional>
#include <cstdint>
#include <future>

// Forward-declare VISA types to avoid including visa.h in a public header.
using ViSession = unsigned long;
using ViStatus = long;

namespace cvisa {

/**
 * @class VisaInterface
 * @brief A C++ RAII wrapper for the VISA C API with manual connection support.
 *
 * This class encapsulates a VISA session, providing an object-oriented,
 * exception-safe interface to the underlying communication layer. It supports
 * both RAII-style (constructor-based) and manual connection management.
 */
class VisaInterface {
public:
    // --- Constructors and Destructor ---
    VisaInterface() = default;
    explicit VisaInterface(const std::string& resourceName,
                           std::optional<unsigned int> timeout_ms = std::nullopt,
                           std::optional<char> read_termination = std::nullopt,
                           std::optional<char> write_termination = std::nullopt);
    virtual ~VisaInterface();

    // --- Rule of Five: Move semantics enabled, copy semantics disabled ---
    VisaInterface(const VisaInterface&) = delete;
    VisaInterface& operator=(const VisaInterface&) = delete;
    VisaInterface(VisaInterface&& other) noexcept;
    VisaInterface& operator=(VisaInterface&& other) noexcept;

    // --- Manual Connection Management ---
    void setRessource(const std::string& resourceName);
    void connect();
    void disconnect();
    bool isConnected() const;

    // --- Core I/O Operations ---
    virtual void write(const std::string& command);
    virtual std::string read(size_t bufferSize = 2048);
    virtual std::string query(const std::string& command, size_t bufferSize = 2048, unsigned int delay_ms = 0);
    virtual std::future<std::string> queryAsync(const std::string& command, size_t bufferSize = 2048, unsigned int delay_ms = 0);

    // --- Configuration ---
    virtual void setTimeout(unsigned int timeout_ms);
    virtual void setReadTermination(char term_char, bool enable = true);
    virtual void setWriteTermination(char term_char);

    // --- Static Utilities ---
    static std::vector<std::string> findResources(const std::string& query = "?*INSTR");

private:
    void checkStatus(ViStatus status, const std::string& functionName);

    std::string m_resourceName;
    std::optional<unsigned int> m_timeout_ms;
    std::optional<char> m_read_termination;
    std::optional<char> m_write_termination;

    ViSession m_resourceManagerHandle = 0;
    ViSession m_instrumentHandle = 0;
};

} // namespace cvisa

#endif // CVISA_VISA_INTERFACE_HPP