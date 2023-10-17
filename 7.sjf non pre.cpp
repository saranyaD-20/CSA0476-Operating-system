#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort the processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int current_time = 0;
    int completed = 0;
    while (completed < n) {
        int highest_priority = -1;
        int highest_priority_process = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    highest_priority_process = i;
                }
            }
        }

        if (highest_priority_process == -1) {
            current_time++;
        } else {
            processes[highest_priority_process].remaining_time--;

            if (processes[highest_priority_process].remaining_time == 0) {
                completed++;
                int turnaround_time = current_time - processes[highest_priority_process].arrival_time;
                int waiting_time = turnaround_time - processes[highest_priority_process].burst_time;
                printf("Process %d: Turnaround Time = %d, Waiting Time = %d\n",
                       processes[highest_priority_process].id, turnaround_time, waiting_time);
            }

            current_time++;
        }
    }

    return 0;
}
