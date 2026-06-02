# Direct Source Usage Guide

This guide details how to integrate `cvisa` directly into your C++11 project by including its source files. This approach is ideal for projects that prefer to build all dependencies from source or require deep debugging.

## 1. Include Directories

Add the `src` and `include` directories of `cvisa` to your project's include paths.

**Important:** `cvisa` requires a VISA implementation (e.g., NI-VISA, Keysight VISA) installed on your system. You must also include the VISA headers (typically `visa.h`).

## 2. Add Source Files

Include the necessary `.cpp` files in your build system. `cvisa` is modularized into several components:

### Core Modules (Required)
- `src/core/exceptions.cpp`
- `src/core/Logger.cpp`
- `src/core/VISACom.cpp`
- `src/core/SCPIBase.cpp`

### Driver Modules (Optional - add as needed)
- `src/drivers/Agilent66xxA.cpp`
- `src/drivers/ThermalAirTA5000.cpp`
- `src/drivers/PowerSupply.cpp`

### Utility Modules (Required)
- `src/utils/utils.cpp`

## 3. Link Dependencies

Your project must link against the VISA library (e.g., `visa64.lib`, `visa32.lib`, or `libvisa.so`).

## 4. CMake Example

If you use CMake, you can add the sources to your target directly:

```cmake
# Add cvisa source files
target_sources(YourApplication PRIVATE
    path/to/cvisa/src/core/exceptions.cpp
    path/to/cvisa/src/core/Logger.cpp
    path/to/cvisa/src/core/VISACom.cpp
    path/to/cvisa/src/core/SCPIBase.cpp
    path/to/cvisa/src/utils/utils.cpp
    # Add drivers as needed
    path/to/cvisa/src/drivers/PowerSupply.cpp
)

# Add include directories
target_include_directories(YourApplication PRIVATE
    path/to/cvisa/src
    path/to/cvisa/include
)

# Link against VISA (example for Windows)
target_link_libraries(YourApplication PRIVATE "C:/Program Files/IVI Foundation/VISA/Win64/lib_x64/msc/visa64.lib")
```

## 5. Requirements

- **C++11 or higher**: Ensure your compiler is set to C++11 (`-std=c++11`).
- **VISA SDK**: A VISA provider must be installed on the development and deployment machines.
