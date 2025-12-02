#ifndef CVISA_LOGGER_HPP
#define CVISA_LOGGER_HPP

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace cvisa {

// Defines the verbosity level for logging.
enum class LogLevel {
    NONE,     // No logging
    ERROR,    // Only errors
    WARNING,  // Warnings and errors
    INFO,     // Informational messages, warnings, and errors
    DEBUG     // Debug-level messages and everything else
};

class Logger {
     public:
    /**
     * @brief Sets the output stream for all log messages.
     * @param stream A pointer to the desired output stream (e.g., &std::cout,
     * &myfile). Defaults to &std::cerr.
     */
    static void setOutputStream(std::ostream* stream) {
        s_outputStream = stream ? stream : &std::cerr;
    }

    /**
     * @brief Logs a formatted message if the level is appropriate.
     * @param activeLevel The current verbosity level of the calling instance.
     * @param messageLevel The log level of the message.
     * @param resourceName The VISA resource name of the instrument.
     * @param message The message to log.
     */
    static void log(LogLevel activeLevel, LogLevel messageLevel,
                    const std::string& resourceName,
                    const std::string& message) {
        if (s_outputStream && activeLevel >= messageLevel &&
            messageLevel != LogLevel::NONE) {
            (*s_outputStream) << "[" << getCurrentTimestamp() << "] " << "["
                              << levelToString(messageLevel) << "] " << "["
                              << (resourceName.empty() ? "cvisa" : resourceName)
                              << "] " << message << std::endl;
        }
    }

     private:
    // The stream where log messages will be written.
    static std::ostream* s_outputStream;

    /**
     * @brief Converts a LogLevel enum to its string representation.
     */
    static std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::ERROR:
                return "ERROR  ";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::INFO:
                return "INFO   ";
            case LogLevel::DEBUG:
                return "DEBUG  ";
            default:
                return "UNKNOWN";
        }
    }

    /**
     * @brief Gets the current time as a formatted string (HH:MM:SS.ms).
     */
    static std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch()) %
                  1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%X");
        ss << '.' << std::setw(3) << std::setfill('0') << ms.count();
        return ss.str();
    }
};

// Initialize the static output stream to std::cerr by default.
std::ostream* Logger::s_outputStream = &std::cerr;

}  // namespace cvisa

#endif  // CVISA_LOGGER_HPP