#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 

struct node {
    int vertex;
    int weight;
    struct node *next;
};

struct node *A[MAX_VERTICES];
int parent[MAX_VERTICES];

int findpar(int i) {
    if (parent[i] == i) {
        return i;
    }
    return findpar(parent[i]);
}

void uni(int a, int b) {
    int x = findpar(a);
    int y = findpar(b);
    parent[x] = y;
}

void kruskal(int v) {
    int n = 0, a, b, min;

    for (int i = 0; i < v; i++) {
        parent[i] = i;
    }

    while (n < v - 1) {
        min = 999;
        for (int i = 0; i < v; i++) {
            struct node *temp = A[i];
            while (temp != NULL) {
                if (temp->weight < min && findpar(i) != findpar(temp->vertex)) {
                    a = i;
                    b = temp->vertex;
                    min = temp->weight;
                }
                temp = temp->next;
            }
        }
        uni(a, b);
        printf("Edge %d-%d : Weight = %d\n", a, b, min);
        n++;
    }
}

int main(){
    int u, v, w, n;
    char ch;
    printf("Enter the number of vertices : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        A[i] = NULL;
    }

    struct node *new;
    do{
        printf("\nEnter edge : ");
        scanf("%d %d", &u, &v);
        printf("\nEnter weight from edge %d to %d :  ", u, v);
        scanf("%d", &w);

        new = (struct node *)malloc(sizeof(struct node));
        new->vertex = v;
        new->weight = w;
        new->next = A[u];
        A[u] = new;

        new = (struct node *)malloc(sizeof(struct node));
        new->vertex = u;
        new->weight = w;
        new->next = A[v];
        A[v] = new;

        printf("\nDo you want to enter more edges (y/n) : ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    
    int m;
    while(1){
        printf("\n\n\t** MST Using Adjacency list using Kruskal algorithm");
        printf("\n1.Kruskal \n2.Exit\n");
        printf("\nEnter which algorithm : ");
        scanf("%d",&m);
        switch(m){
            case 1:
                kruskal(n);
                break;
            case 2:
                exit(0);
            default:
                printf("\nEnter a valid option.");
        }
    }
    return 0;
}
