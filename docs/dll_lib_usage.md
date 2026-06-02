# DLL and Library Usage Guide

This guide explains how to build and use `cvisa` as a pre-built static or shared library (DLL).

## 1. Building the Library

You can build `cvisa` using CMake. By default, it builds a static library.

### Static Library (default)
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Shared Library (DLL)
To build a shared library, set the `BUILD_SHARED_LIBS` flag to `ON`:
```bash
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .
```

## 2. Installation

To install the library and headers to a specific directory:
```bash
cmake -DCMAKE_INSTALL_PREFIX=/path/to/install ..
cmake --build . --target install
```
This will create:
- `include/`: All headers (`.hpp`, `.tpp`) and the `visa.h` shim.
- `lib/`: The compiled library (`cvisa.lib`, `libcvisa.a`, or `cvisa.dll`).

## 3. Integrating into Your Project

### Using Pre-built Binaries
1. Add the `include` folder to your compiler's include path.
2. Link your application against the `cvisa` library.
3. If using the DLL version, ensure the `.dll` (Windows) or `.so` (Linux) is in your application's execution path.

### Using CMake `find_package` (Coming Soon)
For now, you can link directly:
```cmake
add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE /path/to/cvisa/lib/cvisa.lib)
target_include_directories(MyApp PRIVATE /path/to/cvisa/include)
```

## 4. Dependencies
`cvisa` dynamically or statically links against the VISA C API. Ensure your runtime environment has the VISA Shared components installed.
