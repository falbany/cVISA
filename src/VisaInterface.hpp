#ifndef CVISA_VISA_INTERFACE_HPP
#define CVISA_VISA_INTERFACE_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <future>

// Forward-declare VISA types to avoid including visa.h in a public header.
using ViSession = unsigned long;
using ViStatus = long;

namespace cvisa {

/**
 * @class VisaInterface
 * @brief A C++11 compliant RAII wrapper for the VISA C API with flexible connection management.
 *
 * This class encapsulates a VISA session. It can be constructed with a VISA
 * resource string for immediate connection (RAII-style) or constructed empty
 * for manual connection management.
 */
class VisaInterface {
public:
    // --- Constructors and Destructor ---
    /**
     * @brief Default constructor. Creates a disconnected interface object.
     */
    VisaInterface();

    /**
     * @brief Constructs and connects with resource name only.
     */
    explicit VisaInterface(const std::string& resourceName);

    /**
     * @brief Constructs and connects with timeout and read termination.
     */
    explicit VisaInterface(const std::string& resourceName, unsigned int timeout_ms, char read_termination);

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
    void applyConfiguration();

    std::string m_resourceName;

    // C++11 compatible way to handle optional configuration
    unsigned int m_timeout_ms;
    bool m_timeout_ms_set;
    char m_read_termination;
    bool m_read_termination_set;
    char m_write_termination;
    bool m_write_termination_set;

    ViSession m_resourceManagerHandle;
    ViSession m_instrumentHandle;
};

} // namespace cvisa

#endif // CVISA_VISA_INTERFACE_HPP