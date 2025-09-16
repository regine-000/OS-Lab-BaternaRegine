/* create_two_children.c */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;
    char cmdLine1[] = "child_echo.exe 1234";
    char cmdLine2[] = "child_echo.exe 5678";

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    printf("Parent: creating two children...\n");

    // Create first child
    if (!CreateProcess(
        NULL,           // No module name
        cmdLine1,       // Command line
        NULL, NULL,     // Process and thread security
        FALSE,          // Inherit handles
        0,              // Creation flags
        NULL, NULL,     // Environment and current directory
        &si1, &pi1)) {
        printf("CreateProcess for child 1 failed (%lu).\n", GetLastError());
        return 1;
    }

    // Create second child
    if (!CreateProcess(
        NULL,
        cmdLine2,
        NULL, NULL,
        FALSE,
        0,
        NULL, NULL,
        &si2, &pi2)) {
        printf("CreateProcess for child 2 failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for both children to finish
    HANDLE handles[2] = { pi1.hProcess, pi2.hProcess };
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    DWORD exitCode1, exitCode2;
    GetExitCodeProcess(pi1.hProcess, &exitCode1);
    GetExitCodeProcess(pi2.hProcess, &exitCode2);

    printf("Parent: Child 1 exited with code %lu\n", exitCode1);
    printf("Parent: Child 2 exited with code %lu\n", exitCode2);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    return 0;
}
