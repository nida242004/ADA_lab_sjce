#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

int graph[SIZE][SIZE], queue[SIZE], rear = -1, front = 0;
int cnt = 0;

// Function to enqueue an element
void enqueue(int ele) {
    queue[++rear] = ele;
    printf("-->%c", ele + 65);
}

// Function to dequeue an element
int dequeue() {
    return queue[front++];
}

// Function to check if the queue is empty
int isEmpty() {
    if (front > rear) {
        front = 0;
        rear = -1;
        return 1;
    }
    return 0;
}

// Function to compute the in-degree of a node
int inDegree(int ind, int n) {
    int indegree = 0;
    for (int i = 0; i < n; i++) {
        cnt++;  // Increment the operation counter
        if (graph[i][ind] == 1) {
            indegree++;
        }
    }
    return indegree;
}

// Function to perform topological sorting
void topo(int n) {
    int in[n];

    for (int i = 0; i < n; i++) {
        in[i] = inDegree(i, n);

        if (in[i] == 0) {
            enqueue(i);
        }
    }

    int completed = 0;

    while (completed < n) {
        if (isEmpty()) {
            printf("Cycle exists as no node with indegree exists\n");
            exit(1);
        }

        int src = dequeue();
        completed++;

        for (int i = 0; i < n; i++) {
            if (graph[src][i] == 1) {
                graph[src][i] = 0;
                in[i]--;

                if (in[i] == 0) {
                    enqueue(i);
                }
            }
        }
    }
}

// Function to generate and analyze graphs
void plotter(int k) {
    FILE *f1 = fopen("TopologicalBEST.txt", "a");
    FILE *f2 = fopen("TopologicalWORST.txt", "a");

    if (f1 == NULL || f2 == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int v;
    int arr[SIZE][SIZE];  // Temporary adjacency matrix for each graph size

    for (int i = 1; i <= 10; i++) {
        v = i;

        // Generate graph based on the type
        if (k == 0) {  // Best-case scenario: Complete graph
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    if (i != j) {
                        arr[i][j] = 1;
                    } else {
                        arr[i][j] = 0;
                    }
                }
            }
        } else {  // Worst-case scenario: Linear chain
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    arr[i][j] = 0;
                }
            }
            for (int i = 0; i < v - 1; i++) {
                arr[i][i + 1] = 1;
            }
        }

        // Copy the generated graph to the global graph array
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                graph[i][j] = arr[i][j];
            }
        }

        // Reset variables for each graph size
        cnt = 0;
        rear = -1;
        front = 0;

        // Perform topological sorting
        topo(v);

        // Write results to the appropriate file
        if (k == 0) {
            fprintf(f1, "%d\t%d\n", v, cnt);  // Best-case results
        } else {
            fprintf(f2, "%d\t%d\n", v, cnt);  // Worst-case results
        }
    }

    fclose(f1);
    fclose(f2);
}

// Main function to generate plots for best and worst-case scenarios
int main() {
    for (int i = 0; i < 2; i++) {
        plotter(i);
    }

    printf("DATA ENTERED INTO THE FILE\n");
    return 0;
}
