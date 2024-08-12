// #include <stdio.h>
// #include <stdlib.h>

// int graph[100][100], visited[100], isCyclic = 0;
// int bfsCount = 0, count = 0;
// int orderCount = 0;

// // Function to perform Breadth-First Search (BFS)
// void bfs(int n, int start) {
//     int queue[n], parent[n];
//     int rear = -1, front = -1;
//     int i, parentNode;

//     // Initialize the BFS
//     visited[start] = 1;
//     count++;
//     queue[++rear] = start;
//     parent[rear] = -1;

//     // Perform BFS
//     while (rear != front) {
//         start = queue[++front];
//         parentNode = parent[front];
        
//         // Explore all adjacent nodes
//         for (i = 0; i < n; i++) {
//             if (i != parentNode && graph[start][i] && visited[i]) {
//                 isCyclic = 1;  // Cycle detected
//             }
            
//             orderCount++;  // Increment the BFS operation count

//             // Enqueue unvisited adjacent nodes
//             if (graph[start][i] && !visited[i]) {
//                 queue[++rear] = i;
//                 parent[rear] = start;
//                 visited[i] = 1;
//                 count++;
//             }
//         }
//     }
// }

// // Function to generate graphs and plot results
// void plotter(int k) {
//     // Open files for appending results
//     FILE *f1 = fopen("BFSBEST.txt", "a");
//     FILE *f2 = fopen("BFSWORST.txt", "a");
//     int v;

//     // Loop to generate and analyze graphs of increasing size
//     for (int i = 1; i <= 10; i++) {
//         v = i;

//         // Generate graph based on type
//         if (k == 0) {  // Best-case graph: Complete graph
//             for (int i = 0; i < v; i++) {
//                 for (int j = 0; j < v; j++) {
//                     graph[i][j] = (i != j) ? 1 : 0;  // All nodes are connected except self-loops
//                 }
//             }
//         }

//         if (k == 1) {  // Worst-case graph: Linear chain
//             for (int i = 0; i < v; i++) {
//                 for (int j = 0; j < v; j++) {
//                     graph[i][j] = 0;  // Initialize all entries to 0
//                 }
//             }
//             for (int i = 0; i < v - 1; i++) {
//                 graph[i][i + 1] = 1;  // Create a chain of connected nodes
//             }
//         }

//         // Reset variables for each graph size
//         isCyclic = 0;
//         bfsCount = 0;
//         count = 0;
//         orderCount = 0;

//         // Initialize visited array for the current graph size
//         for (int j = 0; j < v; j++) {
//             visited[j] = 0;
//         }

//         // Perform BFS traversal starting from node 0
//         bfs(v, 0);
//         bfsCount++;

//         // Check for connectivity by performing BFS from unvisited nodes
//         int start = 1;
//         while (count != v) {
//             if (visited[start] != 1) {
//                 bfs(v, start);
//                 bfsCount++;
//             }
//             start++;
//         }

//         // Output results to appropriate file
//         if (k == 0) {
//             fprintf(f2, "%d\t%d\n", v, orderCount);  // Best-case results
//         } else {
//             fprintf(f1, "%d\t%d\n", v, orderCount);  // Worst-case results
//         }
//     }

//     // Close files
//     fclose(f1);
//     fclose(f2);
// }

// int main() {
//     // Generate plots for best and worst-case scenarios
//     for (int i = 0; i < 2; i++) {
//         plotter(i);
//     }

//     // Notify user that data has been written to files
//     printf("DATA ENTERED INTO THE FILE\n");
// }

#include <stdio.h>
#include <stdlib.h>

int isCycle = 0, components = 0, n, opcount = 0, isTester;

void bfs(int mat[n][n], int *vis, int source)
{
    int queue[n], parent[n];
    int rear = -1, front = -1;
    vis[source] = 1;
    queue[++rear] = source;
    parent[rear] = -1;
    while (rear != front)
    {
        int curr = queue[++front];
        int par = parent[front];
        if (isTester)
            printf("%d ", curr);
        for (int i = 0; i < n; i++)
        {
            opcount++;
            if (i != par && mat[curr][i] && vis[i])
                isCycle = 1;
            if (mat[curr][i] && !vis[i])
            {
                queue[++rear] = i;
                parent[rear] = curr;
                vis[i] = 1;
            }
        }
    }
}

void checkConnectivity(int mat[n][n])
{
    int vis[n], k = 1;
    for (int i = 0; i < n; i++)
    {
        vis[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            components++;
            if (isTester)
                printf("\nConnected component %d: ", k++);
            bfs(mat, &vis[0], i);
        }
    }
}

void tester()
{
    isTester = 1;
    printf("Enter number of vertices :\n");
    scanf("%d", &n);
    int adjMat[n][n];
    printf("Enter the adjacency matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adjMat[i][j]);
        }
    }

    checkConnectivity(adjMat);
    printf("\nNumber of connected components in the graph: %d", components);

    if (isCycle == 1)
    {
        printf("\nCycle exists\n");
    }
    else
    {
        printf("\nCycle doesnot exists\n");
    }
}

void plotter()
{
    isTester = 0;
    FILE *f1 = fopen("bfsadjMat.txt", "w");
    for (int k = 1; k <= 10; k++)
    {
        n = k;
        int adjMat[n][n];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    adjMat[i][j] = 1;
                }
                else
                {
                    adjMat[i][j] = 0;
                }
            }
        }
        opcount = 0;
        checkConnectivity(adjMat);
        fprintf(f1, "%d\t%d\n", n, opcount);
    }
    fclose(f1);
}

void main()
{
    int choice;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice");
    }
}
