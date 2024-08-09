#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100], isCyclic = 0;
int bfsCount = 0, count = 0;
int orderCount = 0;

// Function to perform Breadth-First Search (BFS)
void bfs(int n, int start) {
    int queue[n], parent[n];
    int rear = -1, front = -1, i, parentNode;

    // Mark the starting node as visited
    visited[start] = 1;
    count++;
    queue[++rear] = start;
    parent[rear] = -1;

    // Process the queue
    while (rear != front) {
        start = queue[++front];
        parentNode = parent[front];
        
        // Print the current node
        printf("--> %c", start + 65);

        // Iterate through all adjacent nodes
        for (i = 0; i < n; i++) {
            orderCount++;

            // Check for cycles
            if (i != parentNode && graph[start][i] && visited[i]) {
                isCyclic = 1; // Cycle detected
            }

            // If an adjacent node is unvisited, add it to the queue
            if (graph[start][i] && !visited[i]) {
                queue[++rear] = i;
                parent[rear] = start;
                visited[i] = 1;
                count++;
            }
        }
    }
}

void main() {
    int n, start;

    bfsCount = 0;
    count = 0;
    orderCount = 0;

    // Input number of nodes
    printf("Enter the number of nodes in the graph:\n");
    scanf("%d", &n);

    // Input adjacency matrix
    printf("Enter the Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
        visited[i] = 0; // Initialize visited array
    }

    // Print the adjacency matrix
    printf("The Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    // Initialize and perform BFS traversal from node 0
    isCyclic = 0;
    printf("\nBFS traversal starting from node %c\n", 65);
    bfsCount++;
    bfs(n, 0);

    // Check if the graph is connected
    if (count == n) {
        printf("\nThe Graph is connected\n");
    } else {
        printf("\nThe Graph is not connected\n");
        start = 1;
        while (count != n) {
            if (!visited[start]) {
                bfsCount++;
                bfs(n, start);
                printf("\n");
            }
            start++;
        }
    }

    // Output the number of connected components
    printf("\nThe number of components is %d\n", bfsCount);

    // Output if the graph is cyclic
    if (isCyclic) {
        printf("\nThe graph is cyclic\n");
    } else {
        printf("\nThe graph is acyclic\n");
    }
}
