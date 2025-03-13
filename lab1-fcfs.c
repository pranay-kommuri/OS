#include <stdio.h>
#define MAX 10

/*

#include<stdio.h>
#define MAX 100
int p[MAX], bt[MAX], at[MAX], tat[MAX], wt[MAX], ct[MAX], n;
void sort();
void fcfs();
void display();
void main(){
    printf("Enter the number of process:");
    scanf("%d",&n);
    printf("Enter the process data:\n\n");
    for (int i=0 ; i<n ; i++){
        printf("process no.:");
        scanf("%d",&p[i]);
        printf("process AT:");
        scanf("%d",&at[i]);
        printf("process BT:");
        scanf("%d",&bt[i]);
    }
    sort();
    fcfs();
    int sumTAT = 0, sumWT=0;
    for(int i=0; i<n ; i++){
        sumTAT=sumTAT + tat[i];
        sumWT=sumWT + wt[i];
    }
    int avgTAT=sumTAT/n , avgWT = sumWT/n;
    display();
    printf("\nThe avg TAT = %d\nThe avg WT = %d\n",avgTAT,avgWT);
}

void sort(){
    for (int i=0; i<n ; i++){
        for (int j=i+1; j<n ; j++){
            if (at[i] > at[j]){
                int temp = at[i];
                at[i]=at[j];
                at[j]=temp;
                temp = p[i];
                p[i]=p[j];
                p[j]=temp;
                temp = bt[i];
                bt[i]=bt[j];
                bt[j]=temp;
            }
        }
    }
}

void fcfs(){
    int pt=0;
    for (int i=0 ; i<n ;i++){
        pt = pt + bt[i];
        if(pt<at[i]){
            pt=at[i];
        }
        ct[i] = pt;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

void display(){
    printf("\nProcess  AT\tBT\tCT\tTAT\tWT\n");
    for (int i=0; i<n ; i++){
        printf("%d\t %d\t%d\t%d\t%d\t%d\t\n", p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
}
*/

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

    // Get Arrival Times (AT)
    printf("Enter the Arrival Times (AT) for each process:\n");
    for (i = 0; i < n; i++) {
        printf("AT[%d]: ", i + 1);
        scanf("%d", &AT[i]);
    }

    // Get Burst Times (BT)
    printf("Enter the Burst Times (BT) for each process:\n");
    for (i = 0; i < n; i++) {
        printf("BT[%d]: ", i + 1);
        scanf("%d", &BT[i]);
        order[i] = i;  // Store the original indices
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
        PT = (PT < AT[i]) ? AT[i] : PT+BT[i];
        CT[i] = PT;
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        RT[i] = WT[i];
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

    // Output the results
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
