#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edge;
} Graph;

typedef struct Node {
    int dest, weight;
    struct Node* next;
} Node;

typedef struct AdjList {
    Node* head;
} AdjList;

typedef struct GraphAdjList {
    int V;
    AdjList* array;
} GraphAdjList;

typedef struct subset {
    int parent;
    int rank;
} subset;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*) malloc(E * sizeof(Edge));
    return graph;
}

GraphAdjList* createGraphAdjList(int V) {
    GraphAdjList* graph = (GraphAdjList*) malloc(sizeof(GraphAdjList));
    graph->V = V;
    graph->array = (AdjList*) malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdgeToAdjList(GraphAdjList* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraphAdjList(GraphAdjList* graph) {
    for (int v = 0; v < graph->V; ++v) {
        Node* temp = graph->array[v].head;
        printf("Vertex %d:", v);
        while (temp) {
            printf(" -> %d (weight %d)", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int find(subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight > edgeB->weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    subset *subsets = (subset*) malloc(V * sizeof(subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }

    free(subsets);
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V, E);
    GraphAdjList* graphAdjList = createGraphAdjList(V);

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = weight;
        addEdgeToAdjList(graphAdjList, src, dest, weight);
    }

    printf("Graph (Adjacency List Representation):\n");
    printGraphAdjList(graphAdjList);

    printf("\nMinimum Spanning Tree (Kruskal's Algorithm):\n");
    KruskalMST(graph);

    free(graph->edge);
    free(graph);
    free(graphAdjList->array);
    free(graphAdjList);
    return 0;
}
