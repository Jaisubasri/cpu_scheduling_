#include<iostream>
#include<iomanip>
#include<climits>
//#include"queue.h"
using namespace std;
class queue
{
        int *q,front,rear,size;
        public:
                queue(int n)
                {
                    q=new int [n];
                    front=-1;
                    rear=-1;
                    size=n;
                }
                int enqueue(int);
                void dequeue();
                float MLQS(int burst[],int id[],int p[]);
                void display();
};
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
float queue::MLQS(int burst[],int id[],int p[])
{
    int size;
    int i,j,wt[size],tat[size],wait_avg,turn_avg;
    int temp;
    for(i=0;i<size;i++)
    {
        for(j=i+1;j<size;j++)
        {
            if(id[i]>id[j])
            {
                temp=p[i];
                p[j]=p[i];
                p[i]=temp;
                temp=burst[i];
                burst[j]=burst[i];
                burst[i]=temp;
                temp=id[i];
                id[j]=id[i];
                id[i]=temp;
            }
        }
    }
    for(i=0;i<size;i++)
        cout<<id[i]<<"-";
        enqueue(burst[i]);
    wt[0]=0;
    front=0;int num=1;
    while(front!=rear)
    {
        if(num<size)
        {
            wt[num]=q[front]+wt[num-1];
            tat[num-1]=q[front]+wt[num-1];
            num++;
            front++;
        }
    }
    tat[size-1]=q[front]+wt[size-1];
    front=0;
    cout<<"Processes |Priority| Burst time | Waiting time | Turn around time "<<endl;
    for(i=0;i<size;i++)
    {
       cout<<setw(7)<<p[i]<<setw(12)<<id[i]<<setw(12)<<q[front]<<setw(11)<<wt[i]<<setw(17)<<tat[i]<<endl;
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
int main()
{
    int ni,total_timing[7],total=0,n,choice;
    cout<<"Enter the number of processes :"<<endl;
    cin>>n;
    int burst[n],id[n],p[n];
    cout<<"Enter the burst time for each processes :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the burst time for "<<i+1<<" process :"<<endl;
        cin>>burst[i];
    }
    do
    {
        cout<<"Enter the method:\n1.FIRST COME FIRST SERVED \n3.SHORTEST REMAINING TIME\n6.MULTI LEVEL QUEUE  "<<endl;
        cin>>choice;
        switch(choice)
        {
        case 6:
            {
                queue obj6(n);
                for(int i=0;i<n;i++)
                {
                    p[i]=i;
                    cout<<"Enter the system/user process "<<i+1<<" :"<<endl;
                    cin>>id[i];
                }
                total_timing[5]=obj6.MLQS(burst,id,p);
            }

        }

    }while(choice!=8);
}
