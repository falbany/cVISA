# Agent Development Guide for cvisa

This guide outlines the core design principles and development patterns for the `cvisa` library. Adhering to these conventions is crucial for maintaining the library's quality, consistency, and reusability.

## Code Formatting

To ensure a consistent and readable codebase, all C++ source files (`.cpp`, `.hpp`) **must** be formatted using `clang-format` before committing. The project includes a `.clang-format` configuration file in the root directory that defines the coding style.

You can format all C++ files by running the following command from the root of the repository:

```bash
find src examples -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i
```

---

## Core Architecture

The library is built on a two-layer architecture:

1.  **Low-Level VISA Wrapper (`VisaInstrument`):** This class is a direct, RAII-compliant wrapper around the VISA C API. It handles the low-level details of opening, closing, reading from, and writing to an instrument. It should *not* contain any instrument-specific logic. Its purpose is to provide a generic, safe, and reliable communication channel.

2.  **High-Level Driver Abstraction (`InstrumentDriver`):** This is an abstract base class from which all instrument-specific drivers must inherit. It provides shared functionality, most importantly the `executeCommand` helper function, which centralizes the logic for executing SCPI commands defined as data.

## How to Add a New Instrument Driver

When tasked with adding support for a new instrument (e.g., a "Keysight E3631A Power Supply"), you **must** follow this pattern. Do not add instrument-specific methods directly to `VisaInstrument`.

### 1. Create the Driver Files

Create a new header (`.hpp`) and source (`.cpp`) file for your driver inside the `cvisa/src/drivers/` directory. For example: `KeysightE3631A.hpp` and `KeysightE3631A.cpp`.

### 2. Define the Driver Class

In the header file, define your new class and ensure it inherits from `cvisa::drivers::InstrumentDriver`.

```cpp
// In KeysightE3631A.hpp
#include "../InstrumentDriver.hpp"
#include "../Command.hpp"
#include <map>
#include <string>

namespace cvisa::drivers {

class KeysightE3631A : public InstrumentDriver {
public:
    explicit KeysightE3631A(VisaInstrument& instrument);

    // Define the public, high-level methods for this instrument
    void setVoltage(double voltage, int output_channel);
    double measureCurrent(int output_channel);
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
*   Use standard C-style format specifiers (`%f`, `%d`, `%s`, etc.) in the command strings for `snprintf`.
*   Assign the correct `CommandType` (`WRITE` or `QUERY`).

```cpp
// In KeysightE3631A.cpp
#include "KeysightE3631A.hpp"

namespace cvisa::drivers {

// Define the command set as data.
const std::map<std::string, CommandSpec> KeysightE3631A::s_commandRegistry = {
    {"set_voltage", {"VOLT %f, (@%d)", CommandType::WRITE}}, // Example with channel
    {"meas_current",{"MEAS:CURR? (@%d)", CommandType::QUERY}},
    // ... other commands
};

// Implement the constructor
KeysightE3631A::KeysightE3631A(VisaInstrument& instrument)
    : InstrumentDriver(instrument) {}

// Implement the spec lookup helper
const CommandSpec& KeysightE3631A::getSpec(const std::string& commandName) const {
    auto it = s_commandRegistry.find(commandName);
    if (it == s_commandRegistry.end()) {
        throw std::invalid_argument("Command not found: " + commandName);
    }
    return it->second;
}

// Implement the public methods
void KeysightE3631A::setVoltage(double voltage, int output_channel) {
    // Public methods should be clean one-liners that call the
    // executeCommand function inherited from the base class.
    executeCommand(getSpec("set_voltage"), voltage, output_channel);
}

double KeysightE3631A::measureCurrent(int output_channel) {
    std::string response = executeCommand(getSpec("meas_current"), output_channel);
    // Parse the response as needed...
    return std::stod(response);
}

// ... etc.

} // namespace
```

### 4. Update the Build System

Finally, add your new source file (`.cpp`) to the library target in `cvisa/CMakeLists.txt`.

```cmake
# In cvisa/CMakeLists.txt
add_library(cvisa
    src/VisaInstrument.cpp
    src/exceptions.cpp
    src/drivers/PowerSupply.cpp
    src/drivers/Agilent66xxA.cpp
    src/drivers/KeysightE3631A.cpp # <-- ADD YOUR NEW DRIVER HERE
)
```

By following this pattern, you ensure that new drivers are easy to create, read, and maintain, and that the core library remains clean and reusable.