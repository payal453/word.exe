
#include<stdio.h>

int smallestPath(int visited[] ,int  dist[] , int v)
{
    int min = 99;
    int a;
    for(int i=0;i<v;i++)
    {
        if(dist[i]<min && visited[i]!=1)
        {
            min = dist[i];
            a=i;
        }
    }
    return a;
}

void diskstra(int a[][100], int v) {

    int visited[v], u,dist[v];

    for(int i=0;i<v;i++)
    {
        visited[i]=0;
        dist[i]=99;
    }

    printf("Enter start : ");
    scanf("%d",&u);

    dist[u]=0;

    for(int i=0;i<v;i++)
    {
        u = smallestPath(visited,dist,v);
        visited[u] = 1;
        for(int j=0;j<v;j++)
        {
            if(visited[j]!=1 && dist[u]!=99 && a[u][j]!=99 && dist[u] + a[u][j] < dist[j])
            {
                dist[j] = dist[u] + a[u][j];
            }
        }
    }

    for(int i=0;i<v;i++)
    {
        printf("%d---%d\n",i,dist[i]);
    }
    
}
int main( )
{
    int v;
    printf("Enter the no of vertices : ");
    scanf("%d",&v);
    int a[100][100];
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
       
            a[i][j]=99;
        }
       
    }
    int e,st,en;
    int w;
    printf("Enter the no of edges : ");
    scanf("%d",&e);
    for(int i=0;i<e;i++)
    {
        printf("Enter the start and end : ");
        scanf("%d %d",&st,&en);
        printf("Enter weight : ");
        scanf("%d",&w);

        a[st][en] = a[en][st] = w;
    }

    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }

    diskstra(a,v);
}