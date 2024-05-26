#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct AdjList {
    Node* head;
} AdjList;

typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

typedef struct Stack {
    int top;
    unsigned capacity;
    int* array;
} Stack;

Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

int isQueueFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int isStackEmpty(Stack* stack) {
    return (stack->top == -1);
}

int isStackFull(Stack* stack) {
    return (stack->top == stack->capacity - 1);
}

void push(Stack* stack, int item) {
    if (isStackFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

void BFS(Graph* graph, int start) {
    Queue* queue = createQueue(graph->V);
    int visited[graph->V];
    for (int i = 0; i < graph->V; ++i)
        visited[i] = 0;

    visited[start] = 1;
    enqueue(queue, start);

    printf("Breadth First Traversal starting from vertex %d: ", start);

    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);

        Node* temp = graph->array[current].head;
        while (temp) {
            int adjNode = temp->dest;
            if (!visited[adjNode]) {
                visited[adjNode] = 1;
                enqueue(queue, adjNode);
            }
            temp = temp->next;
        }
    }

    printf("\n");
    free(queue->array);
    free(queue);
}

void DFSUtil(Graph* graph, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);

    Node* temp = graph->array[v].head;
    while (temp) {
        int adjNode = temp->dest;
        if (!visited[adjNode])
            DFSUtil(graph, adjNode, visited);
        temp = temp->next;
    }
}

void DFS(Graph* graph, int start) {
    int visited[graph->V];
    for (int i = 0; i < graph->V; ++i)
        visited[i] = 0;

    printf("Depth First Traversal starting from vertex %d: ", start);
    DFSUtil(graph, start, visited);
    printf("\n");
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        Node* pCrawl = graph->array[v].head;
        printf("Adjacency list of vertex %d\n", v);
        printf("head");
        while (pCrawl) {
            printf(" -> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int main() {
    int V, E, src;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V);

    printf("Enter edges (source destination):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    printf("Graph (Adjacency List Representation):\n");
    printGraph(graph);

    printf("Enter the starting vertex for BFS and DFS traversal: ");
    scanf("%d", &src);

    BFS(graph, src);
    DFS(graph, src);

    for (int i = 0; i < V; ++i) {
        Node* current = graph->array[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
