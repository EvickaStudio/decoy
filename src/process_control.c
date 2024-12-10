#include <windows.h>
#include <stdio.h>
#include <io.h>
#include "process_control.h"
#include "utils.h"

// Global storage of process info
static FakeProcess processes[64];
static BOOL processesInitialized = FALSE;
static BOOL quietMode = FALSE; // Local tracking, actual quietMode is in utils if needed

// Dummy tool names to mimic
static const char *processNames[] = {
    "autoruns.exe",
    "autorunsc.exe",
    "avgui.exe",
    "blnsvr.exe",
    "csfalconservice.exe",
    "daq64.exe",
    "dumpcap.exe",
    "Fiddler.exe",
    "filemon.exe",
    "HookExplorer.exe",
    "ImmunityDebugger.exe",
    "ImportREC.exe",
    "joeboxcontrol.exe",
    "joeboxserver.exe",
    "LordPE.exe",
    "PETools.exe",
    "prl_tools.exe",
    "ProcessHacker.exe",
    "procmon.exe",
    "proc_analyzer.exe",
    "qemu-ga.exe",
    "regmon.exe",
    "ResourceHacker.exe",
    "sniff_hit.exe",
    "SysInspector.exe",
    "sys_analyzer.exe",
    "taniumclient.exe",
    "tcpview.exe",
    "template.exe",
    "vboxservice.exe",
    "vboxtray.exe",
    "vdagent.exe",
    "vdservice.exe",
    "vmsrvc.exe",
    "vmtoolsd.exe",
    "vmwaretray.exe",
    "vmwareuser.exe",
    "windbg.exe",
    "Wireshark.exe",
    "x32dbg.exe",
    "x64dbg.exe",
    "xagt.exe",
    "xenservice.exe",
    "OllyDbg.exe",
    "IDA.exe",
    "IDA64.exe",
    "DbgView.exe",
    "Procexp.exe",
    "Procexp64.exe",
    "Procdump.exe",
    "Strings.exe",
    "GFlags.exe",
    "CDB.exe",
    "KD.exe",
    "NTSD.exe",
    "WinObj.exe",
    "PEiD.exe",
    "StudPE.exe",
    "Procdump64.exe",
    "ProcessExplorer.exe",
    "Sysmon.exe",
    "Netmon.exe",
    "WPR.exe",
    "WPA.exe"};

static const int processCount = (int)(sizeof(processNames) / sizeof(processNames[0]));

/**
 * @brief Internal helper to initialize the processes array once.
 */
static void initializeProcessesIfNeeded(void)
{
    if (!processesInitialized)
    {
        for (int i = 0; i < processCount; i++)
        {
            processes[i].running = FALSE;
            ZeroMemory(&processes[i].pi, sizeof(processes[i].pi));
        }
        processesInitialized = TRUE;
    }
}

int getProcessCount(void)
{
    initializeProcessesIfNeeded();
    return processCount;
}

const char *getProcessName(int index)
{
    initializeProcessesIfNeeded();
    if (index < 0 || index >= processCount)
        return NULL;
    return processNames[index];
}

void setProcessRunningState(int index, BOOL running)
{
    initializeProcessesIfNeeded();
    if (index < 0 || index >= processCount)
        return;
    processes[index].running = running;
}

BOOL getProcessRunningState(int index)
{
    initializeProcessesIfNeeded();
    if (index < 0 || index >= processCount)
        return FALSE;
    return processes[index].running;
}

PROCESS_INFORMATION *getProcessInfo(int index)
{
    initializeProcessesIfNeeded();
    if (index < 0 || index >= processCount)
        return NULL;
    return &processes[index].pi;
}

/**
 * @brief Ensures the "processes" directory exists and copies dummy.exe into it for each listed process name.
 *
 * Creates "processes" directory if not present and copies dummy.exe to create decoy executables.
 */
void ensureProcessesDirectoryAndCopies(void)
{
    initializeProcessesIfNeeded();

    if (!CreateDirectoryA("processes", NULL))
    {
        DWORD err = GetLastError();
        if (err != ERROR_ALREADY_EXISTS)
        {
            qprintf("[-] Failed to create processes directory. Error: %lu\n", err);
            return;
        }
    }

    for (int i = 0; i < processCount; i++)
    {
        char destPath[MAX_PATH];
        snprintf(destPath, MAX_PATH, "processes\\%s", processNames[i]);

        if (!fileExists(destPath))
        {
            if (!CopyFileA("dummy.exe", destPath, FALSE))
            {
                DWORD err = GetLastError();
                qprintf("[-] Failed to copy dummy.exe to %s. Error: %lu\n", destPath, err);
            }
            else
            {
                qprintf("[+] Copied dummy.exe to %s\n", destPath);
            }
        }
    }
}

/**
 * @brief Starts all decoy processes if they are not already running.
 *
 * Attempts to start each process from the "processes" directory.
 */
void startAllProcesses(void)
{
    initializeProcessesIfNeeded();

    for (int i = 0; i < processCount; i++)
    {
        if (!processes[i].running)
        {
            char processPath[MAX_PATH];
            snprintf(processPath, MAX_PATH, "processes\\%s", processNames[i]);

            STARTUPINFOA si;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&processes[i].pi, sizeof(processes[i].pi));

            if (!CreateProcessA(processPath, NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &processes[i].pi))
            {
                DWORD err = GetLastError();
                qprintf("[-] Failed to start %s. Error: %lu\n", processNames[i], err);
            }
            else
            {
                processes[i].running = TRUE;
                qprintf("[+] Started %s (PID: %lu)\n", processNames[i], processes[i].pi.dwProcessId);
            }
        }
        else
        {
            qprintf("[!] %s already running.\n", processNames[i]);
        }
    }
    fflush(stdout);
}

/**
 * @brief Terminates all running decoy processes.
 *
 * If a process handle is available and marked as running, it is terminated.
 * If not running, attempts to kill by name for safety.
 */
void terminateAllProcesses(void)
{
    initializeProcessesIfNeeded();

    for (int i = 0; i < processCount; i++)
    {
        if (processes[i].running && processes[i].pi.hProcess != NULL)
        {
            if (TerminateProcess(processes[i].pi.hProcess, 0))
            {
                WaitForSingleObject(processes[i].pi.hProcess, 2000);
                CloseHandle(processes[i].pi.hProcess);
                CloseHandle(processes[i].pi.hThread);
                processes[i].running = FALSE;
                qprintf("[+] Terminated %s\n", processNames[i]);
            }
            else
            {
                qprintf("[-] Failed to terminate %s. Error: %lu\n", processNames[i], GetLastError());
            }
        }
        else
        {
            // Attempt to kill by name if no handle or not running in our array
            killProcessByName(processNames[i]);
        }
    }
}

/**
 * @brief Restarts all processes by first terminating, ensuring copies, and then starting them again.
 */
void restartAllProcesses(void)
{
    terminateAllProcesses();
    ensureProcessesDirectoryAndCopies();
    startAllProcesses();
}

/**
 * @brief Provides an interactive mode loop to handle user commands.
 *
 * Waits for user input and handles commands S/T/R/Q.
 */
void interactiveMode(void)
{
    printBanner();
    printMenu();

    char choice;
    BOOL running = TRUE;

    while (running && scanf(" %c", &choice) == 1)
    {
        switch (choice)
        {
        case 'S':
        case 's':
            ensureProcessesDirectoryAndCopies();
            startAllProcesses();
            break;
        case 'T':
        case 't':
            terminateAllProcesses();
            break;
        case 'R':
        case 'r':
            restartAllProcesses();
            break;
        case 'Q':
        case 'q':
            running = FALSE;
            break;
        default:
            qprintf("Unknown command. Please try again.\n");
            break;
        }

        if (running)
        {
            qprintf("\n--------------------------------\n");
            printMenu();
        }
    }

    qprintf("\nExiting Decoy Manager. Goodbye!\n");
}
