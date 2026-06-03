# ============================================================================
# Test suite for cvisa using Google Test
# ============================================================================

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Force shared CRT for MSVC compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable: VISACom tests (requires VISA library)
add_executable(VISACom_test VISACom_test.cpp)

# Link against the library from the parent scope, GTest, and VISA
target_link_libraries(VISACom_test PRIVATE cvisa gtest_main gmock ${VISA_LIBRARY})

target_include_directories(VISACom_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/internal
)

# Test executable: SimulatedDevice tests (no real VISA library needed)
# This test can run on any platform, including MinGW
add_executable(SimulatedDevice_test SimulatedDevice_test.cpp)

# Link against the library from the parent scope and GTest (no VISA_LIBRARY needed)
target_link_libraries(SimulatedDevice_test PRIVATE cvisa gtest_main gmock)

target_include_directories(SimulatedDevice_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/internal
)

# Register tests with CTest
include(GoogleTest)

# Only register VISACom_test if VISA library is available
if(NOT MINGW)
    gtest_discover_tests(VISACom_test)
endif()

# SimulatedDevice_test works on all platforms
gtest_discover_tests(SimulatedDevice_test)
