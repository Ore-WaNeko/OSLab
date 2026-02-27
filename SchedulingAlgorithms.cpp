#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int bt;
    int at;
    int tt;
    int wt;
    int ct;
};

// Function to calculate recommended quantum time
int recommendedQuantumTime(int bt[], int n) {
    // Calculate mean of burst times
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += bt[i];
    }
    int mean = sum / n;
    
    // Round to nearest whole number
    return (int)round((double)mean);
}

// Shortest Job First (Non-preemptive)
void SJF(Process processes[], int n) {
    cout << "\n========== SHORTEST JOB FIRST (SJF) ==========\n";
    
    // Sort by burst time (ascending)
    sort(processes, processes + n, [](const Process& a, const Process& b) {
        if (a.at != b.at)
            return a.at < b.at;
        return a.bt < b.bt;
    });
    
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        // If process arrives after current time, CPU is idle
        if (processes[i].at > currentTime) {
            currentTime = processes[i].at;
        }
        
        processes[i].ct = currentTime + processes[i].bt;
        processes[i].tt = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tt - processes[i].bt;
        
        currentTime = processes[i].ct;
    }
    
    // Sort back by PID for display
    sort(processes, processes + n, [](const Process& a, const Process& b) {
        return a.pid < b.pid;
    });
    
    // Display table
    cout << "\n" << left << setw(8) << "PID" 
         << setw(8) << "AT" 
         << setw(8) << "BT" 
         << setw(8) << "CT" 
         << setw(8) << "TT" 
         << setw(8) << "WT" << endl;
    cout << "============================================================\n";
    
    int totalTT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        cout << left << setw(8) << processes[i].pid 
             << setw(8) << processes[i].at 
             << setw(8) << processes[i].bt 
             << setw(8) << processes[i].ct 
             << setw(8) << processes[i].tt 
             << setw(8) << processes[i].wt << endl;
        totalTT += processes[i].tt;
        totalWT += processes[i].wt;
    }
    
    cout << "\nAverage TT: " << fixed << setprecision(2) << (double)totalTT / n << endl;
    cout << "Average WT: " << fixed << setprecision(2) << (double)totalWT / n << endl;
}

// Shortest Remaining Time First (Preemptive)
void SRTF(Process processes[], int n) {
    cout << "\n========== SHORTEST REMAINING TIME FIRST (SRTF) ==========\n";
    
    // Create working copies
    Process temp[20];
    for (int i = 0; i < n; i++) {
        temp[i] = processes[i];
    }
    
    int remaining[20];
    for (int i = 0; i < n; i++) {
        remaining[i] = temp[i].bt;
    }
    
    int completed = 0;
    int currentTime = 0;
    
    while (completed < n) {
        // Find process with minimum remaining time that has arrived
        int minIdx = -1;
        int minTime = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (temp[i].at <= currentTime && remaining[i] > 0 && remaining[i] < minTime) {
                minTime = remaining[i];
                minIdx = i;
            }
        }
        
        if (minIdx == -1) {
            // No process available, jump to next arrival
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (remaining[i] > 0 && temp[i].at > currentTime) {
                    nextArrival = min(nextArrival, temp[i].at);
                }
            }
            currentTime = nextArrival;
        } else {
            remaining[minIdx]--;
            currentTime++;
            
            if (remaining[minIdx] == 0) {
                temp[minIdx].ct = currentTime;
                temp[minIdx].tt = temp[minIdx].ct - temp[minIdx].at;
                temp[minIdx].wt = temp[minIdx].tt - temp[minIdx].bt;
                completed++;
            }
        }
    }
    
    // Sort by PID for display
    sort(temp, temp + n, [](const Process& a, const Process& b) {
        return a.pid < b.pid;
    });
    
    // Update original array and display
    for (int i = 0; i < n; i++) {
        processes[i] = temp[i];
    }
    
    // Display table
    cout << "\n" << left << setw(8) << "PID" 
         << setw(8) << "AT" 
         << setw(8) << "BT" 
         << setw(8) << "CT" 
         << setw(8) << "TT" 
         << setw(8) << "WT" << endl;
    cout << "============================================================\n";
    
    int totalTT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        cout << left << setw(8) << processes[i].pid 
             << setw(8) << processes[i].at 
             << setw(8) << processes[i].bt 
             << setw(8) << processes[i].ct 
             << setw(8) << processes[i].tt 
             << setw(8) << processes[i].wt << endl;
        totalTT += processes[i].tt;
        totalWT += processes[i].wt;
    }
    
    cout << "\nAverage TT: " << fixed << setprecision(2) << (double)totalTT / n << endl;
    cout << "Average WT: " << fixed << setprecision(2) << (double)totalWT / n << endl;
}

// Round Robin
void RoundRobin(Process processes[], int n, int quantum) {
    cout << "\n========== ROUND ROBIN (Quantum = " << quantum << ") ==========\n";
    
    // Create working copies
    Process temp[20];
    for (int i = 0; i < n; i++) {
        temp[i] = processes[i];
    }
    
    int remaining[20];
    for (int i = 0; i < n; i++) {
        remaining[i] = temp[i].bt;
    }
    
    queue<int> q;
    // Add all processes to queue (sorted by arrival time)
    vector<int> indices;
    for (int i = 0; i < n; i++) {
        indices.push_back(i);
    }
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return temp[a].at < temp[b].at;
    });
    
    for (int idx : indices) {
        q.push(idx);
    }
    
    int currentTime = 0;
    
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        
        // If process hasn't arrived yet
        if (temp[i].at > currentTime) {
            currentTime = temp[i].at;
        }
        
        // Execute for quantum or remaining time, whichever is less
        int exec = min(quantum, remaining[i]);
        remaining[i] -= exec;
        currentTime += exec;
        
        if (remaining[i] > 0) {
            q.push(i);
        } else {
            temp[i].ct = currentTime;
            temp[i].tt = temp[i].ct - temp[i].at;
            temp[i].wt = temp[i].tt - temp[i].bt;
        }
    }
    
    // Sort by PID for display
    sort(temp, temp + n, [](const Process& a, const Process& b) {
        return a.pid < b.pid;
    });
    
    // Update original array and display
    for (int i = 0; i < n; i++) {
        processes[i] = temp[i];
    }
    
    // Display table
    cout << "\n" << left << setw(8) << "PID" 
         << setw(8) << "AT" 
         << setw(8) << "BT" 
         << setw(8) << "CT" 
         << setw(8) << "TT" 
         << setw(8) << "WT" << endl;
    cout << "============================================================\n";
    
    int totalTT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        cout << left << setw(8) << processes[i].pid 
             << setw(8) << processes[i].at 
             << setw(8) << processes[i].bt 
             << setw(8) << processes[i].ct 
             << setw(8) << processes[i].tt 
             << setw(8) << processes[i].wt << endl;
        totalTT += processes[i].tt;
        totalWT += processes[i].wt;
    }
    
    cout << "\nAverage TT: " << fixed << setprecision(2) << (double)totalTT / n << endl;
    cout << "Average WT: " << fixed << setprecision(2) << (double)totalWT / n << endl;
}

int main() {
    int n = 8;
    int at[8] = {1, 3, 8, 4, 6, 7, 2, 5};
    int bt[8] = {53, 43, 18, 16, 24, 73, 99, 27};
    
    // Create process structures
    Process processes[8];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].at = at[i];
        processes[i].bt = bt[i];
        processes[i].tt = 0;
        processes[i].wt = 0;
        processes[i].ct = 0;
    }
    
    // Calculate recommended quantum time
    int quantum = recommendedQuantumTime(bt, n);
    cout << "========================================\n";
    cout << "RECOMMENDED QUANTUM TIME: " << quantum << endl;
    cout << "========================================\n";
    
    // Create copies for each algorithm
    Process processesSJF[8], processesSRTF[8], processesRR[8];
    for (int i = 0; i < n; i++) {
        processesSJF[i] = processes[i];
        processesSRTF[i] = processes[i];
        processesRR[i] = processes[i];
    }
    
    // Run all three algorithms
    SJF(processesSJF, n);
    SRTF(processesSRTF, n);
    RoundRobin(processesRR, n, quantum);
    
    return 0;
}
