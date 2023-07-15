#include<iostream>
#include"queue.h"
#include"linkedlist.h"
using namespace std;
float short_job_first(int* ,int);
float round_robin(int*,int);
int main()
{
    int n,choice,i;
    float total_timing[5];
    cout<<endl<<endl;
    cout<<"\t\t\t\t\t\t!!!CPU SCHEDULING!!!"<<endl<<endl<<endl;
    cout<<"\t\t\t\t\tEnter the number of processes :";
    cin>>n;
    int burst[n],id[n],ats[n],su[n],p[n];
    cout<<"\n\t\t\t\t\tEnter the burst time for each processes :";
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"\n\t\t\t\t\tEnter the burst time for "<<i+1<<" process :";
        cin>>burst[i];
    }
    do
    {
        cout<<"\n\n";
        cout<<"\t\t\t\t\tEnter the method:\n\t\t\t\t\t1.FIRST COME FIRST SERVED \n\t\t\t\t\t2.SHORTEST JOB FIRST \n\t\t\t\t\t3.SHORTEST REMAINING TIME \n\t\t\t\t\t4.ROUND ROBIN SCHEDULING \n\t\t\t\t\t5.PRIORITY SCHEDULING \n\t\t\t\t\t6.MULTI LEVEL QUEUE "<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            {
               system("cls");
               queue obj1(n);
               for(i=0;i<n;i++)
               {
                    obj1.enqueue(burst[i]);
               }
               total_timing[0]=obj1.FCFS();
               break;
            }
        case 2:
            {
               system("cls");
               float tots;
               tots=short_job_first(burst,n);
               total_timing[1]=tots;
               break;
            }
        case 3:
            {
               system("cls");
               int total,i;
               cout<<"Enter the process id and arrival time \n";
               for(i=0;i<n;i++)
               {
                    cout<<"Enter values for "<<i+1<<endl;
                    cin>>id[i];
                    cin>>ats[i];
                    total=total+burst[i];
               }
               queue obj3;
               total_timing[2]=obj3.SRT(n,burst,id,ats);
               break;
            }
        case 4:
            {
                system("cls");
                float tot;
                tot=round_robin(burst,n);
                total_timing[3]=tot;
                break;
            }
        case 5:
            {
                system("cls");
                int i,j,temp;
                ll obj4;
                int p[n],pri[n];
                for(i=0;i<n;i++)
                {
                    p[i]=i;
                    cout<<"Enter the priority "<<i+1<<" :"<<endl;
                    cin>>pri[i];
                }
                for(i=0;i<n;i++)
                {
                    for(j=i+1;j<n;j++)
                    {
                        if(pri[i]>pri[j])
                        {
                            temp=p[i];
                            p[i]=p[j];
                            p[j]=temp;
                            temp=burst[i];
                            burst[i]=burst[j];
                            burst[j]=temp;
                            temp=pri[i];
                            pri[i]=pri[j];
                            pri[j]=temp;
                        }
                    }
                }
                obj4.create(p[0],burst[0],pri[0]);
                for(i=1;i<n;i++)
                {
                    obj4.inserts(p[i],burst[i],pri[i]);
                }
                total_timing[4]=obj4.priorityqueue(n);
                break;
            }
        case 6:
            {
                system("cls");
                for(i=0;i<n;i++)
                {
                    p[i]=i+1;
                    cout<<"Enter whether system/user process (0 or 1) : "<<endl;
                    cin>>su[i];
                }
                queue obj6(n);
                total_timing[5]=obj6.mlqs(burst,su,p);
                break;
            }
        }

    }while(choice!=8);
    cout<<"THE CPU SCGEDULLING IS COMPLETED!!!"<<endl;
}

float short_job_first(int burst[],int n)
{
    int p[n],wt[n],tat[n],i,j,total=0,pos,temp;
    float avg_wt,avg_tat;
    for(i=0;i<n;i++)
    {
        p[i]=i+1;
    }
   //sorting of burst times
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(burst[j]<burst[pos])
                pos=j;
        }
        temp=burst[i];
        burst[i]=burst[pos];
        burst[pos]=temp;
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
    wt[0]=0;
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=burst[j];
        total+=wt[i];
    }
    avg_wt=(float)total/n;
    total=0;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=burst[i]+wt[i];
        total+=tat[i];
        cout<<"\n"<<p[i]<<"\t\t"<<burst[i]<<"\t\t"<<wt[i]<<"\t\t\t"<<tat[i]<<endl;
    }
    avg_tat=(float)total/n;
    cout<<"\n\nAverage Waiting Time = "<<avg_wt<<endl;
    cout<<"\nAverage Turnaround Time = "<<avg_tat<<endl;
    cout<<endl;
    return avg_tat;
}

float round_robin(int burst[],int n)
{
    int i,sum=0,count=0,y,quant,wt=0,tat=0,at[n],temp[n];
    float avg_wt,avg_tat;
    y=n;
    for(i=0; i<n; i++)
    {
        cout<<"Enter the arrival time of the Process "<< i+1<<" :"<<endl;
        cout<<"Arrival time is:"<<endl;
        cin>>at[i];
        temp[i]=burst[i];
    }
    cout<<"Enter the Time Quantum for the process: "<<endl;
    cin>>quant;
    cout<<"\nProcess No \t\t Burst Time \t\t TAT \t\t Waiting Time "<<endl;
    for(sum=0, i = 0; y!=0; )
    {
        if(temp[i] <= quant && temp[i] > 0)
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count=1;
        }
        else if(temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if(temp[i]==0 && count==1)
        {
            y--;
            cout<<"\nProcess No["<<i+1<<"] \t\t "<<burst[i]<<" \t\t\t "<<sum-at[i]<<" \t\t\t "<<sum-at[i]-burst[i]<<endl;
            wt = wt+sum-at[i]-burst[i];
            tat = tat+sum-at[i];
            count =0;
        }
        if(i==n-1)
        {
            i=0;
        }
        else if(at[i+1]<=sum)
        {
            i++;
        }
        else
        {
            i=0;
        }
    }
    avg_wt = wt * 1.0/n;
    avg_tat = tat * 1.0/n;
    cout<<"\nAverage Turn Around Time: \t"<<avg_wt<<endl;
    cout<<"\nAverage Waiting Time: \t"<<avg_tat<<endl;
    cout<<endl;
    return avg_tat;
}
