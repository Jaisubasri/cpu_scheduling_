struct node
{
    int id;
    int burst;
    int pri;
    struct node *link;
};
class ll
{
    struct node *start,*ptr;
public:
    void create(int ele,int ele1,int ele2);
    void inserts(int ele,int ele1,int ele2);
    void display();
    float priorityqueue(int n);
};

