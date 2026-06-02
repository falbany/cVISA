# CMakeLists.txt for the cvisa project

cmake_minimum_required(VERSION 3.24)
project(cvisa LANGUAGES CXX)

# --- Project Settings ---
# Set the C++ standard to C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_EXAMPLES "Build example applications" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so)" OFF)

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
target_include_directories(cvisa
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
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


    # Link the example application against our cvisa library.
    # CMake automatically handles setting up include paths and linking because
    # we defined these properties as PUBLIC on the cvisa target.
    target_link_libraries(example_app PRIVATE cvisa)
    target_link_libraries(ta5000_example PRIVATE cvisa)
    target_link_libraries(agilent66xxa_example PRIVATE cvisa)
endif()

# --- Testing ---
enable_testing()
add_subdirectory(tests)

# Optional: Add a message to guide the user on how to build.
message(STATUS "CVisa library and example configured. To build, run your build tool (e.g., 'make' or 'cmake').")
