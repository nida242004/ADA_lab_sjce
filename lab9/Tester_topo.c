#include <stdio.h> 
#include <stdlib.h> 

#define MAX 100  // Maximum number of vertices

int graph[MAX][MAX], visited[MAX], path[MAX], count = 0;
int stack[MAX], top = -1;  // Stack to store the topological order
int c = 0;  // Flag to detect cycles

// Recursive function to perform Depth-First Search (DFS)
void dfs(int n, int start) {
    visited[start] = 1;  // Mark the current node as visited
    path[start] = 1;     // Mark the node as part of the current path

    // Explore all adjacent nodes
    for (int i = 0; i < n; i++) {
        // If there's a back edge (cycle detected)
        if (graph[start][i] && visited[i] == 1 && path[i] == 1) {
            c = 1;  // Set flag to indicate cycle
        }
        
        // If the adjacent node is unvisited, perform DFS on it
        if (graph[start][i] && visited[i] == 0) {
            dfs(n, i);
        }
    }
    
    // Mark the current node as not part of the path
    path[start] = 0;
    
    // Push the node onto the stack
    stack[++top] = start;
}

// Main function
void main() {
    int n;
    
    // Get the number of vertices from the user
    printf("\nEnter the number of vertices:\n");
    scanf("%d", &n);
    
    // Get the adjacency matrix from the user
    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
        visited[i] = 0;  // Initialize visited array to 0
    }
     
    // Perform DFS for all unvisited nodes
    printf("\nTopological Order:\n");
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            dfs(n, i);
        }
    }
    
    // Check if a cycle was detected
    if (c == 1) {
        printf("IT HAS A LOOP SO NO TOPOLOGICAL ORDER\n");
        return;
    }
    
    // Print the topological order from the stack
    for (int i = 0; i < n; i++) {
        printf(" --> %c", stack[i] + 65);  // Print vertices as 'A', 'B', 'C', etc.
    }
    printf("\n");
}


/*
Enter the number of vertices:
3

Enter the adjacency matrix:
0
1
1
1
0
1
1
1
0

Topological Order:
IT HAS A LOOP SO NO TOPOLOGICAL ORDER
PS C:\Users\syeda\OneDrive\Desktop\ADA_lab_sjce\lab9> ./a.exe

Enter the number of vertices:
5

Enter the adjacency matrix:
0
0
1
0
0
0
0
1
0
0
0
0
0
1
1
0
0
0
0
1
0
0
0
0
0

Topological Order:
 --> E --> D --> C --> A --> B
*/