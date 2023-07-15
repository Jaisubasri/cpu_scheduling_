#include<iostream>
#include<iomanip>
#include"linklist.h"
using namespace std;
void ll::create(int ele,int ele1,int ele2)
{
    struct node*n=new node;
    n->id=ele;
    n->burst=ele1;
    n->pri=ele2;
    n->link=NULL;
    start=n;
}
void ll::inserts(int ele,int ele1,int ele2)
{
    ptr=start;
    while(ptr->link!=NULL)
    {
        ptr=ptr->link;
    }
    struct node*n=new node;
    n->id=ele;
    n->burst=ele1;
    n->pri=ele2;
    n->link=NULL;
    ptr->link=n;
}
void ll::display()
{
    ptr=start;
    while(ptr!=NULL)
    {
        cout<<ptr->id<<"-"<<ptr->burst<<"-"<<ptr->pri<<endl;
        ptr=ptr->link;
    }
}
float ll::priorityqueue(int n)
{
    ptr=start;
    int wt[n],tat[n],i=1;
    float wt_avg,tat_avg;
    wt[0]=0;
    ptr=start;
    while(ptr->link!=NULL)
    {
        if(i<n)
        {
            wt[i]=ptr->burst+wt[i-1];
            tat[i-1]=ptr->burst+wt[i-1];
            i++;
            ptr=ptr->link;
        }
    }
    tat[n-1]=ptr->burst+wt[n-1];
    for(i=0;i<n;i++)
    {
        wt_avg+=wt[i];
        tat_avg+=tat[i];
    }
    cout << "\nProcesses  "<< " Burst time  "<< " Waiting time  " << " Turn around time\n"<<endl;
    ptr=start;
    for(i=0;i<n;i++)
    {
        cout << "   " << ptr->id<< "\t\t"<< ptr->burst << "\t    " << wt[i] << "\t\t  " << tat[i] <<endl;
        ptr=ptr->link;
    }
    cout << "\nAverage waiting time = " << wt_avg/n<<" ."<<endl;
    cout << "\nAverage turn around time = " << tat_avg/n <<" ."<<endl;
    return tat_avg/n;
}
