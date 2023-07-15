#include<iostream>
using namespace std;
class queue
{
        int *q,front,rear,size;
        public:
                queue()
                {
                    q=new int [20];
                    front =-1;
                    rear=-1;
                    size=20;
                }
                queue(int n)
                {
                    q=new int[n];
                    front=-1;
                    rear=-1;
                    size=n;
                }
                int enqueue(int);
                void dequeue();
                float FCFS();
                float SRT(int n,int burst [],int id[],int at[]);
                float mlqs(int burst[],int su[],int p[]);
                void display();
};
