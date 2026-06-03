# cVISA Simulation Backend - PyVisa-Like Hardware-Free Testing

## Overview

The cVISA simulation backend provides a PyVisa-compatible way to test SCPI drivers without real hardware. It allows you to:

- **Define simulated instruments** with predefined SCPI command-response dialogues
- **Test drivers** without requiring the VISA SDK or physical instruments
- **Simulate multiple instruments** simultaneously on different resource strings
- **Use exact and pattern matching** for SCPI commands
- **Maintain device state** across multiple commands
- **Integrate seamlessly** with existing cVISA drivers via the `IVISABackend` abstraction

## Architecture

The simulation system consists of three main components:

### 1. **SimulatedDevice**
Represents a single simulated SCPI instrument with a collection of dialogues (Q&A pairs).

```cpp
cvisa::SimulatedDevice device("keysight_6640a");
device.addDialogue("*IDN?", "Keysight Technologies,6641A,SN00000001,1.0");
device.addDialogue("VOLTage?", "5.000");
device.addDialogue("OUTPut 1");  // Command without response
```

**Features:**
- Store multiple command-response pairs (dialogues)
- Exact matching for common commands
- Pattern matching with wildcards (* and ?)
- Session-specific state storage (`getState`/`setState`)

### 2. **SimulatedVISABackend**
Implements the `IVISABackend` interface to simulate all VISA operations.

```cpp
auto backend = std::make_unique<cvisa::SimulatedVISABackend>();
backend->registerDevice("GPIB0::5::INSTR", device);
```

**Features:**
- Tracks session-to-resource mappings
- Tracks last-written commands (for query-response handling)
- Routes commands to appropriate simulated devices
- Returns simulated responses

### 3. **Simulations.hpp**
Pre-configured device factories for common instruments.

```cpp
// Pre-configured Keysight 6640A with typical dialogues
auto device = cvisa::simulations::createKeysight6640A();

// Pre-configured backend with multiple resources
auto backend = cvisa::simulations::createKeysightSimulation();
```

## Usage Patterns

### Pattern 1: Quick Testing with Pre-configured Devices

```cpp
#include "src/core/VISACom.hpp"
#include "src/core/Simulations.hpp"

int main() {
    // Create pre-configured backend
    auto backend = cvisa::simulations::createKeysightSimulation();
    
    // Create VISACom with simulated backend
    cvisa::VISACom com(backend, false);
    
    // Connect to simulated resource
    com.connect("GPIB0::5::INSTR");
    
    // All operations are simulated!
    std::string idn = com.query("*IDN?");
    com.write("OUTPut 1");
    std::string voltage = com.query("VOLTage?");
    
    com.disconnect();
    return 0;
}
```

### Pattern 2: Custom Device Configuration

```cpp
auto backend = std::make_unique<cvisa::SimulatedVISABackend>();

// Create custom device
cvisa::SimulatedDevice myDevice("my_psu");
myDevice.addDialogue("*IDN?", "Custom PSU,Model-X,12345,1.0");
myDevice.addDialogue("VOLTage 10.0");
myDevice.addDialogue("VOLTage?", "10.000");
myDevice.addDialogue("CURRent?", "2.500");

// Register on multiple resource strings
backend->registerDevice("GPIB0::5::INSTR", myDevice);
backend->registerDevice("TCPIP0::192.168.1.100::inst0::INSTR", myDevice);

// Use with VISACom
cvisa::VISACom com(backend, false);
com.connect("GPIB0::5::INSTR");
// ...
```

### Pattern 3: Driver Testing with Google Test

```cpp
#include <gtest/gtest.h>
#include "src/core/SimulatedVISABackend.hpp"
#include "src/core/Simulations.hpp"

class PowerSupplyDriverTest : public ::testing::Test {
protected:
    std::unique_ptr<cvisa::SimulatedVISABackend> backend;
    std::shared_ptr<cvisa::IVISABackend> backendPtr;
    
    void SetUp() override {
        backend = std::make_unique<cvisa::SimulatedVISABackend>();
        backend->registerDevice("GPIB0::5::INSTR", 
                              cvisa::simulations::createKeysight6640A());
        backendPtr = backend;
    }
};

TEST_F(PowerSupplyDriverTest, QueryIdentity) {
    cvisa::VISACom com(backendPtr, false);
    com.connect("GPIB0::5::INSTR");
    
    std::string idn = com.query("*IDN?");
    EXPECT_THAT(idn, HasSubstr("Keysight"));
    
    com.disconnect();
}
```

### Pattern 4: Driver Integration Testing

Create a driver that works with both real and simulated backends:

```cpp
class PowerSupply : public cvisa::drivers::SCPIBase {
public:
    // Constructor accepts optional backend (uses RealVISABackend by default)
    explicit PowerSupply(std::shared_ptr<cvisa::IVISABackend> backend = nullptr)
        : SCPIBase(backend) {}
    
    // ... driver methods ...
};

// In production: uses RealVISABackend automatically
PowerSupply psu;
psu.connect("GPIB0::5::INSTR");

// In testing: inject SimulatedVISABackend
auto testBackend = cvisa::simulations::createKeysightSimulation();
PowerSupply testPSU(testBackend);
testPSU.connect("GPIB0::5::INSTR");
```

## Dialogue Format

Dialogues are command-response pairs that simulate SCPI interactions.

### Basic Format

```cpp
device.addDialogue("*IDN?", "Keysight Technologies,6641A,SN00000001,1.0");
device.addDialogue("OUTPut 1");  // Command without response (empty string)
```

### Matching Rules

1. **Exact matching (primary):** Command must match dialogue query exactly
2. **Pattern matching (fallback):** Using wildcards:
   - `*` matches any sequence of characters
   - `?` matches any single character

Examples:
```cpp
device.addDialogue("VOLTage?", "5.000");      // Exact: "VOLTage?"
device.addDialogue("VOLTage *", "");          // Pattern: "VOLTage 5.0", "VOLTage 10.0"
device.addDialogue("MEASure:*", "");          // Pattern: "MEASure:VOLTage?", "MEASure:CURRent?"
```

### Terminator Handling

The simulation backend automatically:
- Adds `\n` terminators to responses if not already present
- Trims whitespace from incoming commands
- Maintains proper formatting

## Pre-configured Devices

### Keysight 6640A/6641A Power Supply

```cpp
auto device = cvisa::simulations::createKeysight6640A();
backend->registerDevice("GPIB0::5::INSTR", device);
```

**Supported commands:**
- `*IDN?` - Device identification
- `*RST`, `*CLS`, `*OPC?` - Standard commands
- `OUTPut`, `OUTPut?` - Output control
- `VOLTage`, `VOLTage?`, `MEASure:VOLTage?` - Voltage control and measurement
- `CURRent`, `CURRent?`, `MEASure:CURRent?` - Current control and measurement
- `VOLTage:PROTection`, `CURRent:PROTection:STATe` - Protection settings

### Agilent 66311B Power Module

```cpp
auto device = cvisa::simulations::createAgilent66311B();
```

**Supported commands:**
- Basic IEEE-488.2 commands
- Output control
- Voltage and current queries

### Generic SCPI Device

```cpp
auto device = cvisa::simulations::createGenericSCPIDevice();
```

**Supported commands:**
- Generic SCPI command set
- System status and error queries
- Suitable for basic testing

## Resource String Mapping

Resources are mapped using standard VISA naming conventions:

```cpp
// GPIB resources
backend->registerDevice("GPIB0::5::INSTR", device);
backend->registerDevice("GPIB0::6::INSTR", device);

// TCPIP resources
backend->registerDevice("TCPIP0::192.168.1.100::inst0::INSTR", device);
backend->registerDevice("TCPIP0::hostname::inst0::INSTR", device);

// USB resources
backend->registerDevice("USB0::0x2A8D::0x0001::SN00000001::INSTR", device);

// Simulated resources (common for testing)
backend->registerDevice("TCPIP0::SIM::inst0::INSTR", device);
```

## Advanced Features

### Device State Management

Store and retrieve persistent state within a device:

```cpp
device.setState("mode", "fast");
std::string mode = device.getState("mode");
```

Use cases:
- Track output state changes
- Simulate stateful behavior
- Track measurement history

### Session Isolation

Each connection gets its own session with independent command tracking:

```cpp
// Two independent connections to the same device
com1.connect("GPIB0::5::INSTR");
com2.connect("GPIB0::5::INSTR");

// Each maintains its own state
com1.write("OUTPut 1");
com2.query("OUTPut?");  // Might return different response based on history
```

### Multiple Devices on One Backend

```cpp
backend->registerDevice("GPIB0::5::INSTR", psuDevice);
backend->registerDevice("GPIB0::6::INSTR", dmmDevice);
backend->registerDevice("GPIB0::7::INSTR", siggenDevice);

// Different drivers can connect to different devices
com_psu.connect("GPIB0::5::INSTR");
com_dmm.connect("GPIB0::6::INSTR");
com_sig.connect("GPIB0::7::INSTR");
```

## Comparison with PyVisa-Sim

| Feature | cVISA Simulation | PyVisa-Sim |
|---------|-----------------|-----------|
| Language | C++11 | Python |
| Integration | IVISABackend abstraction | Monkey-patching |
| Dialogue Format | C++ API | YAML files |
| Type Safety | Compile-time | Runtime |
| Performance | Native C++, minimal overhead | Python interpreter |
| Use Case | C++ driver development | Python driver development |

## Testing Best Practices

### 1. **Test Isolation**
Each test should use a fresh backend instance:

```cpp
void SetUp() override {
    backend = std::make_unique<cvisa::SimulatedVISABackend>();
    backend->registerDevice("GPIB0::1::INSTR", device);
}
```

### 2. **Resource Names Matter**
Use consistent, self-documenting resource names:

```cpp
backend->registerDevice("GPIB0::PSU1::INSTR", psuDevice);  // Clear
backend->registerDevice("GPIB0::1::INSTR", psuDevice);     // Ambiguous
```

### 3. **Document Expected Behaviors**
Include comments explaining what dialogues simulate:

```cpp
// Simulate power supply that remembers output state
device.addDialogue("OUTPut 1");          // Enable output
device.addDialogue("OUTPut 0");          // Disable output
device.addDialogue("OUTPut?", "1");      // Returns last set state
```

### 4. **Use Pre-configured Factories**
Leverage existing device configurations for consistency:

```cpp
// Prefer:
backend->registerDevice("GPIB0::5::INSTR", 
                       cvisa::simulations::createKeysight6640A());

// Over manual configuration (when possible)
```

## Extending with Custom Devices

To add support for new instruments:

1. **Create device class** (optional):
```cpp
// src/core/Simulations.hpp
inline SimulatedDevice createMyCustomDevice() {
    SimulatedDevice device("my_device");
    device.addDialogue("*IDN?", "My Vendor,Model-X,SN123,1.0");
    // Add all your command-response pairs
    return device;
}
```

2. **Use in your tests**:
```cpp
backend->registerDevice("GPIB0::1::INSTR", 
                       cvisa::simulations::createMyCustomDevice());
```

3. **Consider contributing** pre-configured devices back to the project!

## Troubleshooting

### Problem: Unknown Command Returns Empty Response
**Expected behavior.** If a command isn't in the device's dialogues, the response is empty.

**Solution:** Add the dialogue to your device:
```cpp
device.addDialogue("UNKNOWN:COMMAND?", "response");
```

### Problem: Connection Fails to Non-existent Resource
**Expected behavior.** SimulatedVISABackend checks resource registration.

**Solution:** Register the resource first:
```cpp
backend->registerDevice("GPIB0::5::INSTR", device);
```

### Problem: Test Works with Simulated Backend but Fails with Real Hardware
**Likely cause:** Simulation responses don't match actual hardware behavior.

**Solution:** Update device dialogues to match real hardware responses:
```cpp
// Test with real hardware first to capture actual responses
// Then update simulation accordingly
```

## Building and Running Tests

```bash
# Build all tests including simulation tests
cmake --build build

# Run simulation tests (no VISA library required)
ctest --test-dir build -R SimulatedDevice_test -V

# Run VISA tests (requires VISA SDK - Windows/MSVC only)
ctest --test-dir build -R VISACom_test -V
```

## Related Documentation

- [VISACom.hpp](../src/core/VISACom.hpp) - Core VISA communication wrapper
- [IVISABackend.hpp](../src/core/IVISABackend.hpp) - Backend abstraction interface
- [SCPIBase.hpp](../src/core/SCPIBase.hpp) - SCPI driver base class
- [AGENTS.md](../AGENTS.md) - Driver development guide

## Conclusion

The cVISA simulation backend brings the power and flexibility of PyVisa-sim to C++ driver development. It enables:

- **Hardware-free testing** during development
- **Continuous integration** without physical instruments
- **Reproducible test scenarios** with predefined responses
- **Multi-instrument simulation** in a single test
- **Driver development** without VISA SDK installation

By using the simulation backend, you can develop robust SCPI drivers with confidence, test edge cases reliably, and ensure your drivers work correctly before deployment to real hardware.
