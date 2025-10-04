#include <stdio.h>

typedef struct {
    int pid, at, bt, ct, tat, wt;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort by Arrival Time
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    int time = 0;
    float totalTAT = 0, totalWT = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at; // idle CPU
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalTAT += p[i].tat;
        totalWT  += p[i].wt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT/n);
    printf("\nAverage WT  = %.2f\n", totalWT/n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    int prev = 0;
    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("   %d", p[i].ct);
    }
    printf("\n");
    return 0;
}
