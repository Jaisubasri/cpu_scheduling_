#include<iostream>
#include<iomanip>
#include"queue.h"
using namespace std;
int queue::enqueue(int elt)
{
    if(rear==size)
    {
        cout<<"Queue Full!!"<<endl;
        return 0;
    }
    else
    {
        rear=rear+1;
        q[rear]=elt;
    }
}
void queue::dequeue()
{
    int item;
    front=front+1;
    item=q[front];
}
float queue::FCFS()
{
    int wait[size],turn[size];
    float wait_avg=0,turn_avg=0;
    wait[0]=0;
    front=front+1;
    int i=1;
    while(front!=rear)
    {
        if(i<size)
        {
            wait[i]=q[front]+wait[i-1];
            turn[i-1]=q[front]+wait[i-1];
            i++;
            front++;
        }
    }
    turn[size-1]=q[front]+wait[size-1];
    front=0;
    cout<<"Processes | Burst time | Waiting time | Turn around time "<<endl;
    for(i=0;i<size;i++)
    {
       cout<<setw(7)<<i+1<<setw(12)<<q[front]<<setw(11)<<wait[i]<<setw(17)<<turn[i]<<endl;
       front++;
       wait_avg+=wait[i];
       turn_avg+=turn[i];
    }
    cout<<"The average waiting time is "<<setprecision(3)<<wait_avg/size<<endl;
    cout<<"The average turn around time is "<<setprecision(3)<<turn_avg/size<<endl;
    return turn_avg/size;
}
float queue::SRT(int n,int burst [],int id[],int ats[])
{
    cout<<"hi"<<endl;
    int rt[n],wt[n],ct[n],count[n],tat[n];
    int i,j,k;
    float tot_wt,tot_tat;
    for(i=0;i<n;i++)
    {
        rt[i]=burst[i];
        count[i]=0;
    }
    cout<<"hi"<<endl;
    int comp=0,t=0,min=INT_MAX;
    int shortest=0,finish=0;
    bool check=false;
    while(comp!=n)
    {
        for(j=0;j<n;j++)
        {
            if((ats[j]<=t) && (rt[j]<min) && rt[j]>0)
            {
                min=rt[j];
                shortest=j;
                check=true;
            }
        }
        if(check==false)
        {
            t++;
            continue;
        }
        rt[shortest]--;
        enqueue(shortest);
        min=rt[shortest];
        if(min==0)
            min=INT_MAX;
        if(rt[shortest]==0)
        {
            comp++;
            check=false;
            finish=t+1;
        }
        t++;
    }
    cout<<"hi"<<endl;
    for(i=0;i<n;i++)
    {
        front=0;
        while(front!=rear+1)
        {
            if(i==q[front])
            {
                count[i]++;
                if(count[i]==burst[i])
                {
                    ct[i]=front+1;
                    dequeue();
                }
                else
                    dequeue();
            }
            else
                dequeue();
        }
    }
    for(k=0;k<n;k++)
    {
        tat[k]=ct[k]-ats[k];
        wt[k]=tat[k]-burst[k];
        tot_wt+=wt[k];
        tot_tat+=tat[k];
    }
    cout<<"Process | arrival time | burst time | comp time | tat time | wt time "<<endl;
    for(k=0;k<n;k++)
    {
        cout<<setw(5)<<k+1<<setw(10)<<ats[k]<<setw(15)<<burst[k]<<setw(15)<<ct[k]<<setw(10)<<tat[k]<<setw(10)<<wt[k]<<endl;
    }
    cout<<"The average waiting time is "<<setprecision(3)<<tot_wt/n<<endl;
    cout<<"The average turn around time is "<<setprecision(3)<<tot_tat/n<<endl;
    return tot_tat/n;
}
float queue::mlqs(int burst[],int su[],int p[])
{
    int i,j,temp,wt[size],tat[size],k=1;
    float wait_avg=0.0,turn_avg=0.0;
    for(i=0;i<size;i++)
    {
        for(j=i+1;j<size;j++)
        {
            temp=p[i];
			p[i]=p[j];
			p[j]=temp;
			temp=burst[i];
			burst[i]=burst[j];
			burst[j]=temp;
			temp=su[i];
			su[i]=su[j];
			su[j]=temp;
        }
    }
    wt[0]=0;
    for(i=0;i<size;i++)
        enqueue(burst[i]);
    front=front+1;
    while(front!=rear)
    {
        if(k<size)
        {
            wt[k]=q[front]+wt[k-1];
            tat[k-1]=q[front]+wt[k-1];
            k++;
            front++;
        }
    }
    tat[size-1]=q[front]+wt[size-1];
    front=0;
    cout<<"Processes | Priority | Burst time | Waiting time | Turn around time "<<endl;
    for(i=0;i<size;i++)
    {
       cout<<setw(7)<<p[i]<<setw(12)<<su[i]<<setw(7)<<q[front]<<setw(11)<<wt[i]<<setw(17)<<tat[i]<<endl;
       front++;
       wait_avg+=wt[i];
       turn_avg+=tat[i];
    }
    cout<<"The average waiting time is "<<setprecision(3)<<wait_avg/size<<endl;
    cout<<"The average turn around time is "<<setprecision(3)<<turn_avg/size<<endl;
    return turn_avg/size;
}
void queue :: display()
{
    front=front+1;
    do
    {
        cout<<q[front]<<"   ";
        front++;
    }while(front!=rear+1);
}
