# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- `InstrumentDriver::executeCommandChain()` for sending multiple `WRITE` commands in a single operation.
- `CHANGELOG.md` to document changes to the project.

### Changed
- Refactored common SCPI command definitions into a public `CommonCommands` struct for better reusability and discoverability.
- Removed the private `s_common_command_registry` from `InstrumentDriver`.
