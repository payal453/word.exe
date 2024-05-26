#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a node in the adjacency list
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Structure to represent an adjacency list
typedef struct {
    AdjListNode* head;
} AdjList;

// Structure to represent the graph
typedef struct {
    int V;
    AdjList* array;
} Graph;

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency list representation of the graph
void printAdjacencyList(Graph* graph) {
    printf("Adjacency List Representation of the Graph:\n");
    for (int i = 0; i < graph->V; ++i) {
        AdjListNode* pCrawl = graph->array[i].head;
        printf("Vertex %d: ", i);
        while (pCrawl) {
            printf("(%d, %d) -> ", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("NULL\n");
    }
}

// Function to find the vertex with the minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function to implement Dijkstra's algorithm to find shortest paths from source to all other vertices
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i

    int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        // u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (AdjListNode* pCrawl = graph->array[u].head; pCrawl != NULL; pCrawl = pCrawl->next) {
            int v = pCrawl->dest;

            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && pCrawl->weight && dist[u] != INT_MAX && dist[u] + pCrawl->weight < dist[v])
                dist[v] = dist[u] + pCrawl->weight;
        }
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

int main() {
    int V, E, src, dest, weight;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V);

    printf("Enter edges and weights (source destination weight):\n");
    for (int i = 0; i < E; ++i) {
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printf("Graph (Adjacency List Representation):\n");
    printAdjacencyList(graph);

    printf("\nEnter the source vertex: ");
    scanf("%d", &src);

    printf("Shortest distances from source vertex %d:\n", src);
    dijkstra(graph, src);

    return 0;
}
