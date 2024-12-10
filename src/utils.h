#ifndef UTILS_H
#define UTILS_H

#include <windows.h>

/**
 * @file utils.h
 * @brief Utility function declarations for printing, file existence checks, and process killing by name.
 */

/**
 * @brief Prints formatted output if not in quiet mode.
 *
 * @param fmt Format string
 * @param ... Additional arguments
 */
void qprintf(const char *fmt, ...);

/**
 * @brief Checks if a file exists.
 *
 * @param filename Path to the file.
 * @return BOOL TRUE if exists, otherwise FALSE.
 */
BOOL fileExists(const char *filename);

/**
 * @brief Kills all running instances of processes with a given name.
 *
 * @param pname Process name (e.g. "procmon.exe")
 */
void killProcessByName(const char *pname);

/**
 * @brief Sets quiet mode on/off.
 *
 * @param mode TRUE for quiet, FALSE for verbose.
 */
void setQuietMode(BOOL mode);

/**
 * @brief Checks if quiet mode is currently enabled.
 *
 * @return BOOL TRUE if quiet, FALSE otherwise.
 */
BOOL isQuietMode(void);

#endif // UTILS_H
