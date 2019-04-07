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
	printf("First Come First Serve running");
	int i,sum=0;
	int *wt=(int*)malloc(3*sizeof(int));
	fcfs_sort(queue1,index[0]);
	int first_burst=queue1[0].burst;
	for(i=0;i<index[0];i++)
	{
		printf("\n");
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
			printf("Process of id:%d\n",queue1[i].p_id);
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
	printf("Average Waiting Time:%d\n",sum/3);
	
}


void prio_sort(struct process *q,int n_size)
{
	int i,j;
	struct process t;
	for(i=0;i<n_size;i++)
	{
		for(j=0;j<n_size-1-i;j++)
		{
			if(q[j].priority>q[j+1].priority)
			{
				t=q[j];
				q[j]=q[j+1];
				q[j+1]=t;
			}	
		}
	}
	int min=q[0].arrival;
	for(i=0;i<n_size;i++)
	{
		if(q[i].arrival<min)
		{
			min=q[i].arrival;
			j=i;
		}
	}
	t=q[j];
	q[0]=q[j];
	q[j]=t;
}

void priority()
{
	int i,j,k;
	struct process *temp=(struct process *)malloc(n*sizeof(struct process));
	struct process *newq=(struct process *)malloc(n*sizeof(struct process));
	struct process *wqueue=(struct process *)malloc(n*sizeof(struct process));
	prio_sort(queue2,index[1]);
	for(i=0;i<index[1];i++)
	{
		temp[0]=queue2[i];
		for(j=0;j<temp[0].burst;j++)
		{
			
			for(k=0;k<index[1];k++)
			{
				if(newq!=NULL&&newq[r].priority<=temp[0].priority)
				{
					wqueue[w]=temp[0];
					w++;
					temp[0]=newq[r];
				}
				if(temp[0].arrival<queue2[k].arrival)
				{
					temp[0].burst-=abs(queue2[k].arrival-temp[0].arrival);
					if(temp[0].burst>0)
					{ 
						newq[l]=temp[0];
						l++;
					}
					temp[0]=queue2[k];
				}
				else
				{
					wqueue[w]=queue2[k];
					w++;
				}
			}
		}
	}
}

main()
{
	enter();
	fcfs();
}
