#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[10], waiting[10] = {0}, turnaround[10];
    int arrival[10] = {0};  // All arrive at time 0 for simplicity
    int completed[10] = {0};
    
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    int time = 0;
    
    // Non-preemptive SJF scheduling
    for (int count = 0; count < n; count++) {
        int shortest = -1;
        int min_burst = 999999;
        
        // Find the process with shortest burst time that hasn't completed
        for (int i = 0; i < n; i++) {
            if (!completed[i] && burst[i] < min_burst) {
                min_burst = burst[i];
                shortest = i;
            }
        }
        
        // Execute the selected process completely (non-preemptive)
        time += burst[shortest];
        completed[shortest] = 1;
        turnaround[shortest] = time;
        waiting[shortest] = time - burst[shortest];
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
