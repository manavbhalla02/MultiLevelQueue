#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
struct process // structure having process id, arrival time , priority and burst time of process
{
	int arrival;
	int p_id;
	int priority;
	int burst;
}*queue1,*queue2,*queue3,*proc;// queues comprising of classes
static int n,index[]={0,0,0}; //no. of processes and index consists the size of each queue
void enter();//To take the entry from user
void arrival_sort(); //Sorting according to arrival time
int fcfs(int u);//First Come First Serve algorithm
void prioritySortReal(struct process *q,int n_size);//Sorting according to priority
void priority_sort(struct process *q,int n_size);//Sorting according to priority
												//Then swaping process at first position with process of least arrival time
												//Then swaping process at second position with process of second highest priority
int priority(int u);//Preamptive priority scheduling algorithm
int round_robin(int u);//Round robin algorithm
void arrival_sort(struct process *q,int n_size)
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
int fcfs(int u)
{
	printf("First Come First Serve running\n");
	int i,sum=0;
	int *wt=(int*)malloc(3*sizeof(int));
	arrival_sort(queue1,index[0]);
	int first_burst=queue1[0].burst;
	for(i=u;i<index[0];)
	{
		printf("Execution of process id:%d from queue1\n",queue1[i].p_id);
		i++;
		return i;
	}
	
}
void prioritySortReal(struct process *q,int n_size)
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
}
void priority_sort(struct process *q,int n_size)
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
	q[j]=q[0];
	q[0]=t;
	j=1;
	min=q[1].priority;
	for(i=1;i<n_size;i++)
	{
		if(q[i].priority<min)
		{
			min=q[i].priority;
			j=i;
			
		}
	}
	t=q[j];
	q[j]=q[1];
	q[1]=t;
}

int priority(int u)
{
	printf("Priority scheduling\n");
	int i=0,j,k,r=0,s=0,l=0,size=index[1];
	struct process temp;
	struct process *wqueue=(struct process *)malloc(index[1]*sizeof(struct process));
	struct process *allproc=(struct process *)malloc(2*index[1]*sizeof(struct process));
	temp=queue2[0];
	for(k=1;k<size;k++)
	{
		if(temp.arrival<queue2[k].arrival&&temp.priority>queue2[k].priority)//got preampted
		{
			temp.burst-=abs(queue2[k].arrival-temp.arrival);
			if(temp.burst>0)
			{
				wqueue[l]=temp;
				l++;	
			}
			else
			{
				temp.burst=0;
			}
			allproc[s]=temp;
		    s++;
			temp=queue2[k];
		}
		else
		{
			wqueue[l]=queue2[k];
			l++;
		}
		allproc[s]=temp;
		s++; 
		if(k==size-1)
		{
			for(j=0;j<l;j++)
			{
				queue2[j]=wqueue[j];
			}
			size=l;
		}
	}
	prioritySortReal(queue2,size);
	for(j=0;j<size;j++)
	{
		allproc[s]=queue2[j];
		s++;
	}
	struct process *tem=(struct process*)malloc(s*sizeof(struct process));
	j=0;
	for (i=0; i<s-1; i++) 
        if (allproc[i].p_id!= allproc[i+1].p_id) 
            tem[j++] = allproc[i];
			  
    tem[j++] = allproc[s-1]; 
    for (i=0; i<j; i++) 
        allproc[i] = tem[i]; 
        
	for(i=u;i<j;)
	{
		printf("Execution of process id:%d from queue2\n",allproc[i].p_id);
		i++;
		return i;
	}
}
int round_robin(int u)
{
	printf("round robin scheduling\n");
	int i,l=0,k=index[2],s=0,j;
	struct process *temp=(struct process *)malloc(n*sizeof(struct process));
	struct process *proc=(struct process *)malloc(n*sizeof(struct process));
	arrival_sort(queue3,index[2]);
	int quant=4;
	for(i=0;i<k;i++)
	{
		queue3[i].burst-=quant;
		if(queue3[i].burst>0)
		{
			temp[l]=queue3[i];
			l++;
		}
		proc[s]=queue3[i];
		s++;
		if(i==k-1)
		{
			for(j=0;j<l;j++)
			{
				queue3[j]=temp[j];
			}
			k=l;
			i=-1;
			l=0;
		}
	}
	for(i=u;i<s;)
	{
		printf("Execution of process id:%d from queue3\n",proc[i].p_id);
		i++;
		return i;
	}
}
void enter()
{
	int i;
	printf("Enter no. of processes\n");
	scanf("%d",&n);
	struct process t;
	queue1=(struct process*)malloc(n*sizeof(struct process));//QUEUE 1 WHICH PROCESSES ACCORDING TO FIRST COME FIRST SERVE BASIS (PRIORITY IN RANGE 1 TO 5)
	queue2=(struct process*)malloc(n*sizeof(struct process));//QUEUE 2 WHICH PROCESSES ACCORDING TO PREEMPTIVE PRIORITY SCHEDULING ALGORITHM (PRIORITY IN RANGE 6 TO 12)
	queue3=(struct process*)malloc(n*sizeof(struct process));//QUEUE 3 WHICH PROCESSES ACCORDING TO ROUND ROBIN ALGORITHM (PRIORITY AFTER 13)
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
main()
{
	int i,j,k,n,l=0,t=0,v=0;
	enter();
	for(i=0;i<n;i++)
	{
		for(j=0;j<index[0];j++)
		{
			l=fcfs(l);
		}
		sleep(10);
		for(k=0;k<index[1];k++)
		{
			t=priority(t);	
		}
		sleep(10);
		for(n=0;n<index[2];n++)
		{
			v=round_robin(v);	
		}
		sleep(10);
	}
}
