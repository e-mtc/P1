#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "LowBoundTSP.h"

// Calculate distance between two bombs
double calculateDistance(mine_s bomb1, mine_s bomb2) {
    return (sqrt(pow(bomb1.x - bomb2.x, 2) + pow(bomb1.y - bomb2.y, 2)) * (bomb1.tw + bomb2.tw));
}

double **structTo2D(mine_s bombs[], int bombAmount) {

}






//Main function to find the solution of TSP using Christofides
void christofides(mine_s bombs[], int bombAmount) {
    //Build the complete graph of distances between bombs
    structTo2D(bombs, bombAmount);

    //Step 1: Find Minimum Spanning Tree
    int parent[MAX];
    //primMST(graph, bombAmount, parent);

    //Step 2: Find nodes with odd degree
    int oddVertices[MAX], oddCount = 0;
    //findOddVertices(bombAmount, parent, oddVertices, &oddCount);

    //Step 3: Perfect Matching
    int matching[MAX][2] = {0};
    //perfectMatching(graph, oddVertices, oddCount, matching);

    //Step 4: Create Eulerian Circuit
    int circuit[MAX * 2], circuitSize = 0;
    //eulerianCircuit(graph, bombAmount, parent, matching, oddCount / 2, circuit, &circuitSize);

    //Step 5: Convert Eulerian to Hamiltonian
    int path[MAX], pathSize = 0;
    //eulerianToHamiltonian(circuit, circuitSize, path, &pathSize, bombAmount, graph);


    //Convert path[] to struct array - Make the changes in sortedArray[]
    //pathToStructArray(path, bombAmount, bombs, sortedArray);
}