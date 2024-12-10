#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <tlhelp32.h>

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
    "WPA.exe"
};

static const int processCount = (int)(sizeof(processNames) / sizeof(processNames[0]));

typedef struct {
    PROCESS_INFORMATION pi;
    BOOL running;
} FakeProcess;

static FakeProcess processes[64];
static BOOL quietMode = FALSE;

static void qprintf(const char *fmt, ...) {
    if (!quietMode) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        fflush(stdout);
    }
}

static BOOL fileExists(const char *filename) {
    return (_access(filename, 0) == 0);
}

static void killProcessByName(const char *pname) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);

    if (Process32First(hSnapshot, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, pname) == 0) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProc) {
                    TerminateProcess(hProc, 0);
                    WaitForSingleObject(hProc, 2000);
                    CloseHandle(hProc);
                    qprintf("[+] Terminated %s (PID: %lu)\n", pname, pe.th32ProcessID);
                }
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
}

static void ensureProcessesDirectoryAndCopies(void) {
    if (!fileExists("dummy.exe")) {
        qprintf("[-] dummy.exe not found. Please ensure it is in the same directory.\n");
        return;
    }

    CreateDirectoryA("processes", NULL);

    for (int i = 0; i < processCount; i++) {
        char destPath[MAX_PATH];
        snprintf(destPath, MAX_PATH, "processes\\%s", processNames[i]);

        if (!fileExists(destPath)) {
            if (!CopyFileA("dummy.exe", destPath, FALSE)) {
                DWORD err = GetLastError();
                qprintf("[-] Failed to copy dummy.exe to %s. Error: %lu\n", destPath, err);
            }
        }
    }
}

static void startAllProcesses(void) {
    for (int i = 0; i < processCount; i++) {
        if (!processes[i].running) {
            STARTUPINFOA si;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&processes[i].pi, sizeof(processes[i].pi));

            char path[MAX_PATH];
            snprintf(path, MAX_PATH, "processes\\%s", processNames[i]);

            if (fileExists(path)) {
                if (CreateProcessA(path, NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &processes[i].pi)) {
                    processes[i].running = TRUE;
                    qprintf("[+] Started %s (PID: %lu)\n", processNames[i], processes[i].pi.dwProcessId);
                } else {
                    qprintf("[-] Failed to start %s. Error: %lu\n", processNames[i], GetLastError());
                }
            } else {
                qprintf("[-] %s not found in processes directory.\n", processNames[i]);
            }
        } else {
            qprintf("[!] %s already running.\n", processNames[i]);
        }
    }
    fflush(stdout);
}

static void terminateAllProcesses(void) {
    for (int i = 0; i < processCount; i++) {
        if (processes[i].running) {
            TerminateProcess(processes[i].pi.hProcess, 0);
            WaitForSingleObject(processes[i].pi.hProcess, 2000);
            CloseHandle(processes[i].pi.hProcess);
            CloseHandle(processes[i].pi.hThread);
            processes[i].running = FALSE;
            qprintf("[+] Terminated %s\n", processNames[i]);
        }
    }

    for (int i = 0; i < processCount; i++) {
        killProcessByName(processNames[i]);
    }

    fflush(stdout);
}

static void restartAllProcesses(void) {
    terminateAllProcesses();
    ensureProcessesDirectoryAndCopies();
    startAllProcesses();
}

static void printBanner(void) {
    qprintf("\x1b[35m");
    qprintf("     __                 \n");
    qprintf(" ___/ /__ _______  __ __\n");
    qprintf("/ _  / -_) __/ _ \\/ // /\n");
    qprintf("\\_,_/\\__/\\__/\\___/\\_, / ");
    qprintf("\x1b[0m");
    qprintf("v0.1.0\n");
    qprintf("\x1b[35m");
    qprintf("                 /___/  \n");
    qprintf("\x1b[0m\n");
    qprintf("Welcome to the Decoy Manager!\n");
    qprintf("--------------------------------\n");
    qprintf("This tool launches multiple dummy processes\n");
    qprintf("as known analysis/debugger tool names.\n");
    qprintf("Use it to deter simple malware checks.\n\n");
    qprintf("Each process uses minimal resources.\n\n");
    fflush(stdout);
}

static void printMenu(void) {
    qprintf("Available Commands:\n");
    qprintf("[S] Start all processes\n");
    qprintf("[T] Terminate all processes\n");
    qprintf("[R] Restart all processes\n");
    qprintf("[Q] Quit\n");
    qprintf("--------------------------------\n");
    qprintf("Enter a command: ");
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < processCount; i++) {
        processes[i].running = FALSE;
    }

    BOOL startImmediate = FALSE;
    BOOL terminateImmediate = FALSE;

    for (int i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-S") == 0) || (strcmp(argv[i], "-s") == 0)) {
            startImmediate = TRUE;
        } else if ((strcmp(argv[i], "-T") == 0) || (strcmp(argv[i], "-t") == 0)) {
            terminateImmediate = TRUE;
        } else if ((strcmp(argv[i], "-Q") == 0) || (strcmp(argv[i], "-q") == 0)) {
            quietMode = TRUE;
            startImmediate = TRUE;
        }
    }

    if (quietMode && startImmediate && !terminateImmediate) {
        ensureProcessesDirectoryAndCopies();
        startAllProcesses();
        return 0;
    }

    if (startImmediate && !terminateImmediate) {
        printBanner();
        qprintf("[*] Starting all processes as requested by command-line argument.\n");
        ensureProcessesDirectoryAndCopies();
        startAllProcesses();
        return 0;
    }

    if (terminateImmediate) {
        printBanner();
        qprintf("[*] Terminating all processes as requested by command-line argument.\n");
        terminateAllProcesses();
        return 0;
    }

    // Enable ANSI if possible
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
    }

    // Interactive mode
    printBanner();
    printMenu();

    char choice;
    BOOL running = TRUE;

    while (running && scanf(" %c", &choice) == 1) {
        switch (choice) {
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
            terminateAllProcesses();
            break;
        default:
            qprintf("Unknown command. Please try again.\n");
            break;
        }

        if (running) {
            qprintf("\n--------------------------------\n");
            printMenu();
        }
    }

    qprintf("\nExiting Decoy Manager. Goodbye!\n");
    return 0;
}
