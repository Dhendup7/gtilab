#include <stdio.h>
int main() {
int n, i, time = 0, done;
int bt[20], rt[20], wt[20], tat[20]; 
int quantum;
float avg_wt = 0, avg_tat = 0;
printf("Enter number of processes: ");
scanf("%d", &n);
printf("Enter time quantum: ");
scanf("%d", &quantum);
for (i = 0; i < n; i++) {
printf("Enter burst time for Process %d: ", i + 1);
scanf("%d", &bt[i]);
rt[i] = bt[i]; 
}
printf("\n--- Round Robin Execution ---\n");
printf("Process\tStart\tEnd\tRemaining\n");
do{
done = 1; 
for (i = 0; i < n; i++) {
if (rt[i] > 0) {
done = 0; 
int start = time;
if (rt[i] > quantum) {
time += quantum;
rt[i] -= quantum;
} else {
time += rt[i];
wt[i] = time - bt[i]; 
rt[i] = 0;
}
printf("P%d\t%d\t%d\t%d\n", i + 1, start, time, rt[i]);
}
}
} while (done == 0);
for (i = 0; i < n; i++) {
tat[i] = bt[i] + wt[i];
avg_wt += wt[i];
avg_tat += tat[i];
}
avg_wt /= n;
avg_tat /= n;
printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
for (i = 0; i < n; i++)
printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
printf("\nAverage Waiting Time: %.2f ms", avg_wt);
printf("\nAverage Turnaround Time: %.2f ms\n", avg_tat);
return 0;
}
