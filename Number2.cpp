#include <iostream>
using namespace std;

int main() {
    int n = 10;
    int bt[10] = {9, 8, 7, 8, 7, 8, 2, 1, 2, 5};
    int at[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ct[10], wt[10], tat[10];

    // Completion time
    ct[0] = at[0] + bt[0]; // first process finishes at arrival + burst

    for (int i = 1; i < n; i++) {
        // If the next process arrives after the previous one finished, CPU waits
        if (at[i] > ct[i - 1]) {
            ct[i] = at[i] + bt[i];
        } else {
            ct[i] = ct[i - 1] + bt[i];
        }
    }

    // Turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Output
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << " \t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    return 0;
}