#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100], isCyclic = 0;
int dfsCount = 0, count = 0;
int dcount = 0;
int path[100];
int d;

// Recursive function to perform Depth-First Search (DFS)
void dfs1(int n, int start, int parent) {
    // Mark the current node as visited
    visited[start] = 1;
    count++;  // Increase the number of nodes visited

    // Explore all adjacent nodes
    for (int i = 0; i < n; i++) {
        // Check for cycles in the graph
        if (i != parent && graph[start][i] && visited[i]) {
            isCyclic = 1;  // Cycle detected
        }

        dcount++;  // Increment the DFS operation count

        // Recursively perform DFS on unvisited adjacent nodes
        if (graph[start][i] && !visited[i]) {
            dfs1(n, i, start);
        }
    }
}

// Function to generate graphs and plot results
void plotter(int k) {
    // Open files for appending results
    FILE *f1 = fopen("DFSBEST.txt", "a");
    FILE *f2 = fopen("DFSWORST.txt", "a");  // Corrected filename to "DFSWORST.txt"
    int v;

    // Loop to generate and analyze graphs of increasing size
    for (int i = 1; i <= 10; i++) {
        v = i;

        // Generate graph based on type
        if (k == 0) {  // Best-case graph: Complete graph
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    graph[i][j] = (i != j) ? 1 : 0;  // All nodes are connected except self-loops
                }
            }
        }

        if (k == 1) {  // Worst-case graph: Linear chain
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    graph[i][j] = 0;  // Initialize all entries to 0
                }
            }
            for (int i = 0; i < v - 1; i++) {
                graph[i][i + 1] = 1;  // Create a chain of connected nodes
            }
        }

        // Reset variables for each graph size
        isCyclic = 0;
        dfsCount = 0;
        count = 0;
        dcount = 0;

        // Perform DFS traversal starting from node 0
        dfs1(v, 0, -1);
        dfsCount++;

        // Check for connectivity by performing DFS from unvisited nodes
        int start = 1;
        while (count != v) {
            if (visited[start] != 1) {
                dfs1(v, start, -1);
                dfsCount++;
            }
            start++;
        }

        // Output results to appropriate file
        if (k == 0) {
            fprintf(f2, "%d\t%d\n", v, dcount);  // Best-case results
        } else {
            fprintf(f1, "%d\t%d\n", v, dcount);  // Worst-case results
        }
    }

    // Close files
    fclose(f1);
    fclose(f2);
}

void main() {
    // Generate plots for best and worst-case scenarios
    for (int i = 0; i < 2; i++) {
        plotter(i);
    }

    // Notify user that data has been written to files
    printf("DATA ENTERED INTO THE FILE\n");
}
