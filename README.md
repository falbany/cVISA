# cvisa: A Modern C++ VISA Wrapper Library

`cvisa` is a simple, professional C++ library providing a rich, object-oriented wrapper for the VISA C API. It is designed to make communication with SCPI-based lab instruments intuitive, safe, and robust. The library promotes modern C++ practices, including a straightforward inheritance model, a clean data-driven approach to instrument control, and flexible connection management.

## Key Features

*   **Flexible Connection Management:** Constructor overloading allows for both simple, one-line RAII-style connections (by providing a resource string) and manual control over the VISA session (by using the default constructor).
*   **Simple Inheritance Model:** High-level drivers inherit directly from the core communication class, making the API intuitive and easy to use.
*   **Asynchronous Operations:** Perform non-blocking queries using `std::future` for building responsive applications.
*   **Object-Oriented & RAII-Compliant:** Manages VISA sessions automatically. The driver's constructor and destructor handle `viOpen` and `viClose`, preventing resource leaks.
*   **Exception Safety:** All VISA function calls are checked, and descriptive exceptions are thrown on failure.
*   **Declarative, Data-Driven Drivers:** Implement instrument-specific drivers by defining their SCPI command sets as simple data.
*   **Reusable Abstraction Layer:** A clean `InstrumentDriver` base class provides a shared command execution engine for all drivers.
*   **Modern Build System:** Uses CMake for easy integration into cross-platform projects.

## Architecture: Simple and Extensible

The `cvisa` library is built on a simple and powerful inheritance-based architecture.

1.  **`VisaInterface` (The Base Communication Layer):**
    This is the foundational class that directly wraps the VISA C API. It handles the low-level details of opening and closing sessions, writing commands, and reading responses.

2.  **`InstrumentDriver` (The Command Engine):**
    This class inherits from `VisaInterface`, gaining all of its I/O capabilities. It enhances the base layer by adding a powerful, data-driven command execution engine and implementations for all the common SCPI commands (`*IDN?`, `*RST`, etc.).

3.  **Specific Drivers (e.g., `Agilent66xxA`):**
    A specific driver, like one for an Agilent power supply, inherits from `InstrumentDriver`. This gives it the full VISA I/O and command engine functionality. The only responsibility of a specific driver is to define its unique command set in a static map and provide public methods that are meaningful for that instrument (e.g., `setVoltage()`).

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
│       └── Agilent66xxA.cpp
│       ├── PowerSupply.hpp     # Generic power supply driver
│       └── PowerSupply.cpp
├── examples/
│   └── basic_usage.cpp         # Demonstrates high-level driver usage
└── CMakeLists.txt              # The main build script
```

## How to Use

The driver classes feature overloaded constructors to support both simple and advanced use cases.

### Easy Mode: Automatic Connection (RAII)

Provide the VISA resource string to the constructor to connect automatically. The connection will be closed when the object's destructor is called.

```cpp
#include <iostream>
#include "drivers/Agilent66xxA.hpp" // Include your specific driver
#include "exceptions.hpp"

void raii_example(const std::string& resource_address) {
    // 1. Instantiate the driver with a resource string to connect automatically.
    cvisa::drivers::Agilent66xxA psu(resource_address);

    // 2. Use the driver's methods.
    std::cout << "Instrument ID: " << psu.getIdentification() << std::endl;

    // 3. The connection is automatically closed when `psu` is destroyed.
}
```

### Advanced Mode: Manual Connection

Create a driver by calling the default constructor. The driver will be created in a disconnected state, ready for manual configuration and connection.

```cpp
#include <iostream>
#include "drivers/Agilent66xxA.hpp"
#include "exceptions.hpp"

void manual_example(const std::string& resource_address) {
    // 1. Create a disconnected driver by calling the default constructor.
    cvisa::drivers::Agilent66xxA psu;

    // 2. Set the resource and connect manually.
    psu.setRessource(resource_address);
    psu.setTimeout(5000);
    psu.connect();

    // 3. Use the driver's methods.
    std::cout << "ID: " << psu.getIdentification() << std::endl;

    // 4. Manually disconnect.
    psu.disconnect();
}
```