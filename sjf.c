#include<stdio.h>
 int main()
{
    int bt[20],p[20],wt[20],tat[20],i,j,n,pos,temp,P[100];
    char T[100][100];
    printf("Enter number of process:");
    scanf("%d",&n);
  
    printf("Enter taskId  Priority  BurstTime\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",T[i]);
        scanf("%d",&P[i]);
        scanf("%d",&bt[i]);

        p[i]=i+1;         
    }
  
   //sorting of burst times
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]<bt[pos]||bt[j]==bt[pos]&&p[i]>p[j])
                pos=j;
        }
  
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
        
  
    printf("Process    Burst Time    Waiting Time   Turnaround Time\n");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];   
        printf(" T[%d]         %d       \t     %d            \t %d\n",p[i],bt[i],wt[i],tat[i]);
    }
  
}