#include<stdio.h>
 
int main()
{
    int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,pos,temp;
    char T[100][100];
    printf("Enter Total Number of Process:");
    scanf("%d",&n);
 
    printf("Enter taskId  Priority  BurstTime\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",T[i]);
        scanf("%d",&pr[i]);
        scanf("%d",&bt[i]);
        p[i]=i+1;           
    }

    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos]||pr[j]==pr[pos]&&p[i]>p[j])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0; 
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
    }
 
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     
        printf("\nT[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
  printf("\n ");
 
return 0;
}