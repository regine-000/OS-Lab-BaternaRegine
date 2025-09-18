

## Build Instructions (VS Code + MinGW)

1. Open the project folder `OS_LA1_ProcessMgmt_Baterna` in VS Code.
2. Open the terminal inside VS Code.
3. Compile the child program:
   
   gcc src/child_echo.c -o child_echo.exe -mconsole
   
   gcc src/create_basic.c -o create_basic.exe -mconsole

   .\create_basic.exe


##Task A OUTPUT– Creating a Single Child
<img width="970" height="188" alt="image" src="https://github.com/user-attachments/assets/d8143bac-7162-4c4a-b59a-f3f2d8c6af42" />


Notes:

- The `create_basic.exe` program correctly printed the parent PID (`852`).
- The `child_echo.exe` program successfully ran and displayed:
  - Its own PID (`16272`)
  - The parent PID passed as an argument (`852`)
- After the child terminated, the parent (`create_basic.exe`) retrieved and printed the child’s exit code (`55`).
- This confirms successful process creation, argument passing, and exit code handling.


   gcc src/child_echo.c -o child_echo.exe -mconsole
   
   gcc src/create_basic.c -o create_basic.exe -mconsole

   .\create_basic.exe


##TASK B OUTPUT Creating Two Children
<img width="946" height="196" alt="image" src="https://github.com/user-attachments/assets/a4942943-e024-43af-838d-01d97e790e3c" />


Notes:
The parent process successfully created two child processes in parallel.

Each child reported its own unique PID, confirming that separate processes were spawned.

The children were launched without passing the parent PID argument, which is why they displayed “no parent PID argument supplied.”

Both children terminated with exit code 55, showing that the child program explicitly returned this value. This verifies that the parent program correctly collected and reported the children’s exit codes.


Task C OUTPUT Simulating exec()
09/16/2025  01:23 PM             1,727 create_basic.c
09/16/2025  01:27 PM            65,475 create_basic.exe
09/17/2025  02:15 AM             1,873 create_two_children.c
09/17/2025  02:16 AM            64,079 create_two_children.exe
09/16/2025  09:40 AM                95 hello.c
09/16/2025  01:18 PM            61,248 hello.exe
09/17/2025  02:42 AM             1,795 README.md     	
09/17/2025  02:45 AM             1,265 replace_sim.c
09/17/2025  02:46 AM            63,539 replace_sim.exe
              11 File(s)        323,845 bytes
               2 Dir(s)  109,166,125,056 bytes free
               
               
Parent: replacement process exited with code 0
Notes:
-The parent process did not end quickly.
-It waited for the spawned process (cmd /c dir) to finish.
-The parent then exited with the same code (0).
-This shows that in Windows, we must simulate exec() using CreateProcess + WaitForSingleObject + ExitProcess.



##Task D Output
Normal Terminaion:
create_basic: parent PID = 34652
child_echo: my PID = 46284
child_echo: parent PID (from arg) = 34652
create_basic: child exit code = 55

Force Termination:
create_basic: parent PID = 46384
child_echo: my PID = 36044
child_echo: parent PID (from arg) = 46384
create_basic: child exit code = 4294967295

Normal termination: Waited for child to finish → exit code = 55
Forced termination: Killed child → exit code ≠ 55


