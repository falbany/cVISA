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

# Test executable
add_executable(VISACom_test VISACom_test.cpp)

# Link against the library from the parent scope and GTest
target_link_libraries(VISACom_test PRIVATE cvisa gtest_main)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(VISACom_test)
