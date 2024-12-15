#include <windows.h>
#include <string.h>
#include "args.h"
#include "utils.h"

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
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i] != NULL)
            {
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
                else
                {
                    qprintf("[-] Warning: Unrecognized argument '%s'\n", argv[i]);
                }
            }
            else
            {
                qprintf("[-] Warning: NULL argument encountered.\n");
            }
        }
    }
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
                qprintf("[-] Failed to enable ANSI support. Error: %lu\n", GetLastError());
            }
        }
    }
}