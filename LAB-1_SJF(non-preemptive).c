#include <stdio.h>
#define MAX 10

void main() {
    int n;
    int AT[MAX], BT[MAX], CT[MAX], TAT[MAX], WT[MAX], RT[MAX], order[MAX];
    int i, j, time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0, avgRT = 0;

    printf("Enter the number of processes (max 10): ");
    scanf("%d", &n);
    if (n > MAX) {
        printf("The maximum number of processes is 10. Exiting.\n");
        return;
    }
    printf("Enter the Arrival Times (AT) for each process:\n");
    for (i = 0; i < n; i++) {
        printf("AT[%d]: ", i + 1);
        scanf("%d", &AT[i]);
    }
    printf("Enter the Burst Times (BT) for each process:\n");
    for (i = 0; i < n; i++) {
        printf("BT[%d]: ", i + 1);
        scanf("%d", &BT[i]);
        order[i] = i;
    }

    // Sort processes by Arrival Time (AT)
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (AT[i] > AT[j]) {
                int temp = AT[i];
                AT[i] = AT[j];
                AT[j] = temp;
                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    // Array to track if the process has been completed
    int isCompleted[MAX] = {0};

    while (completed < n) {
        int idx = -1;
        int minBT = 99999999;

        // Find the process with the shortest burst time that is ready to execute
        for (i = 0; i < n; i++) {
            if (AT[i] <= time && !isCompleted[i] && BT[i] < minBT) {
                minBT = BT[i];
                idx = i;
            }
        }

        // If no process is ready to execute (i.e., all processes have arrived but not yet started)
        if (idx == -1) {
            time++;  // Increment time until some process arrives
        } else {
            // Execute the selected process
            time += BT[idx];  // Increment time by the burst time of the selected process
            CT[idx] = time;   // Set the completion time for this process
            TAT[idx] = CT[idx] - AT[idx];  // Turnaround time: CT - AT
            WT[idx] = TAT[idx] - BT[idx];  // Waiting time: TAT - BT
            RT[idx] = CT[idx] - AT[idx] - BT[idx];  // Response time: time - AT - BT

            isCompleted[idx] = 1;  // Mark the process as completed
            completed++;  // Increment the completed process counter
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        avgTAT += TAT[i];
        avgWT += WT[i];
        avgRT += RT[i];
    }
    avgTAT /= n;
    avgWT /= n;
    avgRT /= n;

    // Sort the results back by the process number for output
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (order[i] > order[j]) {
                int temp = AT[i];
                AT[i] = AT[j];
                AT[j] = temp;
                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;
                temp = CT[i];
                CT[i] = CT[j];
                CT[j] = temp;
                temp = TAT[i];
                TAT[i] = TAT[j];
                TAT[j] = temp;
                temp = WT[i];
                WT[i] = WT[j];
                WT[j] = temp;
                temp = RT[i];
                RT[i] = RT[j];
                RT[j] = temp;
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    // Output the results
    printf("\n+-----------+------+------+------+-------+------+------+\n");
    printf("|  Process  |  AT  |  BT  |  CT  |  TAT  |  WT  |  RT  |\n");
    printf("+-----------+------+------+------+-------+------+------+\n");
    for (i = 0; i < n; i++) {
        int t = order[i];
        printf("|  P%d\t\t|%6d|%6d|%6d|%7d|%6d|%6d|\n", t + 1, AT[t], BT[t], CT[t], TAT[t], WT[t], RT[t]);
    }
    printf("+-----------+------+------+------+-------+------+------+\n");

    // Print averages
    printf("\nAverage Turnaround Time (TAT): %.2f\n", avgTAT);
    printf("Average Waiting Time (WT): %.2f\n", avgWT);
    printf("Average Response Time (RT): %.2f\n", avgRT);
}
