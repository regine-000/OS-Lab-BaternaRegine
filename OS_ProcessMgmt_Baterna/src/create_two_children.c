#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    printf("Parent PID: %lu\n", GetCurrentProcessId());

    // Create first child
    if (!CreateProcess(
        NULL,
        "child_echo.exe",   // your compiled child program
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si1,
        &pi1)
    ) {
        printf("CreateProcess for child 1 failed (%lu).\n", GetLastError());
        return 1;
    }

    // Create second child
    if (!CreateProcess(
        NULL,
        "child_echo.exe",   // your compiled child program
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si2,
        &pi2)
    ) {
        printf("CreateProcess for child 2 failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for both children to finish
    HANDLE processes[2] = { pi1.hProcess, pi2.hProcess };
    WaitForMultipleObjects(2, processes, TRUE, INFINITE);

    DWORD exitCode1, exitCode2;
    GetExitCodeProcess(pi1.hProcess, &exitCode1);
    GetExitCodeProcess(pi2.hProcess, &exitCode2);

    printf("Child 1 exited with code %lu\n", exitCode1);
    printf("Child 2 exited with code %lu\n", exitCode2);

    // Close process and thread handles
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    return 0;
}
