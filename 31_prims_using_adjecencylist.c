#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

typedef struct {
    int numVertices;
    AdjList* array;
} Graph;

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*) malloc(numVertices * sizeof(AdjList));
    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->array[v].head;
        printf("Vertex %d:", v);
        while (temp) {
            printf(" -> %d (weight %d)", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printMST(int parent[], int numVertices, Graph* graph) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < numVertices; i++) {
        Node* temp = graph->array[i].head;
        while (temp) {
            if (temp->vertex == parent[i]) {
                printf("%d - %d \t%d \n", parent[i], i, temp->weight);
                break;
            }
            temp = temp->next;
        }
    }
}

int minKey(int key[], int mstSet[], int numVertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < numVertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void primMST(Graph* graph) {
    int numVertices = graph->numVertices;
    int parent[MAX];
    int key[MAX];
    int mstSet[MAX];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, mstSet, numVertices);
        mstSet[u] = 1;

        Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->vertex;
            if (mstSet[v] == 0 && temp->weight < key[v]) {
                parent[v] = u;
                key[v] = temp->weight;
            }
            temp = temp->next;
        }
    }

    printMST(parent, numVertices, graph);
}

int main() {
    int numVertices, numEdges, src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    Graph* graph = createGraph(numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (source destination weight) format:\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printf("Graph (Adjacency List Representation):\n");
    printGraph(graph);

    printf("\nMinimum Spanning Tree (Prim's Algorithm):\n");
    primMST(graph);

    return 0;
}
