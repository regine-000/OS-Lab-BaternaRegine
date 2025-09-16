/* replace_sim.c */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command to run (like exec)
    char cmdLine[] = "cmd.exe /c dir";

    printf("Parent: launching replacement process...\n");

    if (!CreateProcess(
            NULL,           // Application name
            cmdLine,        // Command line
            NULL, NULL,     // Security
            FALSE,          // Inherit handles
            0,              // Creation flags
            NULL, NULL,     // Environment, directory
            &si, &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for the spawned process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get the exit code of the spawned process
    GetExitCodeProcess(pi.hProcess, &exitCode);

    printf("Parent: replacement process exited with code %lu\n", exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Exit with the same code as the spawned process
    return (int)exitCode;
}
