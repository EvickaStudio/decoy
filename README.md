# Decoy

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A lightweight Windows utility that creates dummy processes mimicking common analysis and debugging tools. Decoy helps test software behavior in monitored environments by simulating the presence of analysis tools.

## Overview

Decoy creates harmless process imitations of well-known analysis and debugging tools. This can be useful for:
- Testing software behavior in environments that appear to be monitored
- Adding an extra layer of deterrence against malware that checks for analysis tools
- Simulating a monitored environment for testing purposes

> **Note**: Decoy is not a substitute for proper security measures. It should be used as part of a broader security strategy.

## Features

- **Lightweight Process Simulation**
  - Creates minimal resource footprint (~0.3MB per process)
  - No console windows for dummy processes
  - Safe process management with unique identifiers

- **Process Management**
  - Interactive and non-interactive operation modes
  - Start, stop, and restart capabilities
  - Safe termination with process verification

- **Safety Mechanisms**
  - Unique DecoyIdentifier UUID for each process
  - Version information verification before termination
  - Protection against accidental termination of legitimate processes

## Installation

### Building from Source

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Alternatively:
- Use the provided `build.bat` script
- Download pre-built binaries from the [Releases](https://github.com/EvickaStudio/decoy/releases/latest) page

## Usage

### Interactive Mode

Run `decoy-manager` without arguments to access the interactive menu:

| Key | Action |
|-----|--------|
| `S` | Start all decoy processes |
| `T` | Terminate all processes |
| `R` | Restart all processes |
| `Q` | Quit and clean up |

### Command-Line Options

```bash
decoy-manager [-S|-T|-Q|-h]
```

| Option | Description |
|--------|-------------|
| `-S, -s` | Start all processes and exit |
| `-T, -t` | Terminate all processes and exit |
| `-Q, -q` | Quiet mode: start processes without output |
| `-h, --help` | Show help information |

### Simulated Processes

Decoy creates dummy processes for common analysis tools including:
- ProcessHacker.exe
- procmon.exe
- Wireshark.exe
- IDA.exe
- OllyDbg.exe
- And more...

## Technical Details

### Process Safety

Each dummy process includes a unique identifier in its version information:
```plaintext
VALUE "DecoyIdentifier", "0193b58d-cf59-703c-afda-a8c62c43f6b0"
```

This identifier ensures that:
1. Only Decoy-created processes can be terminated by the manager
2. Legitimate tools with matching names remain unaffected
3. Process management operations are safe and targeted

## Compatibility Warning

Some applications, particularly games with anti-cheat systems, may detect and react to Decoy's processes. For example:
- Certain games may refuse to launch
- Anti-cheat systems might flag the presence of analysis tool names
- Some applications may require specific processes to be stopped

## Contributing

Contributions are welcome! Please read our [Contributing Guidelines](CONTRIBUTING.md) before submitting pull requests.

For information about changes and releases, see the [Changelog](CHANGELOG.md).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
