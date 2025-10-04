#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt;
    int completed;
};

int main() {
    int n, i, time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    // Store Gantt Chart order
    int ganttOrder[100], ganttStart[100], ganttEnd[100];
    int gCount = 0;

    while (completed < n) {
        int idx = -1, minBT = 9999;
        for (i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                } else if (p[i].bt == minBT) {
                    // tie-break by arrival time first
                    if (idx == -1 || p[i].at < p[idx].at ||
                       (p[i].at == p[idx].at && p[i].id < p[idx].id)) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // CPU idle
            time++;
            continue;
        }

        ganttStart[gCount] = time;
        ganttOrder[gCount] = p[idx].id;
        time += p[idx].bt;
        ganttEnd[gCount] = time;
        gCount++;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;
        completed++;
    }

    // Print Table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
    }

    printf("\nAverage TAT = %.2f\n", avgTAT / n);
    printf("Average WT  = %.2f\n", avgWT / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    // Print timeline
    printf("%d", ganttStart[0] < p[0].at ? 0 : ganttStart[0]);
    for (i = 0; i < gCount; i++) {
        printf("   %d", ganttEnd[i]);
    }
    printf("\n");

    // Print process sequence
    printf("    ");
    for (i = 0; i < gCount; i++) {
        printf("| P%d ", ganttOrder[i]);
    }
    printf("|\n");

    return 0;
}
