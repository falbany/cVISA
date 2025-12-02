# CMakeLists.txt for the cvisa project

cmake_minimum_required(VERSION 3.10)
project(cvisa LANGUAGES CXX)

# --- Project Settings ---
# Set the C++ standard to C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# --- Build the cvisa Library ---
# Create a static library target from the source files.
add_library(cvisa
    src/core/VisaInterface.cpp
    src/core/InstrumentDriver.cpp
    src/core/exceptions.cpp
    src/utils/utils.cpp
    src/drivers/PowerSupply.cpp
    src/drivers/Agilent66xxA.cpp
)

# Make the 'src' directory publicly available for includes.
# By setting this to PUBLIC, any target that links against cvisa (like the example)
# will also inherit this include directory. This allows for clean includes, e.g.,
# #include "VisaInstrument.hpp" instead of #include "src/VisaInstrument.hpp"
target_include_directories(cvisa
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# --- Find and Link the VISA Library ---
# The VISA library is a core dependency. The user must have a VISA implementation
# (e.g., from National Instruments, Keysight, R&S) installed on their system.
# The following logic attempts to find the library automatically.

if(WIN32)
    # On Windows, the library is typically named visa32.lib or visa64.lib.
    # We provide hints to the common installation directories for the IVI standard.
    find_library(VISA_LIBRARY
        NAMES visa64 visa32
        HINTS
            "C:/Program Files/IVI Foundation/VISA/Win64/lib_x64/msc"
            "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc"
        DOC "Path to the VISA library (visa32.lib or visa64.lib)"
    )
else()
    # On Linux and other UNIX-like systems, the library is typically a shared
    # object named libvisa.so.
    find_library(VISA_LIBRARY
        NAMES visa
        HINTS
            "/usr/local/lib"
            "/usr/lib"
            "/usr/lib64"
        DOC "Path to the VISA library (libvisa.so)"
    )
endif()

if(NOT VISA_LIBRARY)
    message(FATAL_ERROR "VISA library not found. Please ensure a VISA SDK is installed. "
                        "If it's in a non-standard location, you may need to set "
                        "the CMAKE_PREFIX_PATH or manually specify the library path.")
else()
    message(STATUS "Found VISA library: ${VISA_LIBRARY}")
    # Link our cvisa library against the found VISA library.
    # This dependency is PRIVATE because consumers of cvisa should not need to
    # know about or link against the VISA C API directly.
    target_link_libraries(cvisa PRIVATE ${VISA_LIBRARY})
endif()


# --- Build the Example Application ---
# This demonstrates how a consumer would use the cvisa library.

# Add the example executable target from its source file.
add_executable(example_app
    examples/basic_usage.cpp
)

# Link the example application against our cvisa library.
# CMake automatically handles setting up include paths and linking because
# we defined these properties as PUBLIC on the cvisa target.
target_link_libraries(example_app PRIVATE cvisa)

# Optional: Add a message to guide the user on how to build.
message(STATUS "CVisa library and example configured. To build, run your build tool (e.g., 'make' or 'ninja').")