#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

static int cmp_arrival(const void *a, const void *b)
{
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    return (p1->arrival_time != p2->arrival_time)
               ? (p1->arrival_time - p2->arrival_time)
               : (p1->pid - p2->pid);
}

int main(void)
{
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Error: Invalid number of processes.\n");
        return 1;
    }

    Process *p = malloc(n * sizeof(Process));
    if (!p)
    {
        perror("malloc failed");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Process %d - Arrival time: ", p[i].pid);
        if (scanf("%d", &p[i].arrival_time) != 1 || p[i].arrival_time < 0)
        {
            fprintf(stderr, "Error: Arrival time must be >= 0.\n");
            free(p);
            return 1;
        }
        printf("Process %d - Burst time: ", p[i].pid);
        if (scanf("%d", &p[i].burst_time) != 1 || p[i].burst_time <= 0)
        {
            fprintf(stderr, "Error: Burst time must be > 0.\n");
            free(p);
            return 1;
        }
    }

    /* Sort by arrival time (FCFS) */
    qsort(p, n, sizeof(Process), cmp_arrival);

    int cur_time = 0;
    double total_wt = 0.0, total_tat = 0.0;

    for (int i = 0; i < n; i++)
    {
        /* Handle CPU idle time */
        if (cur_time < p[i].arrival_time)
        {
            cur_time = p[i].arrival_time;
        }
        int start_time = cur_time;
        p[i].completion_time = start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        cur_time = p[i].completion_time;
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    /* Output Results Table */
    printf("\n%-5s %-10s %-10s %-12s %-12s %-10s\n",
           "PID", "Arrival", "Burst", "Completion", "Turnaround", "Waiting");
    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-10d %-10d %-12d %-12d %-10d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    free(p);
    return 0;
}