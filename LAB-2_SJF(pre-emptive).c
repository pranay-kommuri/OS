#include <stdio.h>
#include <stdbool.h>
#define MAX 10

void main() {
    int n;
    int AT[MAX], BT[MAX], CT[MAX], TAT[MAX], WT[MAX], RT[MAX], remaining_BT[MAX], order[MAX];
    int i, j, completed = 0, current_time = 0;
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
        remaining_BT[i] = BT[i];
        order[i] = i;
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (AT[i] > AT[j]) {
                int temp = AT[i];
                AT[i] = AT[j];
                AT[j] = temp;
                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;
                temp = remaining_BT[i];
                remaining_BT[i] = remaining_BT[j];
                remaining_BT[j] = temp;
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    bool process_executing[MAX] = {false};
    int last_completed = -1; 

    while (completed < n) {
        int min_index = -1;
        int min_time = 9999999;

        for (i = 0; i < n; i++) {
            if (AT[i] <= current_time && !process_executing[i] && remaining_BT[i] > 0) {
                if (remaining_BT[i] < min_time) {
                    min_time = remaining_BT[i];
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            remaining_BT[min_index]--;
            current_time++;

            if (remaining_BT[min_index] == 0) {
                CT[min_index] = current_time;
                process_executing[min_index] = true;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    for (i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i]; 
        WT[i] = TAT[i] - BT[i]; 
        RT[i] = WT[i]; 

        avgTAT += TAT[i];
        avgWT += WT[i];
        avgRT += RT[i];
    }

    avgTAT /= n;
    avgWT /= n;
    avgRT /= n;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (order[i] > order[j]) {
                int temp = AT[i];
                AT[i] = AT[j];
                AT[j] = temp;
                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
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
            }
        }
    }

    printf("\n+-----------+------+------+------+-------+------+------+\n");
    printf("|  Process  |  AT  |  BT  |  CT  |  TAT  |  WT  |  RT  |\n");
    printf("+-----------+------+------+------+-------+------+------+\n");
    for (i = 0; i < n; i++) {
        int t = order[i];
        printf("|  P%d\t\t|%6d|%6d|%6d|%7d|%6d|%6d|\n", t + 1, AT[t], BT[t], CT[t], TAT[t], WT[t], RT[t]);
    }
    printf("+-----------+------+------+------+-------+------+------+\n");

    printf("\nAverage Turnaround Time (TAT): %.2f\n", avgTAT);
    printf("Average Waiting Time (WT): %.2f\n", avgWT);
    printf("Average Response Time (RT): %.2f\n", avgRT);
}
