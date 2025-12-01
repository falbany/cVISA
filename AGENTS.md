# Agent Development Guide for cvisa

This guide outlines the core design principles and development patterns for the `cvisa` library. Adhering to these conventions is crucial for maintaining the library's quality, consistency, and reusability.

## Code Formatting

To ensure a consistent and readable codebase, all C++ source files (`.cpp`, `.hpp`) **must** be formatted using `clang-format` before committing. The project includes a `.clang-format` configuration file in the root directory that defines the coding style.

You can format all C++ files by running the following command from the root of the repository:

```bash
find src examples -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i
```

---

## Build Environment

**IMPORTANT:** Do not attempt to build the project. The VISA SDK is not available in the test environment, and the build will fail. Code changes should be validated by inspection and static analysis only.

---

## Core Architecture

The library is built on a simple inheritance-based architecture:

1.  **Low-Level VISA Wrapper (`VisaInterface`):** This is the foundational class that directly wraps the VISA C API. It is a direct, RAII-compliant wrapper that handles the low-level details of opening, closing, reading from, and writing to an instrument. It should *not* contain any instrument-specific logic.

2.  **High-Level Driver Abstraction (`InstrumentDriver`):** This class inherits from `VisaInterface`, gaining all of its I/O capabilities. It provides shared functionality for all drivers, most importantly the `executeCommand` helper function, which centralizes the logic for executing SCPI commands defined as data.

3.  **Specific Drivers (e.g., `Agilent66xxA`):** A specific driver inherits from `InstrumentDriver`. Its only responsibility is to define its unique command set in a static map and provide public, high-level methods for instrument control (e.g., `setVoltage()`).

## How to Add a New Instrument Driver

When tasked with adding support for a new instrument (e.g., a "Keysight E3631A Power Supply"), you **must** follow this pattern.

### 1. Create the Driver Files

Create a new header (`.hpp`) and source (`.cpp`) file for your driver inside the `src/drivers/` directory. For example: `KeysightE3631A.hpp` and `KeysightE3631A.cpp`.

### 2. Define the Driver Class

In the header file, define your new class and ensure it inherits from `cvisa::drivers::InstrumentDriver`. The driver should expose overloaded constructors that mirror the base class to support both RAII-style and manual connections.

```cpp
// In KeysightE3631A.hpp
#include "../InstrumentDriver.hpp"
#include "../Command.hpp"
#include <map>
#include <string>

namespace cvisa::drivers {

class KeysightE3631A : public InstrumentDriver {
public:
    // --- Constructors ---
    // Mirror the base class constructors to allow flexible connection styles.
    KeysightE3631A() = default;
    explicit KeysightE3631A(const std::string& resourceName)
        : InstrumentDriver(resourceName) {}
    explicit KeysightE3631A(const std::string& resourceName,
                              unsigned int timeout_ms, char read_termination)
        : InstrumentDriver(resourceName, timeout_ms, read_termination) {}

    // --- Public API ---
    // Define the high-level methods for this instrument.
    void setVoltage(double voltage);
    double measureCurrent();
    // ... etc.

private:
    // Every driver MUST have its own static command registry.
    static const std::map<std::string, CommandSpec> s_commandRegistry;

    // Helper to look up a command spec from the registry.
    const CommandSpec& getSpec(const std::string& commandName) const;
};

} // namespace
```

### 3. Implement the Declarative Command System

In the source file (`.cpp`), you **must** define the SCPI command set for the instrument in the `s_commandRegistry`. This is the core of the declarative, data-driven design.

*   Use logical names for command keys (e.g., `"set_voltage"`).
*   Use standard C-style format specifiers (`%f`, `%d`, `%s`, etc.) in the command strings.
*   Assign the correct `CommandType` (`WRITE` or `QUERY`).
*   Optionally, specify a `delay_ms` for query commands that require extra processing time.

```cpp
// In KeysightE3631A.cpp
#include "KeysightE3631A.hpp"

namespace cvisa::drivers {

// Define the command set as data.
const std::map<std::string, CommandSpec> KeysightE3631A::s_commandRegistry = {
    {"set_voltage", {"VOLT %f", CommandType::WRITE}},
    {"meas_current", {"MEAS:CURR?", CommandType::QUERY, 50}}, // 50ms delay
    // ... other commands
};

// Implement the spec lookup helper.
const CommandSpec& KeysightE3631A::getSpec(const std::string& commandName) const {
    auto it = s_commandRegistry.find(commandName);
    if (it == s_commandRegistry.end()) {
        throw std::invalid_argument("Command not found: " + commandName);
    }
    return it->second;
}

// Implement the public methods.
void KeysightE3631A::setVoltage(double voltage) {
    // Public methods should be clean one-liners that call the
    // executeCommand function inherited from the base class.
    executeCommand(getSpec("set_voltage"), voltage);
}

double KeysightE3631A::measureCurrent() {
    std::string response = executeCommand(getSpec("meas_current"));
    // Parse the response as needed...
    return std::stod(response);
}

// ... etc.

} // namespace
```

### 4. Update the Build System

Finally, add your new source files to the `cvisa` library target in the main `CMakeLists.txt`.

```cmake
# In CMakeLists.txt
add_library(cvisa
    src/VisaInterface.cpp
    src/InstrumentDriver.cpp
    src/exceptions.cpp
    src/utils.cpp
    src/drivers/PowerSupply.cpp
    src/drivers/Agilent66xxA.cpp
    src/drivers/KeysightE3631A.cpp # <-- ADD YOUR NEW DRIVER HERE
)
```

By following this pattern, you ensure that new drivers are easy to create, read, and maintain, and that the core library remains clean and reusable.