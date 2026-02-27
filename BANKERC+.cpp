#include <iostream>
using namespace std;

int main()
{
    int alloc[10][10], maxm[10][10];
    int avail[10], work[10], total[10];
    int need[10][10];
    int n, m;
    int i, j, k;
    int count = 0, c = 0;
    char finish[10];

    // 1. Start the program.

    // 2. Get the values of resources and processes.
    cout << "Enter the number of processes and resources: ";
    cin >> n >> m;

    for(i = 0; i < n; i++)
        finish[i] = 'n';

    cout << "Enter the claim matrix:\n";
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            cin >> maxm[i][j];

    cout << "Enter the allocation matrix:\n";
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter the resource vector: ";
    for(i = 0; i < m; i++)
        cin >> total[i];

    // 3. Get the available value.
    for(i = 0; i < m; i++)
        avail[i] = 0;

    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            avail[j] += alloc[i][j];

    for(i = 0; i < m; i++)
        work[i] = total[i] - avail[i];

    // 4. After allocation find the need value.
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    // 5. Check whether it’s possible to allocate.
    bool executed = false;
A:
    executed = false;
    for(i = 0; i < n; i++)
    {
        c = 0;
        for(j = 0; j < m; j++)
        {
            if((need[i][j] <= work[j]) && (finish[i] == 'n'))
                c++;
        }

        if(c == m)
        {
            cout << "\nAll the resources can be allocated to Process " << i + 1;
            cout << "\nAvailable resources are: ";

            for(k = 0; k < m; k++)
            {
                work[k] += alloc[i][k];
                cout << work[k] << " ";
            }

            finish[i] = 'y';
            cout << "\nProcess " << i + 1 << " executed?: " << finish[i] << "\n";
            count++;
            executed = true;
        }
    }

    // 6 & 7. Check safe state
    if(count == n)
    {
        cout << "\nSystem is in safe state";
        cout << "\nThe given state is safe state";
    }
    else if(!executed)
    {
    cout << "\nSystem is NOT in safe state";
    }
    else
    {
    goto A;
    }
    // 8. Stop the process.
    return 0;
}