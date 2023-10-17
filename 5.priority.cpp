#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
};

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    waitingTime[0] = 0; // Waiting time for the first process is 0

    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverages(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n];

    calculateTimes(processes, n, waitingTime, turnaroundTime);

    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }

    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

// Function to display the schedule
void displaySchedule(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    printf("ProcessID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, waitingTime[i], turnaroundTime[i]);
    }
}

// Function to perform Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    int waitingTime[n], turnaroundTime[n];

    while (completed < n) {
        int highestPriority = -1; // Index of the process with the highest priority

        // Find the process with the highest priority
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && (highestPriority == -1 || processes[i].priority < processes[highestPriority].priority)) {
                highestPriority = i;
                    }
        }

        // If no process is ready, move to the next arrival time
        if (highestPriority == -1) {
            time++;
        } else {
            // Execute the process for one unit of time
            processes[highestPriority].burstTime--;
            time++;

            // If the process is completed
            if (processes[highestPriority].burstTime == 0) {
                completed++;
                waitingTime[highestPriority] = time - processes[highestPriority].arrivalTime - processes[highestPriority].burstTime;
            }
        }
    }

    // Calculate and display average times and schedule
    calculateAverages(processes, n);
    displaySchedule(processes, n, waitingTime, turnaroundTime);
}

int main() {
    int n;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;

        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);

        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Perform Priority Scheduling
    priorityScheduling(processes, n);

    return 0;
}



