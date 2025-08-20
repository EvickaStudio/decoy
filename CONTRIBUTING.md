# Contributing to Decoy

Thank you for your interest in contributing to Decoy! This document provides guidelines for contributing to the project.

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/your-username/decoy.git`
3. Create a feature branch: `git checkout -b feature/your-feature-name`

## Development Environment

### Prerequisites
- Windows operating system (required for building and testing)
- CMake 3.30 or higher
- Microsoft Visual Studio 2019+ or compatible C compiler
- Git for version control

### Building
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Or use the provided `build.bat` script.

## Code Style

- Follow existing code style and formatting
- Use consistent naming conventions
- Include proper documentation for new functions
- Add appropriate error handling and input validation
- Use the logging macros (OKAY, INFO, WARN) for status messages
- Use qprintf() for UI output that respects quiet mode

## Adding New Features

### Adding New Process Names
1. Edit `src/process_control.c` and add entries to the `processNames[]` array
2. Ensure the process count doesn't exceed `MAX_PROCESSES` (defined in `config.h`)
3. Test that the new processes can be started and terminated correctly

### Configuration Changes
- Update `src/config.h` for any new constants or configuration values
- Avoid hardcoding values directly in source files

## Testing

- Test on Windows environments with different privilege levels
- Verify that dummy processes start and terminate correctly
- Test command-line arguments and interactive mode
- Ensure quiet mode works as expected
- Test error conditions and edge cases

## Pull Request Guidelines

1. Provide a clear description of the changes
2. Reference any related issues
3. Include testing instructions
4. Update documentation if needed
5. Update CHANGELOG.md with your changes
6. Ensure your code follows the existing style

## Security Considerations

- Be cautious with file operations and path handling
- Validate all user inputs
- Follow the principle of least privilege
- Test for buffer overflows and memory leaks
- Ensure process verification works correctly

## Code Review

All submissions require review. Please be patient and responsive to feedback.

## Questions?

Feel free to open an issue for questions or discussions about contributing.