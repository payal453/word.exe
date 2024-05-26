#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct queue {
    struct node *front, *rear;
};

struct node *A[10];
int n;

struct queue* create() {
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct queue* q, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(struct queue* q) {
    if (q->front == NULL)
        return -1;
    
    struct node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return data;
}

int queueEmpty(struct queue* q) {
    return (q->front == NULL);
}

void BFS(int start){
    int visited[10];
    struct node *p;

    for (int i = 1; i <= n; i++){
        visited[i] = 0;
    }

    struct queue* q = create();
    enqueue(q, start);
    visited[start] = 1;

    while (!queueEmpty(q)){
        int v = dequeue(q);
        printf("-%d", v);
        p = A[v];

        while (p != NULL){
            if (visited[p->data] == 0){
                enqueue(q, p->data);
                visited[p->data] = 1;
            }
            p = p->next;
        }
    }
}

void printAdjacencyList() {
    for (int i = 1; i <= n; i++) {
        struct node* temp = A[i];
        printf("Adjacency list of vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
int main(){
    int u, v;
    char ch;
    printf("Enter the no of vertices: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++){
        A[i] = NULL;
    }

    struct node *new, *p;
    do{
        printf("\nEnter edge: ");
        scanf("%d %d", &u, &v);

        new = (struct node *)malloc(sizeof(struct node));
        new->data = v;
        new->next = NULL;
        p = A[u];

        if (p == NULL){
            A[u] = new;
        }
        else{
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = new;
        }

        new = (struct node *)malloc(sizeof(struct node));
        new->data = u;
        new->next = NULL;
        p = A[v];

        if (p == NULL){
            A[v] = new;
        }
        else{
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = new;
        }

        printf("\nDo you want to enter more edges (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

     printf("\nAdjacency List:\n");
    printAdjacencyList();

    int startVertex;
    printf("\nEnter the start vertex: ");
    scanf("%d", &startVertex);

    printf("\nBFS Traversal: ");
    BFS(startVertex);

    return 0;
}
