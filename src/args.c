#include <windows.h>
#include <string.h>
#include "args.h"
#include "utils.h"
#include "logger.h"
#include "config.h"
#include "logger.h"

/**
 * @file args.c
 * @brief Argument parsing and ANSI enabling functions.
 *
 * This file contains functions to parse command-line arguments to determine if the program should
 * start processes immediately, terminate them, or run quietly. It also includes enabling ANSI terminal
 * sequences on Windows if possible.
 */

/**
 * @brief Parses command-line arguments to set flags for immediate start/terminate and quiet mode.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @param startImmediate Set TRUE if -S/-s is found
 * @param terminateImmediate Set TRUE if -T/-t is found
 */
void parseArguments(int argc, char *argv[], BOOL *startImmediate, BOOL *terminateImmediate)
{
    // Validate input parameters
    if (startImmediate == NULL || terminateImmediate == NULL)
    {
        WARN("Invalid parameters passed to parseArguments");
        return;
    }

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i] != NULL)
            {
                // Skip empty arguments
                if (strlen(argv[i]) == 0)
                    continue;

                if ((strcmp(argv[i], "-S") == 0) || (strcmp(argv[i], "-s") == 0))
                {
                    *startImmediate = TRUE;
                }
                else if ((strcmp(argv[i], "-T") == 0) || (strcmp(argv[i], "-t") == 0))
                {
                    *terminateImmediate = TRUE;
                }
                else if ((strcmp(argv[i], "-Q") == 0) || (strcmp(argv[i], "-q") == 0))
                {
                    setQuietMode(TRUE);
                    *startImmediate = TRUE;
                }
                else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0) || 
                         (strcmp(argv[i], "-?") == 0) || (strcmp(argv[i], "/?") == 0))
                {
                    printUsage();
                    exit(0);
                }
                else
                {
                    WARN("Unrecognized argument '%s'. Use -h for help.", argv[i]);
                }
            }
            else
            {
                WARN("Warning: NULL argument encountered.");
            }
        }
    }
}

/**
 * @brief Prints usage information and available command-line options.
 */
void printUsage(void)
{
    printf("Decoy Manager v%s\n", DECOY_VERSION_STRING);
    printf("A lightweight Windows utility that creates dummy processes mimicking analysis tools.\n\n");
    printf("Usage: decoy-manager [OPTIONS]\n\n");
    printf("Options:\n");
    printf("  -S, -s    Start all decoy processes and exit\n");
    printf("  -T, -t    Terminate all decoy processes and exit\n");
    printf("  -Q, -q    Quiet mode: start processes without output\n");
    printf("  -h, --help, -?, /?    Show this help message\n\n");
    printf("When run without arguments, enters interactive mode.\n\n");
    printf("Interactive Commands:\n");
    printf("  [S] Start all processes\n");
    printf("  [T] Terminate all processes\n");
    printf("  [R] Restart all processes\n");
    printf("  [Q] Quit\n\n");
    printf("For more information, visit: https://github.com/EvickaStudio/decoy\n");
}

/**
 * @brief Enables ANSI color support in Windows console if possible.
 */
void enableAnsiIfPossible(void)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (!SetConsoleMode(hOut, dwMode))
            {
                WARN("Failed to enable ANSI support. Error: %lu", GetLastError());
            }
        }
    }
}