# Decoy

Decoy is a lightweight tool that launches multiple dummy processes named after common analysis and debugging tools. By imitating known tools, Decoy aims to deter simple malware checks that look for these processes before executing malicious code. In other words, it acts as a "decoy" environment, making malware believe it is under scrutiny by analysts or monitoring tools. - Chatty ^^

## Features

- Launches dummy processes to mimic well-known analysis/debugging programs
- Uses minimal resources for each dummy process (no console for the dummy's, ~0.3MB memory each)
- Interactive mode for starting, terminating, and restarting all processes
- Non-interactive modes via command-line arguments
- Useful for testing software/malware behavior in an environment that appears monitored or "add another layer of security" (not a substitute for proper security measures)

## Safety

Starting from the newer versions (not in v0.1.0), the dummy process includes an extra entry in the [dummy.rc](resources/dummy.rc) resource file:

```plaintext
VALUE "DecoyIdentifier", "0193b58d-cf59-703c-afda-a8c62c43f6b0\0"
```

This `DecoyIdentifier` with a unique UUID allows the manager to distinguish between the decoy processes it started and legitimate processes with the same name. Before terminating any process, the manager checks for this identifier in the process's version information. If the identifier matches, it proceeds to terminate the process; otherwise, it skips it to avoid interfering with legitimate applications.

## Example Process Names

Decoy includes common tool names such as:

- `ProcessHacker.exe`
- `procmon.exe`
- `Wireshark.exe`
- `IDA.exe`
- `OllyDbg.exe`
- ...

*(Additional names are included in the source code.)*

## Build

To build it yourself with CMake, run the following commands:

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Or run the provided `build.bat` script to build the project.

Or download the latest pre-built binaries from the [Releases](https://github.com/EvickaStudio/decoy/releases/latest) page.

## Usage

**Interactive Mode:**  
Run `decoy-manager` without arguments to open the interactive menu:

- Press `S` to start all decoy processes
- Press `T` to terminate all decoy processes
- Press `R` to restart all decoy processes
- Press `Q` to quit and terminate all decoy processes before exiting

**Non-Interactive Modes:**

- `-S` or `-s`: Start all processes and then exit
- `-T` or `-t`: Terminate all running processes and then exit (when closing the program not properly)
- `-Q` or `-q`: Quiet mode, no terminal output; just start all processes and exit

These command-line options are particularly useful if you want to integrate Decoy into scripts or automation workflows without user interaction.

## Disclaimer

**Note:** Some legitimate programs or games (e.g., Battlefield 2042 with procmon.exe) may use anti-cheat mechanisms that detect and blacklist certain processes. Running Decoy might cause these applications to refuse to start or function improperly until specific processes are stopped. Use Decoy with caution to ensure it does not interfere with your legitimate software.
