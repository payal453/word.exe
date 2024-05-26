#include<stdio.h>
#define max 100
int stack[max],n;
int top = -1;

int stackempty(){
    if(top == -1){
        return 0;
    }
    else{
        return 1;
    }
}

void push(int a){
    if(top == (max-1)){
        printf("\nStack Overflow ");
    }
    else{
        stack[++top] = a;
    }
}

int pop(){
    int a;
    if(top == -1){
        printf("\nStack underflow");
        return -1;
    }
    else{
        a = stack[top--];
    }
    return a;
}

void DFS(int G[10][10], int n){
    int visited[10] , v;

    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    printf("\nEnter start vertex : ");
    scanf("%d", &v);

    visited[v] = 1;
    push(v);

    while(stackempty() != 0){
        v = pop();
        printf("-%d",v);

        for(int i=1; i<=n; i++){
            if(G[v][i] == 1 && visited[i] == 0){
                visited[i] = 1;
                push(i);
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

    for (int i = 1; i <= e; i++) {
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

    DFS(G, n);
    return 0;
}
