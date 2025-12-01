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

3.  **Specific Drivers (e.g., `Agilent66xxA`):** A specific driver inherits from `InstrumentDriver`. Its primary responsibility is to define its unique SCPI command set in a public, nested `Commands` struct and provide high-level public methods for instrument control.

## How to Add a New Instrument Driver

When tasked with adding support for a new instrument (e.g., a "Keysight E3631A Power Supply"), you **must** follow this pattern.

### 1. Create the Driver Files

Create a new header (`.hpp`) and source (`.cpp`) file for your driver inside the `src/drivers/` directory. For example: `KeysightE3631A.hpp` and `KeysightE3631A.cpp`.

### 2. Define the Driver Class and Commands

In the header file, define your new class. It must inherit from `cvisa::drivers::InstrumentDriver` and include a public nested `struct` named `Commands`.

*   The `Commands` struct must contain a `static constexpr CommandSpec` for every SCPI command the driver supports. This approach provides compile-time safety and enables IDE autocompletion.
*   The driver should expose overloaded constructors that mirror the base class to support both RAII-style and manual connections.

```cpp
// In KeysightE3631A.hpp
#include "../InstrumentDriver.hpp"
#include "../Command.hpp"
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

    // --- Command Definitions ---
    // Use a public nested struct to hold all command specifications.
    struct Commands {
        static constexpr CommandSpec SET_VOLTAGE = {"VOLT %f", CommandType::WRITE};
        static constexpr CommandSpec MEAS_CURRENT = {"MEAS:CURR?", CommandType::QUERY, 50};
        // ... other commands
    };
};

} // namespace
```

### 3. Implement the Public Methods

In the source file (`.cpp`), implement the driver's public methods. Each method should be a clean, one-line call to the `executeCommand` function inherited from the base class, using the command definitions from the `Commands` struct.

```cpp
// In KeysightE3631A.cpp
#include "KeysightE3631A.hpp"

namespace cvisa::drivers {

// Implement the public methods.
void KeysightE3631A::setVoltage(double voltage) {
    // Public methods should be clean one-liners that call executeCommand
    // with the corresponding static command object.
    executeCommand(Commands::SET_VOLTAGE, voltage);
}

double KeysightE3631A::measureCurrent() {
    std::string response = executeCommand(Commands::MEAS_CURRENT);
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