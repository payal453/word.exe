#include<stdio.h>
#include<stdlib.h>

#define max 100
int n,top = -1;

int queue[max];
int f = -1, r = -1;

int stackempty(){
    if(top == -1){
        return 0;
    }
    else{
        return 1;
    }
}
void nq(int c) {
    if (r == n - 1) {
        printf("\nQueue full\n");
    } else {
        if (f == -1) {
            f = 0;
        }
        r++;
        queue[r] = c;
    }
}

int dq() {
    int a = -1;
    if (f == -1 || f > r) {
        printf("Queue empty\n");
    } else {
       a = queue[f++];
       if(f > r){
        f = r = -1;
       }
    }
    return a;
}

int queueempty() {
    if (r == -1 && f == -1) {
        return 0;
    } else {
        return 1;
    }
}

void BFS(int G[10][10], int n) {
    int visited[10], v;

    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    printf("\nEnter start vertex : ");
    scanf("%d", &v);

    nq(v);
    visited[v] = 1;

    while (queueempty() != 0) {
        v = dq();
        printf("-%d", v);

        for (int i = 1; i <= n; i++) {
            if (G[v][i] == 1 && visited[i] == 0) {
                nq(i);
                visited[i] = 1; 
            }
        }
    }
}

int main() {
    int G[10][10];
    int a, b, e;

    printf("Enter the no of vertex : ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G[i][j] = 0;
        }
    }

    printf("\nEnter the no of edges : ");
    scanf("%d", &e);

    for (int i = 0; i < e; i++) {
        printf("\nEnter edge : ");
        scanf("%d %d", &a, &b);
        G[a][b] = G[b][a] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%5d ", G[i][j]);
        }
        printf("\n");
    }

    int m;
    while(1){
        printf("\n\nEnter which traversal : ");
        printf("\n\n1.BFS \n2.exit\n");
        scanf("%d",&m);
        switch(m){
            case 1:
                BFS(G,n);
                break;
            case 2:
                exit(0);
            default:
                printf("\nEnter the  valid option.");
        }
    }
    return 0;
}
