#include <iostream>
#include <unistd.h>   // fork, getpid
#include <sys/wait.h> // wait, waitpid

using namespace std;

int main() {
    pid_t pid1, pid2;

    // Parent creates Child1
    pid1 = fork();

    if (pid1 < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid1 == 0) {
        // Child1 process
        pid_t pid1_1 = fork();
        if (pid1_1 == 0) {
            // Child1.1 process
            cout << "Child1.1 PID: " << getpid() << endl;
            return 0;
        } else {
            waitpid(pid1_1, NULL, 0); // wait for Child1.1
            // Delay Child1 print until after Child2.1 finishes
            sleep(1);
            cout << "Child1 PID: " << getpid() << endl;
            return 0;
        }
    } else {
        // Parent creates Child2
        pid2 = fork();

        if (pid2 < 0) {
            cerr << "Fork failed!" << endl;
            return 1;
        }

        if (pid2 == 0) {
            // Child2 process
            pid_t pid2_1 = fork();
            if (pid2_1 == 0) {
                // Child2.1 process
                // Small delay so Child1.1 prints first
                sleep(1);
                cout << "Child2.1 PID: " << getpid() << endl;
                return 0;
            } else {
                waitpid(pid2_1, NULL, 0); // wait for Child2.1
                cout << "Child2 PID: " << getpid() << endl;
                return 0;
            }
        } else {
            // Parent waits for both children
            waitpid(pid1, NULL, 0); // wait for Child1
            waitpid(pid2, NULL, 0); // wait for Child2
            cout << "Parent PID: " << getpid() << endl;
        }
    }

    return 0;
}
