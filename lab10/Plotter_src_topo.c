#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct queue {
    int f, r, *arr, cnt;
} QUE;

int graph[MAX][MAX], topo_order[MAX], s[MAX];
int count = 0; // To count the adjacency checks

void indegree(int a[MAX][MAX], int v, int inq[], QUE *temp, int flag[]) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            count++; // Count the adjacency check
            if (a[j][i] == 1)
                inq[i] = inq[i] + 1;
        }
        if (inq[i] == 0) {
            temp->r = (temp->r + 1) % v;
            temp->arr[temp->r] = i;
            temp->cnt = temp->cnt + 1;
            flag[i] = 1;
        }
    }
}

void sourceremove(int a[MAX][MAX], int v, QUE *temp, int inq[], int flag[]) {
    int cnt = 0;
    while (temp->cnt != 0) {
        int source = temp->arr[temp->f];
        temp->f = (temp->f + 1) % v;
        s[cnt] = source;
        temp->cnt = temp->cnt - 1;
        cnt++;
        for (int i = 0; i < v; i++) {
            //count++; // Count the adjacency check
            if (a[source][i] == 1)
                inq[i] = inq[i] - 1;
            if (inq[i] == 0 && flag[i] == 0) {
                temp->r = (temp->r + 1) % v;
                temp->arr[temp->r] = i;
                temp->cnt = temp->cnt + 1;
                flag[i] = 1;
            }
        }
    }

    if (cnt != v) {
        printf("Cycles exist, no topological sorting possible\n");
    } else {
        printf("The topological sorting is\n");
        for (int i = 0; i < cnt; i++) // Corrected to print the valid elements in s
            printf("%c\t", s[i] + 65);
        printf("\n"); // Print new line after the topological order
    }
}

void plotter() {
    FILE *fp; 
    fp=fopen("srm.txt","a");
    srand(time(NULL));
    for (int V = 2; V <= 10; V++) { // Using small values for V for simplicity
        // Randomly create a graph with V vertices and edges
        int E = rand() % (V * (V - 1) / 2);

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                graph[i][j] = 0;
            }
        }

        for (int i = 0; i < E; i++) {
            int u = rand() % V;
            int v = rand() % V;
            if (u != v) {
                graph[u][v] = 1;
            }
        }

        // Initialize the queue and auxiliary arrays for source removal process
        QUE q;
        q.f = 0;
        q.r = -1;
        q.cnt = 0;
        q.arr = (int *)malloc(sizeof(int) * V);

        int *inq = (int *)malloc(sizeof(int) * V);
        int *flag = (int *)malloc(sizeof(int) * V);
        for (int i = 0; i < V; i++) {
            inq[i] = 0;
            flag[i] = 0;
        }

        count = 0;

        indegree(graph, V, inq, &q, flag);
        sourceremove(graph, V, &q, inq, flag);

        fprintf(fp, "%d\t%d\n", V, count);

        free(q.arr);
        free(inq);
        free(flag);
    }
    fclose(fp);
}

int main() {
    plotter();
    return 0;
}