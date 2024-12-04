#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "LowBoundTSP.h"

// Calculate distance between two bombs
int calculateDistance(mine_s bomb1, mine_s bomb2) {
    return (sqrt(pow(bomb1.x - bomb2.x, 2) + pow(bomb1.y - bomb2.y, 2)) * (bomb1.tw + bomb2.tw));
}

int findMinKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, minIndex;

    for (int i = 0; i < n; i++) {
        if (!mstSet[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Generate minimum spanning tree
void primMST(int graph[MAX][MAX], int n, int parent[]) {
    int key[MAX], mstSet[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int i = 0; i < n; i++) {
            if (graph[u][i] && !mstSet[i] && graph[u][i] < key[i]) {
                parent[i] = u;
                key[i] = graph[u][i];
            }
        }
    }
}

// Find odd vertices in MST
void findOddVertices(int n, int parent[], int oddVertices[], int *oddCount) {
    int degree[MAX] = {0};
    for (int i = 1; i < n; i++) {
        degree[i]++;
        degree[parent[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 == 1) {
            oddVertices[(*oddCount)++] = i;
        }
    }
}

// Function to realize minimum perfect pairing
void perfectMatching(int graph[MAX][MAX], int oddVertices[], int oddCount, int matching[MAX][2]) {
    int used[MAX] = {0}, matchIndex = 0;

    for (int i = 0; i < oddCount; i++) {
        if (!used[oddVertices[i]]) {
            int minEdge = INT_MAX, minVertex = -1;
            for (int j = i + 1; j < oddCount; j++) {
                if (!used[oddVertices[j]] && graph[oddVertices[i]][oddVertices[j]] < minEdge) {
                    minEdge = graph[oddVertices[i]][oddVertices[j]];
                    minVertex = j;
                }
            }
            if (minVertex != -1) {
                used[oddVertices[i]] = used[oddVertices[minVertex]] = 1;
                matching[matchIndex][0] = oddVertices[i];
                matching[matchIndex][1] = oddVertices[minVertex];
                matchIndex++;
            }
        }
    }
}

// Function to find the Euler circuit
void eulerianCircuit(int graph[MAX][MAX], int n, int parent[], int matching[MAX][2], int matchCount, int circuit[], int *circuitSize) {
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Adding MST edges to the circuit
    for (int i = 1; i < n; i++) {
        if (!visited[parent[i]]) {
            circuit[(*circuitSize)++] = parent[i];
            visited[parent[i]] = 1;
        }
    }

    // Adding perfect pairing edges to the circuit
    for (int i = 0; i < matchCount; i++) {
        if (!visited[matching[i][0]] || !visited[matching[i][1]]) {
            circuit[(*circuitSize)++] = matching[i][0];
            circuit[(*circuitSize)++] = matching[i][1];
            visited[matching[i][0]] = visited[matching[i][1]] = 1;
        }
    }
}

// Function to convert the Eulerian circuit into a Hamiltonian path
void eulerianToHamiltonian(int circuit[], int circuitSize, int path[], int *pathSize, int n, int graph[MAX][MAX]) {
    int visited[MAX] = {0};

    for (int i = 0; i < circuitSize; i++) {
        if (!visited[circuit[i]]) {
            visited[circuit[i]] = 1;
            path[(*pathSize)++] = circuit[i];
        }
    }

    // Check if all vertices have been visited
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // Find the position to insert the missing vertex
            int pos = 0;
            while (pos < *pathSize - 1 && graph[path[pos]][i] + graph[i][path[pos + 1]] <= graph[path[pos]][path[pos + 1]]) {
                pos++;
            }
            // Shift vertices right to insert missing vertex
            for (int j = *pathSize; j > pos; j--) {
                path[j] = path[j - 1];
            }
            path[pos] = i;
            (*pathSize)++;
            visited[i] = 1;
        }
    }
}

// Function to calculate the factorial of a number
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

//Function to take sorted array of bombs and turn into struct array for later use in printing
void pathToStructArray(int *path, int bombAmount, mine_s *bombs, mine_s sortedArray[bombAmount]) {
    for (int i = 0; i < bombAmount; i++) {
        for (int j = 0; j < bombAmount; j++) {
            if (path[i] == bombs[j].minenumber) {
                sortedArray[i].x = bombs[j].x;
                sortedArray[i].y = bombs[j].y;
                sortedArray[i].tw = bombs[j].tw;
                sortedArray[i].minenumber = i;
                break;
            }
        }
    }
}

//Main function to find the solution of TSP using Christofides
void christofides(mine_s bombs[], int bombAmount, mine_s sortedArray[bombAmount]) {
    //Build the complete graph of distances between bombs
    int graph[MAX][MAX];
    for (int i = 0; i < bombAmount; i++) {
        for (int j = 0; j < bombAmount; j++) {
            graph[i][j] = calculateDistance(bombs[i], bombs[j]);
        }
    }

    //Step 1: Find Minimum Spanning Tree
    int parent[MAX];
    primMST(graph, bombAmount, parent);

    //Step 2: Find nodes with odd degree
    int oddVertices[MAX], oddCount = 0;
    findOddVertices(bombAmount, parent, oddVertices, &oddCount);

    //Step 3: Perfect Matching
    int matching[MAX][2] = {0};
    perfectMatching(graph, oddVertices, oddCount, matching);

    //Step 4: Create Eulerian Circuit
    int circuit[MAX * 2], circuitSize = 0;
    eulerianCircuit(graph, bombAmount, parent, matching, oddCount / 2, circuit, &circuitSize);

    //Step 5: Convert Eulerian to Hamiltonian
    int path[MAX], pathSize = 0;
    eulerianToHamiltonian(circuit, circuitSize, path, &pathSize, bombAmount, graph);


    //Convert path[] to struct array - Make the changes in sortedArray[]
    pathToStructArray(path, bombAmount, bombs, sortedArray);
}