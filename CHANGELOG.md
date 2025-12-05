# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- `drivers/ThermalAirTA5000`: A new, comprehensive instrument driver for the MPI Thermal TA-5000.
- `InstrumentDriver::executeCommandChain()` for sending multiple `WRITE` commands in a single operation.
- `CHANGELOG.md` to document changes to the project.
- `examples/ta5000_usage.cpp`: A new example demonstrating the usage of the `ThermalAirTA5000` driver.

### Changed
- **`Agilent66xxA` Driver**: Significantly enhanced the driver with new commands for over-voltage/over-current protection, display control, and the trigger subsystem.
- **Logging Engine**: Refactored the `Logger` to support multiple output sinks (e.g., console and file) simultaneously.
- **Common Commands**: Refactored common SCPI command definitions into a public `CommonCommands` struct for better reusability and discoverability.
- **`InstrumentDriver`**: Enhanced Doxygen documentation for all public and protected methods.
