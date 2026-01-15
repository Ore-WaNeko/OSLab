#include <stdio.h>

int main() {
    int bt[20], wt[20], tat[20], i, n;
    float wtavg, tatavg;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst times
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Calculate waiting and turnaround times (FCFS - First Come First Served)
    wt[0] = 0;
    tat[0] = bt[0];
    wtavg = 0;
    tatavg = bt[0];

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wtavg = wtavg + wt[i];
        tatavg = tatavg + tat[i];
    }

    // Display results
    printf("\n%-10s %-12s %-15s %-15s\n", "PROCESS", "BURST TIME", "WAITING TIME", "TURNAROUND TIME");
    printf("%-10s %-12s %-15s %-15s\n", "-------", "-----------", "-------------", "---------------");

    for (i = 0; i < n; i++) {
        printf("P%-9d %-12d %-15d %-15d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", wtavg / n);
    printf("Average Turnaround Time: %.2f\n", tatavg / n);

    return 0;
}