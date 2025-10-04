# cvisa: A Modern C++ VISA Wrapper Library

`cvisa` is a simple, professional C++ library providing a rich, object-oriented wrapper for the VISA C API. It is designed to make communication with SCPI-based lab instruments intuitive, safe, and robust. The library promotes modern C++ practices, including RAII for resource management, a straightforward inheritance model for creating drivers, and a clean, data-driven approach to instrument control.

## Key Features

*   **Simple Inheritance Model:** High-level drivers inherit directly from the core communication class, making the API intuitive and easy to use. Create a fully functional driver object in a single line.
*   **Asynchronous Operations:** Perform non-blocking queries using `std::future` for building responsive applications that don't get stuck waiting for slow instruments.
*   **Object-Oriented & RAII-Compliant:** Manages VISA sessions automatically. The driver's constructor and destructor handle `viOpen` and `viClose`, preventing resource leaks.
*   **Exception Safety:** All VISA function calls are checked, and descriptive exceptions are thrown on failure, preventing silent errors.
*   **Declarative, Data-Driven Drivers:** Implement instrument-specific drivers by defining their SCPI command sets as simple data, separating the "what" from the "how."
*   **Reusable Abstraction Layer:** A clean `InstrumentDriver` base class with a shared command execution engine makes creating new, high-level instrument drivers trivial.
*   **Modern Build System:** Uses CMake for easy integration into cross-platform projects.
*   **No External Dependencies:** Besides a VISA SDK (like NI-VISA, Keysight VISA, etc.), the library is self-contained.

## Architecture: Simple and Extensible

The `cvisa` library is built on a simple and powerful inheritance-based architecture.

1.  **`VisaInterface` (The Base Communication Layer):**
    This is the foundational class that directly wraps the VISA C API. It handles the low-level details of opening and closing sessions, writing commands, and reading responses.

2.  **`InstrumentDriver` (The Command Engine):**
    This class inherits from `VisaInterface`, gaining all of its I/O capabilities. It enhances the base layer by adding a powerful, data-driven command execution engine and implementations for all the common SCPI commands (`*IDN?`, `*RST`, etc.).

3.  **Specific Drivers (e.g., `Agilent66xxA`):**
    A specific driver, like one for an Agilent power supply, inherits from `InstrumentDriver`. This gives it the full VISA I/O and command engine functionality. The only responsibility of a specific driver is to define its unique command set in a static map and provide public methods that are meaningful for that instrument (e.g., `setVoltage()`).

This design makes creating new drivers incredibly simple while promoting maximum code reuse.

## Project Structure

The project is organized to separate the core library, instrument-specific drivers, and examples.

```
cvisa/
├── src/
│   ├── VisaInterface.hpp       # Base VISA session wrapper
│   ├── VisaInterface.cpp
│   ├── exceptions.hpp          # Custom exception classes
│   ├── exceptions.cpp
│   ├── InstrumentDriver.hpp    # Base class for all drivers
│   ├── InstrumentDriver.cpp
│   ├── Command.hpp             # Data structures for the command system
│   └── drivers/
│       ├── Agilent66xxA.hpp    # Example hardware-specific driver
│       ├── Agilent66xxA.cpp
│       ├── PowerSupply.hpp     # Generic power supply driver
│       └── PowerSupply.cpp
├── examples/
│   └── basic_usage.cpp         # Demonstrates high-level driver usage
└── CMakeLists.txt              # The main build script
```

## Building the Project

This project uses CMake to generate a native build environment. You must have a C++11 compliant compiler and a VISA SDK installed on your system.

**1. Configure the Build:**
From the `cvisa` root directory, create a build directory and run CMake.

```bash
mkdir build
cd build
cmake ..
```
CMake will automatically try to find your installed VISA library.

**2. Compile the Code:**
Run your platform's build tool.

```bash
# On Linux or macOS
make

# On Windows with Visual Studio
cmake --build .
```
This will build the `cvisa` static library and the `example_app` executable inside the `build/` directory.

## How to Use

Using `cvisa` is straightforward. Simply include the header for the specific instrument you want to control and instantiate it with the VISA resource string.

```cpp
#include <iostream>
#include "drivers/Agilent66xxA.hpp" // Include your specific driver
#include "exceptions.hpp"

int main() {
    // Replace this with the VISA resource string of your instrument.
    const std::string resource_address = "GPIB0::5::INSTR";

    try {
        // 1. Instantiate the driver directly.
        // This single line creates the object and opens the VISA session.
        cvisa::drivers::Agilent66xxA psu(resource_address, 5000, '\n');

        // 2. Use the driver's clean, high-level methods.
        std::cout << "Instrument ID: " << psu.getIdentification() << std::endl;
        std::cout << "Configuring power supply..." << std::endl;
        psu.setVoltage(12.0); // Sets voltage to 12.0 V
        psu.setCurrent(1.0);  // Sets current limit to 1.0 A
        psu.setOutput(true);  // Enables the output

        // 3. Measure actual values from the instrument.
        std::cout << "Measured Voltage: " << psu.measureVoltage() << " V" << std::endl;
        std::cout << "Measured Current: " << psu.measureCurrent() << " A" << std::endl;

        // 4. Clean up.
        psu.setOutput(false);
        std::cout << "Output disabled." << std::endl;

    } catch (const cvisa::VisaException& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```