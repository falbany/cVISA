#ifndef CVISA_EXCEPTIONS_HPP
#define CVISA_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace cvisa {

/**
 * @class VisaException
 * @brief Base exception class for all VISA-related errors.
 *
 * This exception is thrown when a VISA function call returns a status other
 * than VI_SUCCESS. It inherits from std::runtime_error to provide a descriptive
 * error message.
 */
class VisaException : public std::runtime_error {
     public:
    explicit VisaException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @class ConnectionException
 * @brief Exception for errors related to establishing or maintaining a
 * connection.
 *
 * This is thrown for failures in opening a session (e.g., viOpen) or when a
 * connection is unexpectedly terminated.
 */
class ConnectionException : public VisaException {
     public:
    explicit ConnectionException(const std::string& message)
        : VisaException(message) {}
};

/**
 * @class CommandException
 * @brief Exception for errors that occur during command execution
 * (write/read/query).
 *
 * This is thrown for failures in I/O operations like viWrite or viRead, often
 * indicating a problem with the command syntax or instrument state.
 */
class CommandException : public VisaException {
     public:
    explicit CommandException(const std::string& message)
        : VisaException(message) {}
};

}  // namespace cvisa

#endif  // CVISA_EXCEPTIONS_HPP