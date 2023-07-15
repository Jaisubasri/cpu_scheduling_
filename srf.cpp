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
                int dequeue();
                float FCFS();
                float SRT(int n,int burst [],int id[],int at[]);
                void display();
};
struct Process
{
    int proid,bt,art;
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
int queue::dequeue()
{
    int item;
    if(rear==front)
    {
        cout<<"Queue Empty!!"<<endl;
        return 0;
    }
    else
    {
        front=front+1;
        item=q[front];
    }
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
float queue::SRT(int n,int burst [],int id[],int at[])
{
    int rt[n],wt[n];
    int i,j,k;
    for(i=0;i<n;i++)
    {
        rt[i]=burst[i];
    }
    int comp=0,t=0,min=INT_MAX;
    int shortest=0,finish;
    bool check=false;
    while(comp!=n)
    {
        for(j=0;j<n;j++)
        {
            if((at[j]<=t) && (rt[j]<min) && (rt[j]>0))
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
        if(rt[shortest]==0)
        {
            comp++;
            cout<<comp;
            check=false;
            finish=t+1;
        }
        wt[shortest]=finish-burst[shortest]-at[shortest];
        if(wt[shortest]<0)
        {
            wt[shortest]=0;
        }
        t++;
    }
    for(i=0;i<n;i++)
    {
        cout<<wt[i]<<endl;
    }
    display();
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
    int n,choice,i,total_timing[7],total=0;
    cout<<"Enter the number of processes :"<<endl;
    cin>>n;
    int burst[n],id[n],at[n];
    queue obj1(n);
    cout<<"Enter the burst time for each processes :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the burst time for "<<i+1<<" process :"<<endl;
        cin>>burst[i];
    }
    do
    {
        cout<<"Enter the method:\n1.FIRST COME FIRST SERVED \n3.SHORTEST REMAINING TIME "<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            {
               for(i=0;i<n;i++)
               {
                    obj1.enqueue(burst[i]);
               }
               total_timing[0]=obj1.FCFS();
               break;
            }
        case 3:
            {
                cout<<"Enter the process id and arrival time \n";
                for(int i=0;i<n;i++)
                {
                    cout<<"Enter values for "<<i+1<<endl;
                    cin>>id[i];
                    cin>>at[i];
                    total=total+burst[i];
                }
                queue obj3(total+1);
                total_timing[2]=obj3.SRT(n,burst,id,at);
            }
        }

    }while(choice!=8);
}
