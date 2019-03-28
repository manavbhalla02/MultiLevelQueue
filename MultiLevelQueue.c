#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
struct process
{
	int arrival;
	int p_id;
	int priority;
	int burst;
}*queue1,*queue2,*queue3;// queues comprising of classes
static int n,index[3]={0,0,0}; //no. of processes 
void enter()
{
	int i;
	printf("Enter no. of processes\n");
	scanf("%d",&n);
	struct process t;
	queue1=(struct process*)malloc(n*sizeof(struct process));
	queue2=(struct process*)malloc(n*sizeof(struct process));
	queue3=(struct process*)malloc(n*sizeof(struct process));
	for(i=0;i<n;i++)
	{
		printf("Enter Process Id:");
		scanf("%d",&t.p_id);
		printf("Enter Arrival Time");
		scanf("%d",&t.arrival);
		printf("Enter priority:\n");
		scanf("%d",&t.priority);
		printf("Enter burst time:\n");
		scanf("%d",&t.burst);
		if(t.priority>=1&&t.priority<=5)
		{
			queue1[index[0]]=t;
			++index[0];
		}
		else if(t.priority>=6&&t.priority<=12)
		{
			queue2[index[1]]=t;
			++index[1];
		}
		else
		{
			queue3[index[2]]=t;
			++index[2];
		}
	}
	
}
void fcfs_sort(struct process *q,int n_size)
{
	int i,j;
	struct process t;
	for(i=0;i<n_size;i++)
	{
		for(j=0;j<n_size-1-i;j++)
		{
			if(q[j].arrival>q[j+1].arrival)
			{
				t=q[j];
				q[j]=q[j+1];
				q[j+1]=t;
			}	
		}
	}
}
void fcfs()
{
	int i,sum=0;
	int first_burst=0;
	int *wt=(int*)malloc(index[0]*sizeof(int));
	fcfs_sort(queue1,index[0]);
	for(i=0;i<index[0];i++)
	{
		//printf("")
		if(i==0)
		{
			printf("Process of id%d\n",queue1[i].p_id);
			printf("Turn around time:%d\n",queue1[i].burst);
			printf("waiting time:0\n");
			first_burst+=queue1[i+1].burst;
			wt[i]=0;
		}
		else
		{
			printf("Process of id%d\n",queue1[i].p_id);
			printf("Turn around time:%d\n",first_burst);
			printf("waiting time:%d\n",first_burst-queue1[i].burst);
			wt[i]=first_burst-queue1[i].burst;
			first_burst+=queue1[i+1].burst;
		}
	}
	for(i=0;i<index[0];i++)
	{
		sum+=wt[i];
	}
	printf("Average Waiting Time:%d\n",sum);
	
}
main()
{
	enter();
	fcfs();
}
