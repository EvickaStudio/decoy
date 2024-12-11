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
 * @brief Checks if a file has a specific version information.
 *
 * @param exePath The path to the executable.
 * @return TRUE if the file has the DecoyIdentifier, FALSE otherwise.
 */
BOOL hasDecoyIdentifier(const char *exePath)
{
    DWORD verHandle = 0;
    DWORD verSize = GetFileVersionInfoSizeA(exePath, &verHandle);
    if (verSize > 0)
    {
        LPVOID verData = malloc(verSize);
        if (GetFileVersionInfoA(exePath, verHandle, verSize, verData))
        {
            LPVOID lpBuffer = NULL;
            UINT size = 0;
            if (VerQueryValueA(verData, "\\StringFileInfo\\040904b0\\DecoyIdentifier", &lpBuffer, &size))
            {
                if (lpBuffer && strcmp((char *)lpBuffer, "0193b58d-cf59-703c-afda-a8c62c43f6b0") == 0)
                {
                    free(verData);
                    return TRUE;
                }
            }
        }
        free(verData);
        return FALSE;
    }
    return FALSE;
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

    if (Process32First(hSnapshot, &pe))
    {
        do
        {
            if (_stricmp(pe.szExeFile, pname) == 0)
            {
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProcess)
                {
                    char exePath[MAX_PATH];
                    if (GetModuleFileNameExA(hProcess, NULL, exePath, MAX_PATH))
                    {
                        if (hasDecoyIdentifier(exePath))
                        {
                            if (TerminateProcess(hProcess, 0))
                            {
                                WaitForSingleObject(hProcess, 2000);
                                qprintf("[+] Terminated %s (PID: %lu)\n", pname, pe.th32ProcessID);
                            }
                            else
                            {
                                qprintf("[-] Failed to terminate %s (PID: %lu). Error: %lu\n", pname, pe.th32ProcessID, GetLastError());
                            }
                        }
                    }
                    else
                    {
                        qprintf("[-] GetModuleFileNameExA failed for PID: %lu. Error: %lu\n", pe.th32ProcessID, GetLastError());
                    }
                    CloseHandle(hProcess);
                }
                else
                {
                    qprintf("[-] Cannot open process %s (PID: %lu). Error: %lu\n", pname, pe.th32ProcessID, GetLastError());
                }
            }
        } while (Process32Next(hSnapshot, &pe));
    }

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
