#include<stdio.h>
 
int main()
{
      int i,j, limit, total = 0, x, counter = 0, time_quantum,temp1=0,pos;
      int wait_time = 0, turnaround_time = 0, burst_time[10], temp[10],pr[20],p[20];
      float average_wait_time, average_turnaround_time;
      char T[100][100];
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);
      x = limit;
      printf("Enter taskId  Priority  BurstTime\n");
      for(i = 0; i < limit; i++)
      {
 
           
            scanf("%s",T[i]);
            scanf("%d",&pr[i]);
            scanf("%d", &burst_time[i]);
 
            p[i]=i+1;  
      }
 
      printf("\nEnter Time Quantum(in ms):");
      scanf("%d", &time_quantum);
      for(i=0;i<limit;i++)
    {
        pos=i;
        for(j=i+1;j<limit;j++)
        {
             if(pr[j]<pr[pos]||pr[j]==pr[pos]&&p[i]>p[j])
                pos=j;
        }
 
        temp1=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp1;
 
        temp1=burst_time[i];
        burst_time[i]=burst_time[pos];
        burst_time[pos]=temp1;
        temp[i] = burst_time[i];

        temp1=p[i];
        p[i]=p[pos];
        p[pos]=temp1;
    }
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
      for(total = 0, i = 0; x != 0;)
      {
            if(temp[i] <= time_quantum && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
            }
            else if(temp[i] > 0)
            {
                  temp[i] = temp[i] - time_quantum;
                  total = total + time_quantum;
            }
            if(temp[i] == 0 && counter == 1)
            {
                  x--;

                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d",p[i], burst_time[i], total , total - burst_time[i]);

                  wait_time = wait_time + total - burst_time[i];
                  turnaround_time = turnaround_time + total;
                  counter = 0;
            }
            if(i == limit - 1)
            {
                  i = 0;
            }
            else
            {
                  i++;
            }
      }
      printf("\n");
      return 0;
}