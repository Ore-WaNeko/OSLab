#include <iostream>
using namespace std;

int main() {
    int n = 6;
    double bt[6] = {99.99, 107.9, 143.77, 20.24, 50.55, 66.66};
    double wt[6], tat[6], ct[6];

    // To keep track of original process numbers after sorting
    int p[6] = {1, 2, 3, 4, 5, 6};

    // SJF sorting based on burst time (ascending)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                // Swap burst times
                double temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process numbers to match
                int tempP = p[i];
                p[i] = p[j];
                p[j] = tempP;
            }
        }
    }

    // Completion time
    ct[0] = bt[0]; // first process finishes at its burst time
    for (int i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i];
    }

    // Turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i];        // arrival time = 0
        wt[i] = tat[i] - bt[i];
    }

    // Output
    cout << "Process\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    // Average WT and TAT
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    cout << "\nAverage WT: " << totalWT / n;
    cout << "\nAverage TAT: " << totalTAT / n << endl;

    return 0;
}