#ifndef PROCESS_CONTROL_H
#define PROCESS_CONTROL_H

#include <windows.h>
#include <stdbool.h>

/**
 * @file process_control.h
 * @brief Function and data declarations for controlling decoy processes.
 *
 * This header provides interfaces for starting, terminating, restarting, and ensuring the directory structure
 * for the decoy processes. It also provides accessors for process count and names.
 */

typedef struct
{
    PROCESS_INFORMATION pi;
    BOOL running;
} FakeProcess;

/**
 * @brief Get total number of decoy processes.
 * @return int Number of processes.
 */
int getProcessCount(void);

/**
 * @brief Get the process name by index.
 *
 * @param index Zero-based index into the process list.
 * @return const char* The name of the process or NULL if out of range.
 */
const char *getProcessName(int index);

/**
 * @brief Sets the running state of a process by index.
 *
 * @param index Index of the process
 * @param running TRUE if running, FALSE otherwise
 */
void setProcessRunningState(int index, BOOL running);

/**
 * @brief Gets the running state of a process.
 *
 * @param index Index of the process
 * @return BOOL TRUE if running, FALSE otherwise.
 */
BOOL getProcessRunningState(int index);

/**
 * @brief Gets the PROCESS_INFORMATION struct for a given process.
 *
 * @param index Index of the process.
 * @return PROCESS_INFORMATION* Pointer or NULL if out of range.
 */
PROCESS_INFORMATION *getProcessInfo(int index);

/**
 * @brief Ensure the "processes" directory and dummy copies are created.
 */
void ensureProcessesDirectoryAndCopies(void);

/**
 * @brief Start all processes.
 */
void startAllProcesses(void);

/**
 * @brief Terminate all processes.
 */
void terminateAllProcesses(void);

/**
 * @brief Restart all processes (terminate, copy, start).
 */
void restartAllProcesses(void);

/**
 * @brief Run interactive mode to handle user input (S/T/R/Q).
 */
void interactiveMode(void);

#endif // PROCESS_CONTROL_H
