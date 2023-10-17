#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
};

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    int current_time = 0;
    int completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= time_quantum) {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    printf("Process %d completed at time %d\n", processes[i].id, current_time);
                    completed++;
                } else {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }
            }
        }
    }

    return 0;
}
