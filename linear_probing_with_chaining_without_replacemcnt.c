#include<stdio.h>
#include<stdlib.h>
void insert(int item, int data[], int flag[], int chain[], int n)
{
    int key = item%n;
    int origKey=key;
    if(flag[key]==0)
    {
        flag[key]=1;
        data[key]=item;
    }
    else
    {
        while(flag[key]!=0)
        {
            origKey=key;
            key=(key+1)%n;
        }
        chain[origKey]=key;
        data[key]=item;
        flag[key]=1;
    }
}
void display(int data[], int flag[], int chain[], int n)
{
    for(int i=0; i<n; i++)
    {
        if(flag[i]==1)
        {
            printf("%d\t%d\t%d\n",i,chain[i],data[i]);
        }
        else
        {
            printf("%d\t%d\n",i,chain[i]);
        }
    }
}
void main()
{
    int n,c,item;
    printf("Enter size of hash table : ");
    scanf("%d",&n);
    int data[n],flag[n],chain[n];
    for(int i=0; i<n; i++)
    {
        chain[i]=-1;
        flag[i]=0;
    }
    printf("1.Insert, 2.Display\n");
    while(1)
    {
        printf("Enter choice : ");
        scanf("%d",&c);
        switch(c)
        {
        case 1:
            printf("Enter item to insert : ");
            scanf("%d",&item);
            insert(item, data, flag, chain, n);
            break;
        case 2:
            display(data,flag,chain,n);
            break;
        }
    }
}

