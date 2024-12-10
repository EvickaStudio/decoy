# Decoy

Decoy is a lightweight tool that launches multiple dummy processes named after common analysis and debugging tools. By imitating known tools, Decoy aims to deter simple malware checks that look for these processes before executing malicious code. In other words, it acts as a "decoy" environment, making malware believe it is under scrutiny by analysts or monitoring tools. - Chatty ^^

## Features

- Launches dummy processes to mimic well-known analysis/debugging programs
- Uses minimal resources for each dummy process (no console for the dummy's, ~0.3MB memory each)
- Interactive mode for starting, terminating, and restarting all processes
- Non-interactive modes via command-line arguments
- Useful for testing software/malware behavior in an environment that appears monitored or "add another layer of security" (not a substitute for proper security measures)

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
