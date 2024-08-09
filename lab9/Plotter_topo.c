#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX], visited[MAX], path[MAX], count = 0;
int stack[MAX], top = -1;
int c = 0;

// Recursive function to perform Depth-First Search (DFS)
void dfs(int n, int start) {
    visited[start] = 1;  // Mark the current node as visited
    path[start] = 1;     // Mark the node as part of the current path

    for (int i = 0; i < n; i++) {
        count++;  // Increment the operation count for each adjacency check

        // If there's a back edge (cycle detected)
        if (graph[start][i] && visited[i] == 1 && path[i] == 1) {
            c = 1;  // Set flag to indicate a cycle
        }
        
        // If the adjacent node is unvisited, perform DFS on it
        if (graph[start][i] && visited[i] == 0) {
            dfs(n, i);
        }
    }
    
    path[start] = 0;  // Mark the current node as not part of the path
    stack[++top] = start;  // Push the node onto the stack after processing
}

// Function to generate graphs and plot results
void ploter(int k) {
    // Open files for appending results
    FILE *f1 = fopen("TopologicalBEST.txt", "a");  // File for best-case results
    FILE *f2 = fopen("TopologicalWORST.txt", "a"); // File for worst-case results
    
    if (f1 == NULL || f2 == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int v;

    // Loop to generate and analyze graphs of increasing size
    for (int i = 1; i <= 10; i++) {
        v = i;

        // Variable-Length Array for adjacency matrix
        int arr[v][v];

        // Generate graph based on the type
        if (k == 0) {  // Complete graph (best-case scenario)
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    if (i != j) {
                        arr[i][j] = 1;  // Connect all nodes
                    } else {
                        arr[i][j] = 0;  // No self-loops
                    }
                }
            }
        }

        if (k == 1) {  // Linear chain (worst-case scenario)
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    arr[i][j] = 0;  // Initialize all entries to 0
                }
            }
            for (int i = 0; i < v - 1; i++) {
                arr[i][i + 1] = 1;  // Create a chain of connected nodes
            }
        }

        // Copy the generated graph to the global graph array
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                graph[i][j] = arr[i][j];
            }
        }

        // Reset the variables for each graph size
        count = 0;
        top = -1;
        c = 0;

        // Reset visited and path arrays
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
            path[i] = 0;
        }

        // Perform DFS traversal starting from each unvisited node
        for (int i = 0; i < v; i++) {
            if (visited[i] == 0) {
                dfs(v, i);
            }
        }

        // Output results to the appropriate file
        if (k == 0) {
            fprintf(f1, "%d\t%d\n", v, count);  // Best-case results
        } else {
            fprintf(f2, "%d\t%d\n", v, count);  // Worst-case results
        }
    }

    fclose(f1);
    fclose(f2);
}


// Main function to generate plots for best and worst-case scenarios
void main() {
    for (int i = 0; i < 2; i++) {
        ploter(i);
    }

    // Notify user that data has been written to files
    printf("DATA ENTERED INTO THE FILE\n");
}
