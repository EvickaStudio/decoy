#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <stdarg.h>
#include <tlhelp32.h>
#include "utils.h"

static BOOL quietMode = FALSE;

/**
 * @file utils.c
 * @brief Utility functions including qprintf, fileExists, killProcessByName, and quiet mode handling.
 */

/**
 * @brief Conditioned print function that prints only if quietMode is FALSE.
 *
 * @param fmt Format string
 * @param ... Arguments for format
 */
void qprintf(const char *fmt, ...)
{
    if (!quietMode)
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        fflush(stdout);
    }
}

/**
 * @brief Checks if a file exists.
 *
 * @param filename The path to the file.
 * @return TRUE if exists, FALSE otherwise.
 */
BOOL fileExists(const char *filename)
{
    return (_access_s(filename, 0) == 0);
}

/**
 * @brief Kills all processes by a given name.
 *
 * Uses a snapshot of system processes and compares against pname.
 *
 * @param pname Name of the process (e.g. "procmon.exe").
 */
void killProcessByName(const char *pname)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        qprintf("[-] Failed to create snapshot. Error: %lu\n", GetLastError());
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);

    if (!Process32First(hSnapshot, &pe))
    {
        qprintf("[-] Failed to retrieve first process. Error: %lu\n", GetLastError());
        CloseHandle(hSnapshot);
        return;
    }

    do
    {
        if (_strnicmp(pe.szExeFile, pname, MAX_PATH) == 0)
        {
            HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
            if (hProc)
            {
                TerminateProcess(hProc, 0);
                WaitForSingleObject(hProc, 2000);
                CloseHandle(hProc);
                qprintf("[+] Terminated %s (PID: %lu)\n", pname, pe.th32ProcessID);
            }
        }
    } while (Process32Next(hSnapshot, &pe));

    CloseHandle(hSnapshot);
}

/**
 * @brief Sets the global quiet mode.
 *
 * @param mode TRUE to enable quiet mode, FALSE otherwise.
 */
void setQuietMode(BOOL mode)
{
    quietMode = mode;
}

/**
 * @brief Checks if quiet mode is enabled.
 *
 * @return TRUE if quiet, FALSE otherwise.
 */
BOOL isQuietMode(void)
{
    return quietMode;
}
