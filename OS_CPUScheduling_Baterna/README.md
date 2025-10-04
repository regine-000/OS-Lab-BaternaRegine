
CPU SCHEDULING ALGORITHMS

In First-Come, First-Served (FCFS) scheduling, processes are executed in the order they arrive in the ready queue, much like people lining up at a cashier.
The first process to arrive is the first to be served, and once a process starts, it runs until completion. For example, if three processes arrive in the 
order P1 (BT = 5), P2 (BT = 3), and P3 (BT = 8), then the CPU will run them in that exact order. While this approach is simple, it can lead to the convoy
effect, where shorter processes are forced to wait behind a very long process.

In Shortest Job First (SJF) scheduling, the CPU selects the process with the smallest burst time among the ones that have already arrived. This results in
a lower average waiting time since shorter processes finish earlier, allowing more tasks to complete quickly. For instance, if processes P1 (BT = 8),
P2 (BT = 4), and P3 (BT = 2) arrive at nearly the same time, the CPU will execute P3 first, then P2, and finally P1. However, one drawback of SJF is the 
risk of starvation, since long processes may be delayed if shorter jobs keep arriving.

In Round Robin (RR) scheduling, each process is assigned a fixed time quantum, such as 2 or 3 units. Processes are executed in a cycle, and if a process 
does not finish within its quantum, it is placed at the back of the queue to wait for its next turn. This makes RR fairer because every process gets CPU 
time regularly. For example, with a quantum of 2 and processes P1 (BT = 5), P2 (BT = 4), and P3 (BT = 3), the CPU will first give 2 units to P1, then 2 to 
P2, then 2 to P3, and return again to P1, continuing until all are complete. The main challenge in RR is choosing the right time quantum — too small causes 
frequent context switching, while too large makes it behave like FCFS.


SAMPLE OUTPUTS


FCFS
<img width="1032" height="413" alt="image" src="https://github.com/user-attachments/assets/e70354a1-9739-47db-9a8c-ba546d95f205" />

