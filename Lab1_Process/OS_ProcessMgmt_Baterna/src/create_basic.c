/* create_basic.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(void) {
    DWORD parentPid = GetCurrentProcessId();
    printf("create_basic: parent PID = %lu\n", (unsigned long)parentPid);

    /* Build mutatable command line for CreateProcess */
    char cmdline[512];
    snprintf(cmdline, sizeof(cmdline), "child_echo.exe %lu", (unsigned long)parentPid);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    BOOL ok = CreateProcessA(
        NULL,       // lpApplicationName
        cmdline,    // lpCommandLine (must be writable)
        NULL, NULL, // process/thread security
        FALSE,      // inherit handles
        0,          // creation flags
        NULL, NULL, // environment, current directory
        &si, &pi
    );

    if (!ok) {
        DWORD err = GetLastError();
        char buf[512];
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, sizeof(buf), NULL);
        fprintf(stderr, "CreateProcess failed (error %lu): %s\n", (unsigned long)err, buf);
        return 1;
    }

    /* Wait until child exits */
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode = 0;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        fprintf(stderr, "GetExitCodeProcess failed\n");
    } else {
        printf("create_basic: child exit code = %lu\n", (unsigned long)exitCode);
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
