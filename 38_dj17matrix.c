#include <stdio.h>

#define MAX_VERTICES 100
#define INF 99999

// Function to implement Dijkstra's algorithm to find shortest paths from source to all other vertices
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int V, int src) {
    int dist[MAX_VERTICES]; // The output array. dist[i] will hold the shortest distance from src to i
    int sptSet[MAX_VERTICES]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        // u is always equal to src in the first iteration.
        int minDist = INF, u;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    // Print the constructed distance array
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

int main() {
    int V, E, src, dest, weight;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    printf("Enter edges and weights (source destination weight):\n");
    for (int i = 0; i < E; ++i) {
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
        graph[dest][src] = weight; // Undirected graph, so both directions need to be updated
    }

    printf("\nAdjacency Matrix Representation of the Graph:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j] == 0)
                printf("0 ");
            else
                printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter the source vertex: ");
    scanf("%d", &src);

    printf("Shortest distances from source vertex %d:\n", src);
    dijkstra(graph, V, src);

    return 0;
}
