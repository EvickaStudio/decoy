# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.0] - 2024-08-20

### Added
- Initial release of Decoy Manager
- Support for creating dummy processes mimicking analysis tools
- Interactive mode with S/T/R/Q commands
- Command-line options for immediate start/terminate
- Quiet mode operation
- Safe process management with DecoyIdentifier UUID
- Version information verification before termination
- ANSI color support in Windows console

### Improved  
- Modernized CMake build system with target-based approach
- Added configuration header (config.h) for centralized constants
- Enhanced input validation and error handling
- Added bounds checking and buffer overflow protection
- Implemented help system with -h/--help support
- Improved code documentation and function safety
- Added named constants to replace magic numbers
- Better string operation safety with snprintf return checking

### Security
- Added path validation to prevent directory traversal
- Enhanced process verification before termination
- Improved buffer safety in string operations
- Added input parameter validation