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

int mindist(int a[], int b[], int n) {
    int min = 999, ind = -1;
    for (int i = 0; i < n; i++) {
        if (!b[i] && a[i] < min) {
            min = a[i];
            ind = i;
        }
    }
    return ind;
}

void display(int parent[], int n) {
    printf("\n\nMinimum spanning tree is : ");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \n", parent[i], i);
    }
}

void prims(int n, int start_vertex) {
    int visited[n];
    int dist[n], u;

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = 999;
    }

    dist[start_vertex] = 0;
    for (int i = 0; i < n - 1; i++) {
        u = mindist(dist, visited, n);
        visited[u] = 1;

        struct node *temp = A[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (!visited[v] && weight < dist[v]) {
                dist[v] = weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    display(parent, n);
}

void displayGraph(int n) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++) {
        struct node *p = A[i];
        printf("%d: ", i);
        while (p != NULL) {
            printf("(%d, %d) -> ", p->vertex, p->weight);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int u, v, w, n, start_vertex;
    char ch;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        A[i] = NULL;
    }

    struct node *new;
    do {
        printf("\nEnter edge: ");
        scanf("%d %d", &u, &v);
        printf("\nEnter weight from edge %d to %d: ", u, v);
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

        printf("\nDo you want to enter more edges (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    displayGraph(n);

    printf("Enter the start vertex for Prim's algorithm: ");
    scanf("%d", &start_vertex);

    int m;
    while (1) {
        printf("\n\n\t** MST Using Adjacency list using Prim's algorithm");
        printf("\n1. Prim's \n2. Exit\n");
        printf("\nEnter which algorithm: ");
        scanf("%d", &m);
        switch (m) {
            case 1:
                prims(n, start_vertex);
                break;
            case 2:
                exit(0);
            default:
                printf("\nEnter a valid option.");
        }
    }
    return 0;
}
