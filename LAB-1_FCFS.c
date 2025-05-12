#include <stdio.h>
#define MAX 10

void main() {
    int n;
    int AT[MAX], BT[MAX], CT[MAX], TAT[MAX], WT[MAX], RT[MAX], order[MAX];
    int i, j;
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
    int PT = 0;
    for (i = 0; i < n; i++) {
        CT[i] = PT = (PT < AT[i]) ? AT[i] : PT+BT[i];
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        RT[i] = WT[i];
    }
    for (i = 0; i < n; i++) {
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


/*
* OUTPUT:
* Enter the number of processes (max 10): 4
* Enter the Arrival Times (AT) for each process:
* AT[1]: 0
* AT[2]: 8
* AT[3]: 3
* AT[4]: 5
* Enter the Burst Times (BT) for each process:
* BT[1]: 7
* BT[2]: 3
* BT[3]: 4
* BT[4]: 6
* 
* +-----------+------+------+------+-------+------+------+
* |  Process  |  AT  |  BT  |  CT  |  TAT  |  WT  |  RT  |
* +-----------+------+------+------+-------+------+------+
* |  P1		|     0|     7|     7|      7|     0|     0|
* |  P2		|     8|     3|    20|     12|     9|     9|
* |  P3		|     3|     4|    11|      8|     4|     4|
* |  P4		|     5|     6|    17|     12|     6|     6|
* +-----------+------+------+------+-------+------+------+
* 
* Average Turnaround Time (TAT): 9.75
* Average Waiting Time (WT): 4.75
* Average Response Time (RT): 4.75
*/
