#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];
int queue[MAX], front = -1, rear = -1;

void enqueue(int vertex) {
    if (rear == MAX - 1)
        printf("\nQueue Overflow\n");
    else {
        if (front == -1)
            front = 0;
        queue[++rear] = vertex;
    }
}

int dequeue() {
    int vertex;
    if (front == -1 || front > rear) {
        printf("\nQueue Underflow\n");
        return -1;
    } else {
        vertex = queue[front++];
        if (front > rear) {
            front = rear = -1;
        }
        return vertex;
    }
}

int isQueueEmpty() {
    return (front == -1);
}

void BFS(int startVertex, int numVertices) {
    int i, currentVertex;
    
    for (i = 0; i < numVertices; i++)
        visited[i] = 0;
    
    enqueue(startVertex);
    visited[startVertex] = 1;
    
    while (!isQueueEmpty()) {
        currentVertex = dequeue();
        printf("%d ", currentVertex);
        
        for (i = 0; i < numVertices; i++) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

void DFSUtil(int vertex, int numVertices) {
    int i;
    
    printf("%d ", vertex);
    visited[vertex] = 1;
    
    for (i = 0; i < numVertices; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFSUtil(i, numVertices);
        }
    }
}

void DFS(int startVertex, int numVertices) {
    int i;
    
    for (i = 0; i < numVertices; i++)
        visited[i] = 0;
    
    DFSUtil(startVertex, numVertices);
}

void displayAdjacencyMatrix(int numVertices) {
    int i, j;
    
    printf("Adjacency Matrix:\n");
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int numVertices, numEdges, i, j, u, v, startVertex;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    // Initialize adjacency matrix to 0
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }
    
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);
    
    printf("Enter the edges (u v) format:\n");
    for (i = 0; i < numEdges; i++) {
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // assuming it's an undirected graph
    }
    
    // Display the adjacency matrix
    displayAdjacencyMatrix(numVertices);
    
    printf("Enter the starting vertex for BFS and DFS: ");
    scanf("%d", &startVertex);
    
    printf("BFS Traversal: ");
    BFS(startVertex, numVertices);
    printf("\n");
    
    printf("DFS Traversal: ");
    DFS(startVertex, numVertices);
    printf("\n");
    
    return 0;
}
