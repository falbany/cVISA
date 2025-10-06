# cvisa: A Modern C++ VISA Wrapper Library

`cvisa` is a simple, professional C++ library providing a rich, object-oriented wrapper for the VISA C API. It is designed to make communication with SCPI-based lab instruments intuitive, safe, and robust. The library promotes modern C++ practices, including RAII for resource management and a clean, data-driven approach to instrument control.

## Key Features

*   **Object-Oriented & RAII-Compliant:** Manages VISA sessions automatically within the `VisaInstrument` class constructor and destructor. No more manual `viOpen` or `viClose` calls.
*   **Exception Safety:** All VISA function calls are checked, and descriptive exceptions are thrown on failure, preventing silent errors.
*   **Declarative, Data-Driven Drivers:** Implement instrument-specific drivers by defining their SCPI command sets as simple data, separating the "what" from the "how" and making drivers easy to read and maintain.
*   **Reusable Abstraction Layer:** A clean `InstrumentDriver` base class with a shared command execution engine makes creating new, high-level instrument drivers trivial.
*   **Modern Build System:** Uses CMake for easy integration into cross-platform projects.
*   **No External Dependencies:** Besides a VISA SDK (like NI-VISA, Keysight VISA, etc.), the library is self-contained.

## Project Structure

The project is organized to separate the core library, instrument-specific drivers, and examples.

```
cvisa/
├── src/
│   ├── VisaInstrument.hpp      # Core VISA session wrapper
│   ├── VisaInstrument.cpp
│   ├── exceptions.hpp          # Custom exception classes
│   ├── exceptions.cpp
│   ├── InstrumentDriver.hpp    # Base class for all drivers
│   ├── Command.hpp             # Data structures for the command system
│   └── drivers/
│       ├── Agilent66xxA.hpp    # Example hardware-specific driver
│       └── Agilent66xxA.cpp
├── examples/
│   └── basic_usage.cpp         # Demonstrates high-level driver usage
└── CMakeLists.txt              # The main build script
```

## Building the Project

This project uses CMake to generate a native build environment. You must have a C++17 compliant compiler and a VISA SDK installed on your system.

**1. Configure the Build:**
From the `cvisa` root directory, create a build directory and run CMake.

```bash
mkdir build
cd build
cmake ..
```
CMake will automatically try to find your installed VISA library. If it's in a non-standard location, you may need to provide a hint to CMake.

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

The recommended way to use `cvisa` is through the instrument driver pattern. First, establish a connection with `VisaInstrument`, then pass it to a specific driver.

```cpp
#include <iostream>
#include "VisaInstrument.hpp"
#include "drivers/Agilent66xxA.hpp" // Include your specific driver

int main() {
    // --- IMPORTANT ---
    // Replace this with the VISA resource string of your instrument.
    const std::string resource_address = "GPIB0::5::INSTR";

    try {
        // 1. Establish the low-level VISA connection
        cvisa::VisaInstrument instrument(resource_address, 5000, '\n');

        // 2. Instantiate the high-level driver
        cvisa::drivers::Agilent66xxA psu(instrument);

        // 3. Use the driver's clean, high-level methods
        std::cout << "Configuring power supply..." << std::endl;
        psu.setVoltage(12.0); // Sets voltage to 12.0 V
        psu.setCurrent(1.0);  // Sets current limit to 1.0 A
        psu.setOutput(true);  // Enables the output

        // 4. Measure actual values from the instrument
        std::cout << "Measured Voltage: " << psu.measureVoltage() << " V" << std::endl;
        std::cout << "Measured Current: " << psu.measureCurrent() << " A" << std::endl;

        // 5. Clean up
        psu.setOutput(false);

    } catch (const cvisa::VisaException& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```