#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid, at, bt, ct, tat, wt;
    int remaining_bt;
} Process;

int main() {
    int n, q;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &q);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining_bt = p[i].bt;
    }

    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    int gantt_proc[100], gantt_time[100], gcount = 0;

    while (completed < n) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_bt > 0 && p[i].at <= time) {
                done = false;
                if (p[i].remaining_bt > q) {
                    time += q;
                    p[i].remaining_bt -= q;
                    gantt_proc[gcount] = p[i].pid;
                    gantt_time[gcount++] = time;
                } else {
                    time += p[i].remaining_bt;
                    p[i].remaining_bt = 0;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    gantt_proc[gcount] = p[i].pid;
                    gantt_time[gcount++] = time;

                    totalTAT += p[i].tat;
                    totalWT += p[i].wt;
                    completed++;
                }
            }
        }
        if (done) time++; // CPU idle
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT/n);
    printf("\nAverage WT  = %.2f\n", totalWT/n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("0"); 
    for (int i = 0; i < gcount; i++) {
        printf(" | P%d | %d", gantt_proc[i], gantt_time[i]);
    }
    printf("\n");

    return 0;
}
