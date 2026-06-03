# CMakeLists.txt for the cvisa project
# This project provides a C++ RAII wrapper around IVI Foundation VISA libraries
# with SCPI layer and instrument driver abstraction

cmake_minimum_required(VERSION 3.24)
project(cvisa VERSION 0.1.0 LANGUAGES CXX)

# --- Project Settings ---
# Set the C++ standard to C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_EXAMPLES "Build example applications" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so)" OFF)
option(BUILD_TESTS "Build test suite" ON)
option(BUILD_SIMULATION "Build simulation support with YAML config" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(BuildTypes)
include(StaticAnalysis)
include(Sanitizers)
include(CodeCoverage)


# --- Source Definitions ---
set(CORE_SOURCES
    src/core/exceptions.cpp
    src/core/Logger.cpp
    src/core/VISACom.cpp
    src/core/SCPIBase.cpp
)

set(DRIVER_SOURCES
    src/drivers/Agilent66xxA.cpp
    src/drivers/ThermalAirTA5000.cpp
    src/drivers/PowerSupply.cpp
)

set(UTILS_SOURCES
    src/utils/utils.cpp
)

set(ALL_SOURCES
    ${CORE_SOURCES}
    ${DRIVER_SOURCES}
    ${UTILS_SOURCES}
)

# --- Build the cvisa Library ---
add_library(cvisa ${ALL_SOURCES})

# Make the 'src' and 'include' directories publicly available for includes.
# The 'src/internal' directory contains IVI Foundation VISA headers
target_include_directories(cvisa
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/internal>
        $<INSTALL_INTERFACE:include>
)


# --- Find and Link the IVI Foundation VISA Library ---
# The VISA library is a core dependency. The user must have a VISA implementation
# (e.g., from National Instruments, Keysight, R&S) installed on their system.
# This library uses IVI Foundation VISA standard types and functions.
#
# Common VISA implementations:
# - National Instruments VISA (NI-VISA)
# - Keysight VISA (formerly Agilent)
# - Rohde & Schwarz VISA (R&S VISA)

if(WIN32)
    # On Windows, the library is typically named visa64.lib or visa32.lib.
    # We provide hints to the common installation directories for IVI Foundation VISA
    find_library(VISA_LIBRARY
        NAMES visa64 visa32
        HINTS
            "C:/Program Files/IVI Foundation/VISA/Win64/lib_x64/msc"
            "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc"
            "C:/Program Files/National Instruments/VISA/lib"
            "C:/Program Files (x86)/National Instruments/VISA/lib"
        DOC "Path to the IVI Foundation VISA library (visa64.lib or visa32.lib)"
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
            "/opt/ni/visa/lib"
        DOC "Path to the IVI Foundation VISA library (libvisa.so)"
    )
endif()

if(NOT VISA_LIBRARY)
    message(FATAL_ERROR "IVI Foundation VISA library not found. Please ensure a VISA SDK is installed. "
                        "Common installations:\n"
                        "  - National Instruments VISA (NI-VISA)\n"
                        "  - Keysight VISA\n"
                        "  - Rohde & Schwarz VISA\n"
                        "If it's in a non-standard location, you may need to set "
                        "the CMAKE_PREFIX_PATH or manually specify the library path.")
else()
    message(STATUS "Found IVI Foundation VISA library: ${VISA_LIBRARY}")
    # Link our cvisa library against the found VISA library.
    # This dependency is PUBLIC so that tests and drivers also link against it.
    target_link_libraries(cvisa PUBLIC ${VISA_LIBRARY})
endif()


# Export VISA library path to cache for subdirectories to use
set(VISA_LIBRARY_FOR_TESTS "${VISA_LIBRARY}" CACHE STRING "VISA library path for tests" FORCE)

# --- Installation ---
install(TARGETS cvisa
    EXPORT cvisaTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY src/ DESTINATION include
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.tpp"
)
install(DIRECTORY include/ DESTINATION include)


# --- Build the Example Application ---
if(BUILD_EXAMPLES)
    # Add the example executable target from its source file.
    add_executable(example_app
        examples/basic_usage.cpp
    )
    add_executable(ta5000_example
        examples/ta5000_usage.cpp
    )
    add_executable(agilent66xxa_example
        examples/agilent66xxa_usage.cpp
    )
    add_executable(simulated_device_example
        examples/simulated_device_usage.cpp
    )

    # Link the example application against our cvisa library.
    # CMake automatically handles setting up include paths and linking because
    # we defined these properties as PUBLIC on the cvisa target.
    target_link_libraries(example_app PRIVATE cvisa)
    target_link_libraries(ta5000_example PRIVATE cvisa)
    target_link_libraries(agilent66xxa_example PRIVATE cvisa)
    target_link_libraries(simulated_device_example PRIVATE cvisa)
endif()

# --- Tests ---
if(BUILD_TESTS)
    enable_testing()
    
    # Check if we're using MinGW (incompatible with MSVC VISA SDK)
    if(MINGW)
        message(WARNING "MinGW detected - VISA tests will be skipped due to linker incompatibility. "
                        "Use MSVC or a compatible VISA SDK for MinGW to run tests. "
                        "Simulation tests (no VISA required) will still be built.")
        # Add only simulation tests (no VISA library needed)
        add_subdirectory(tests)
        # Remove VISA-dependent test from build
        set_target_properties(VISACom_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
    else()
        add_subdirectory(tests)
    endif()
endif()

# --- Tests ---
if(BUILD_TESTS)
    enable_testing()
    
    # Check if we're using MinGW (incompatible with MSVC VISA SDK)
    if(MINGW)
        message(WARNING "MinGW detected - VISA tests will be skipped due to linker incompatibility. "
                        "Use MSVC or a compatible VISA SDK for MinGW to run tests.")
        # Skip tests when using MinGW
    else()
        add_subdirectory(tests)
    endif()
endif()

# Optional: Add a message to guide the user on how to build.
message(STATUS "CVisa library and example configured. To build, run your build tool (e.g., 'make' or 'cmake').")

# --- Simulation Support (nlohmann/json for YAML/JSON parsing) ---
if(BUILD_SIMULATION)
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    )
    FetchContent_MakeAvailable(nlohmann_json)
    
    # Add nlohmann_json to the cvisa library dependencies
    target_link_libraries(cvisa PRIVATE nlohmann_json::nlohmann_json)
    
    # Add include directory for SimulationConfig.hpp
    target_include_directories(cvisa PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
endif()
