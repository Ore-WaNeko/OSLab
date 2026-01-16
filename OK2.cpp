#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    int n;
    double quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;

    double burst[20], remaining[20], waiting[20], turnaround[20];
    for (int i = 0; i < n; i++) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> burst[i];
        remaining[i] = burst[i];
        waiting[i] = 0;
        turnaround[i] = 0;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) q.push(i);

    double time = 0;
    int ganttProc[100];
    double ganttTime[100];
    int gIndex = 0;

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        double exec = (remaining[i] > quantum) ? quantum : remaining[i];
        remaining[i] -= exec;
        time += exec;

        ganttProc[gIndex] = i + 1;
        ganttTime[gIndex] = exec;
        gIndex++;

        // Update waiting time for all other processes still in queue
        for (int j = 0; j < n; j++) {
            if (j != i && remaining[j] > 0) {
                waiting[j] += exec;
            }
        }

        if (remaining[i] == 0) {
            turnaround[i] = time;
        } else {
            q.push(i); // put back into queue if not finished
        }
    }

    cout << "\nProcess\tBurst\tWaiting\tTurnaround\n";
    double avg_wait = 0, avg_turn = 0;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << burst[i] << "\t" << waiting[i] << "\t" << turnaround[i] << "\n";
        avg_wait += waiting[i];
        avg_turn += turnaround[i];
    }
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avg_turn / n << endl;

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < gIndex; i++) {
        cout << "|   P" << ganttProc[i] << "   ";
    }
    cout << "|\n";

    double currentTime = 0;
    cout << setw(4) << "0";
    for (int i = 0; i < gIndex; i++) {
        currentTime += ganttTime[i];
        cout << setw(8) << fixed << setprecision(2) << currentTime;
    }
    cout << endl;

    return 0;
}
