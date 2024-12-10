#ifndef ARGS_H
#define ARGS_H

#include <windows.h>

/**
 * @file args.h
 * @brief Declarations for argument parsing and ANSI enabling functions.
 */

/**
 * @brief Parses command-line arguments and sets the appropriate flags for immediate actions.
 *
 * @param argc Argument count
 * @param argv Argument values
 * @param startImmediate Pointer to BOOL that will be set if -S/-s is present
 * @param terminateImmediate Pointer to BOOL that will be set if -T/-t is present
 */
void parseArguments(int argc, char *argv[], BOOL *startImmediate, BOOL *terminateImmediate);

/**
 * @brief Enables ANSI escape sequences in the Windows console if possible.
 */
void enableAnsiIfPossible(void);

#endif // ARGS_H
