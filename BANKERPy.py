# 1. Start the program

# 2. Get the values of processes and resources
n, m = map(int, input("Enter the number of processes and resources: ").split())

alloc = [[0] * m for _ in range(n)]
maxm = [[0] * m for _ in range(n)]
need = [[0] * m for _ in range(n)]
total = [0] * m
avail = [0] * m
work = [0] * m
finish = ['n'] * n

print("Enter the claim matrix:")
for i in range(n):
    row = list(map(int, input().split()))
    for j in range(m):
        maxm[i][j] = row[j]

print("Enter the allocation matrix:")
for i in range(n):
    row = list(map(int, input().split()))
    for j in range(m):
        alloc[i][j] = row[j]

print("Enter the resource vector:")
total = list(map(int, input().split()))

# 3. Get the available value
for i in range(n):
    for j in range(m):
        avail[j] += alloc[i][j]

for i in range(m):
    work[i] = total[i] - avail[i]

# 4. After allocation find the need value
for i in range(n):
    for j in range(m):
        need[i][j] = maxm[i][j] - alloc[i][j]

count = 0

# 5. Check whether it’s possible to allocate
while True:
    executed = False

    for i in range(n):
        if finish[i] == 'n':
            c = 0
            for j in range(m):
                if need[i][j] <= work[j]:
                    c += 1

            if c == m:
                print(f"\nAll the resources can be allocated to Process {i + 1}")
                print("Available resources are:", end=" ")

                for k in range(m):
                    work[k] += alloc[i][k]
                    print(work[k], end=" ")

                finish[i] = 'y'
                print(f"\nProcess {i + 1} executed?: {finish[i]}")
                count += 1
                executed = True

    # 6 & 7. Check safe state
    if count == n:
        print("\nSystem is in safe state")
        print("The given state is safe state")
        break
    elif not executed:
        print("\nSystem is NOT in safe state")
        break

# 8. Stop the program