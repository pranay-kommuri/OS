#include <stdio.h>
#include <math.h>

// Function to compute GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute LCM of two numbers
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// Function to compute LCM of an array
int compute_hyperperiod(int periods[], int n) {
    int hyperperiod = periods[0];
    for (int i = 1; i < n; i++) {
        hyperperiod = lcm(hyperperiod, periods[i]);
    }
    return hyperperiod;
}

// Utilization bound calculation
double utilization_bound(int n) {
    return n * (pow(2, 1.0/n) - 1);
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    
    int periods[n], burst_times[n];
    double total_utilization = 0.0;
    
    // Input task parameters
    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i+1);
        printf("Enter burst time (Bi): ");
        scanf("%d", &burst_times[i]);
        printf("Enter period (Ti): ");
        scanf("%d", &periods[i]);
        total_utilization += (double)burst_times[i] / periods[i];
    }
    
    // Calculate hyperperiod
    int hyperperiod = compute_hyperperiod(periods, n);
    printf("\nHyperperiod (LCM): %d\n", hyperperiod);
    
    // Check schedulability
    double bound = utilization_bound(n);
    printf("Total utilization: %.3f\n", total_utilization);
    printf("Utilization bound: %.3f\n", bound);
    
    if (total_utilization <= bound) {
        printf("Tasks are schedulable under RMS!\n");
    } else {
        printf("Tasks may not be schedulable. Further analysis needed.\n");
    }
    
    return 0;
}


/*
Enter number of tasks: 3

Task 1:
Enter burst time (Bi): 3
Enter period (Ti): 3

Task 2:
Enter burst time (Bi): 6
Enter period (Ti): 4

Task 3:
Enter burst time (Bi): 8
Enter period (Ti): 5

Hyperperiod (LCM): 60
Total utilization: 4.100
Utilization bound: 0.780
Tasks may not be schedulable. Further analysis needed.
*/
