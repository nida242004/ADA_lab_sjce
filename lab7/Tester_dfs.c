#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100], isCyclic = 0;
int dfsCount = 0, count = 0;
int dcount = 0;
int path[100];
int d;

// Function to perform Depth-First Search (DFS)
void dfs(int n, int start, int parent) {
    // Mark the current node as visited and part of the current path
    visited[start] = 1;
    path[start] = 1;
    count++;
    
    // Print the current node
    printf("--> %c ", start + 65);

    // Iterate through all adjacent nodes
    for (int i = 0; i < n; i++) {
        // Check for cycles
        if (d == 1) {  // Directed graph
            if (i != parent && graph[start][i] && visited[i] == 1 && path[i] == 1) {
                isCyclic = 1;  // Cycle detected
            }
        } else {  // Undirected graph
            if (i != parent && graph[start][i] && visited[i]) {
                isCyclic = 1;  // Cycle detected
            }
        }
        
        dcount++;
        
        // Recur for unvisited adjacent nodes
        if (graph[start][i] && !visited[i]) {
            dfs(n, i, start);
        }
    }
    
    // Unmark the current node as part of the current path
    path[start] = 0;
}

void main() {
    int n, start;
    dfsCount = 0;
    count = 0;
    dcount = 0;
    d = 0;

    // Input number of nodes
    printf("Enter the number of nodes in the graph:\n");
    scanf("%d", &n);
    
    // Input adjacency matrix
    printf("Enter the Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
        visited[i] = 0;  // Initialize visited array
        path[i] = 0;     // Initialize path array
    }

    // Input graph type (0 for undirected, 1 for directed)
    printf("Enter 1 if the graph is directed, 0 otherwise:\n");
    scanf("%d", &d);

    // Print the adjacency matrix
    printf("The Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    // Initialize and perform DFS traversal from node 0
    isCyclic = 0;
    printf("\nDFS traversal starting from node %c\n", 65);
    dfs(n, 0, -1);
    dfsCount++;

    // Check if the graph is connected
    if (count == n) {
        printf("\nThe Graph is connected\n");
    } else {
        printf("\nThe Graph is not connected\n");
        start = 1;
        while (count != n) {
            if (!visited[start]) {
                printf("\n");
                dfs(n, start, -1);
                dfsCount++;
            }
            start++;
        }
    }

    // Output the number of connected components
    printf("\nThe number of components is %d\n", dfsCount);

    // Output if the graph is cyclic
    if (isCyclic) {
        printf("\nThe graph is cyclic\n");
    } else {
        printf("\nThe graph is not cyclic\n");
    }
}
