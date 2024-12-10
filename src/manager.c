#include <windows.h>
#include <stdio.h>
#include "process_control.h"
#include "banner.h"
#include "args.h"
#include "utils.h"

/**
 * @file manager.c
 * @brief The main entry point for the Decoy Manager program.
 *
 * This file sets up the environment, parses arguments, and either runs in
 * interactive mode or performs requested immediate actions (start/terminate quietly).
 */

int main(int argc, char *argv[])
{
    // Initialize process running states
    for (int i = 0; i < getProcessCount(); i++)
    {
        setProcessRunningState(i, FALSE);
    }

    BOOL startImmediate = FALSE;
    BOOL terminateImmediate = FALSE;

    // Parse command line arguments to decide what actions to take
    parseArguments(argc, argv, &startImmediate, &terminateImmediate);

    // Quiet start
    if (isQuietMode() && startImmediate && !terminateImmediate)
    {
        ensureProcessesDirectoryAndCopies();
        startAllProcesses();
        return 0;
    }

    // Start immediately with banner
    if (startImmediate && !terminateImmediate)
    {
        printBanner();
        qprintf("[*] Starting all processes as requested by command-line argument.\n");
        ensureProcessesDirectoryAndCopies();
        startAllProcesses();
        return 0;
    }

    // Terminate immediately
    if (terminateImmediate)
    {
        printBanner();
        qprintf("[*] Terminating all processes as requested by command-line argument.\n");
        terminateAllProcesses();
        return 0;
    }

    // Otherwise, run interactively
    enableAnsiIfPossible();
    interactiveMode();

    return 0;
}