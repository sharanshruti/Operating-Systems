#include<stdio.h>
 
 int main()
{
    int n,bt[100],wt[100],tat[100],i,j,P[100];
    char T[100][100];
    printf("Enter total number of processes:");
    scanf("%d",&n);
 
    printf("Enter taskId  Priority  BurstTime\n");
    for(i=0;i<n;i++)
    {   
        scanf("%s",T[i]);
        scanf("%d",&P[i]);
        scanf("%d",&bt[i]);
    }
 
    wt[0]=0;   
 
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 
    printf("Process  Burst Time   Waiting Time  Turnaround Time\n");
 
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        printf("T[%d]       %d       \t     %d       \t  %d \n",i+1,bt[i],wt[i],tat[i]);
    }
 
    return 0;
}


// T1 4 20
// T2 3 25
// T3 3 25
// T4 5 15
// T5 5 20
// T6 1 10
// T7 3 30
// T8 10 25

// T1 1 50
// T2 1 50
// T3 1 50
// T4 1 50
// T5 1 50
// T6 1 50

// T1 4 8
// T2 1 40
// T3 2 9
// T4 3 15