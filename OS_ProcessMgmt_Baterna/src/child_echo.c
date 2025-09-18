#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    DWORD myPid = GetCurrentProcessId();
    printf("child_echo: my PID = %lu\n", (unsigned long)myPid);

    if (argc > 1) {
        printf("child_echo: parent PID (from arg) = %s\n", argv[1]);
    } else {
        printf("child_echo: no parent PID argument supplied\n");
    }

    // Wait 10 seconds so you can see the process in PowerShell
    Sleep(6000);

    return 55;
}

