#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct {
    int visited;
    int distance;
} Vertex;

int minDistance(Vertex* vertices, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!vertices[v].visited && vertices[v].distance <= min) {
            min = vertices[v].distance;
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int dest, int V) {
    Vertex vertices[V];
    for (int i = 0; i < V; i++) {
        vertices[i].visited = 0;
        vertices[i].distance = INT_MAX;
    }
    vertices[src].distance = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(vertices, V);
        vertices[u].visited = 1;

        for (int v = 0; v < V; v++) {
            if (!vertices[v].visited && graph[u][v] && vertices[u].distance != INT_MAX &&
                vertices[u].distance + graph[u][v] < vertices[v].distance) {
                vertices[v].distance = vertices[u].distance + graph[u][v];
            }
        }
    }

    printf("Shortest distance from node %d to node %d is: %d\n", src, dest, vertices[dest].distance);
}

void printGraph(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    printf("Adjacency Matrix Representation of the Graph:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j)
            printf("%d\t", graph[i][j]);
        printf("\n");
    }
}

int main() {
    int V, E;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    int graph[MAX_VERTICES][MAX_VERTICES];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;
    }

    printf("Enter edges and weights (source destination weight):\n");
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // Assuming undirected graph
    }

    printf("Graph (Adjacency Matrix Representation):\n");
    printGraph(graph, V);

    int src, dest;
    printf("Enter the source node: ");
    scanf("%d", &src);
    printf("Enter the destination node: ");
    scanf("%d", &dest);

    dijkstra(graph, src, dest, V);

    return 0;
}
