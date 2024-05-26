#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int parent;
    int rank;
} Subset;

typedef struct {
    int vertices;
    int** graph;
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->graph = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; ++i) {
        graph->graph[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; ++j)
            graph->graph[i][j] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->graph[src][dest] = weight;
    graph->graph[dest][src] = weight; // Undirected graph
}

void printGraph(Graph* graph) {
    printf("Adjacency Matrix Representation of the Graph:\n");
    for (int i = 0; i < graph->vertices; ++i) {
        for (int j = 0; j < graph->vertices; ++j)
            printf("%d\t", graph->graph[i][j]);
        printf("\n");
    }
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void printMST(int parent[], Graph* graph) {
    printf("Edge   Weight\n");
    for (int i = 1; i < graph->vertices; ++i)
        printf("%d - %d    %d\n", parent[i], i, graph->graph[i][parent[i]]);
}

void kruskalMST(Graph* graph) {
    int V = graph->vertices;
    int parent[V];
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int edge_count = 0;

    while (edge_count < V - 1) {
        int min_weight = INT_MAX;
        int u = -1, v = -1;

        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (find(subsets, i) != find(subsets, j) && graph->graph[i][j] && graph->graph[i][j] < min_weight) {
                    min_weight = graph->graph[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        if (u != -1 && v != -1) {
            parent[v] = u;
            Union(subsets, u, v);
            edge_count++;
        }
    }

    printf("Minimum Spanning Tree using Kruskal's algorithm:\n");
    printMST(parent, graph);
    free(subsets);
}

int main() {
    int V, E;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V);

    printf("Enter edges and weights (source destination weight):\n");
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }

    printf("Graph (Adjacency Matrix Representation):\n");
    printGraph(graph);

    kruskalMST(graph);

    for (int i = 0; i < V; ++i)
        free(graph->graph[i]);
    free(graph->graph);
    free(graph);

    return 0;
}
