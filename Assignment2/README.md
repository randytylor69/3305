# FCFS CPU Scheduling

A C implementation of the First-Come, First-Served (FCFS) CPU scheduling algorithm with idle time handling and performance metrics.

## Compilation

Compile using `make`:

```bash
make
```

Or compile directly with `gcc`:

```bash
gcc -Wall main.c -o main.out
```

## Execution

Run the program:

```bash
./main.out
```

Clean build artifacts:

```bash
make clean
```

## Sample Input and Output

### Input

```text
Enter number of processes: 3
Process 1 - Arrival time: 0
Process 1 - Burst time: 4
Process 2 - Arrival time: 1
Process 2 - Burst time: 3
Process 3 - Arrival time: 6
Process 3 - Burst time: 2
```

### Output

```text
PID   Arrival    Burst      Completion   Turnaround   Waiting
1     0          4          4            4            0
2     1          3          7            6            3
3     6          2          9            3            1

Average Waiting Time: 1.33
Average Turnaround Time: 4.33
```
