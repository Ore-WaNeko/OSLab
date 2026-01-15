#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int burst[10], remaining[10], waiting[10] = {0}, turnaround[10];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
    }

    int time = 0;
    while (1) {
        int all_done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                all_done = 0;
                int exec = (remaining[i] > quantum) ? quantum : remaining[i];
                remaining[i] -= exec;
                time += exec;

                for (int j = 0; j < n; j++) {
                    if (j != i && remaining[j] > 0) {
                        waiting[j] += exec;
                    }
                }

                if (remaining[i] == 0) {
                    turnaround[i] = time;
                }
            }
        }
        if (all_done) break;
    }

    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    float avg_wait = 0, avg_turn = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", i + 1, burst[i], waiting[i], turnaround[i]);
        avg_wait += waiting[i];
        avg_turn += turnaround[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_wait / n);
    printf("Average Turnaround Time: %.2f\n", avg_turn / n);

    return 0;
}
