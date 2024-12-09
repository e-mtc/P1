#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LowBoundTSP.h"

// Calculate distance between two bombs
double calculateDistance(mine_s bomb1, mine_s bomb2) {
    return (sqrt(pow(bomb1.x - bomb2.x, 2) + pow(bomb1.y - bomb2.y, 2))) * (bomb1.tw + bomb2.tw);
}

//Finds amount of edges in travelArray to be build
int findEdgeAmount(int bombAmount) {
    int edgeAmount = 0;
    for (int i = bombAmount-1; 0 < i; i--) {
        edgeAmount += i;
    }
    return bombAmount;
}

//Makes the struct array to a travel
void structToStruct(mine_s bombs[], int bombAmount, int edgeAmount, edge_s edgeArray[edgeAmount]) {
    int pathsMade = 0;

    for (int i = 0; i < bombAmount; i++) {
        for (int j = 1+i; j < bombAmount; j++) {
            edgeArray[pathsMade].sourceBomb = bombs[i];
            edgeArray[pathsMade].destinationBomb = bombs[j];
            edgeArray[pathsMade].distanceBetween = calculateDistance(bombs[i], bombs[j]);
            pathsMade++;
        }
    }
}

//Sorts the array
void bubbleSort(int edgeAmount, edge_s edgeArray[edgeAmount]){
    //Temporary values are intialized
    mine_s tempSource, tempDestination;
    double tempDistance;

    //We run through the 2D arrays weight value edgeAmount-1 times since the last postition is assumed correct if the rest is
    for (int i = 0; i < (edgeAmount - 1); ++i){
        //This is run through EdgeAmount-1-i times since the comparison function is unneeded on already assumed correct values(i)
        for (int j = 0; j < edgeAmount - 1 - i; ++j ){
            //A single weight value (j) in the array is compared to the one following it - If larger we swap their places
            if (edgeArray[j].distanceBetween > edgeArray[j+1].distanceBetween){
                tempSource = edgeArray[j+1].sourceBomb;
                tempDestination = edgeArray[j+1].destinationBomb;
                tempDistance = edgeArray[j+1].distanceBetween;


                edgeArray[j+1].sourceBomb = edgeArray[j].sourceBomb;
                edgeArray[j+1].destinationBomb = edgeArray[j].destinationBomb;
                edgeArray[j+1].distanceBetween = edgeArray[j].distanceBetween;


                edgeArray[j].sourceBomb = tempSource;
                edgeArray[j].destinationBomb = tempDestination;
                edgeArray[j].distanceBetween = tempDistance;
            }
        }
    }
}

//Runs the kruskal algorithm to make a minimum spanning tree from a distance-sorted index of travelpoints
void kruskalAlgo(int edgeAmount, int bombAmount, double minCost, edge_s sortedArray[edgeAmount], edge_s MST[bombAmount-1]) {
    int parent[edgeAmount];
    int rank[edgeAmount];
    int j = 0;

    //Function to initialize parent[] and rank[]
    makeSet(parent, rank, edgeAmount);

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < edgeAmount; ++i) {
        int v1 = findParent(parent, sortedArray[i].sourceBomb.mineNumber);
        int v2 = findParent(parent, sortedArray[i].destinationBomb.mineNumber);

        //If the parents are different that means they are in different sets so we union them
        if (v1 != v2) {
            unionSet(v1, v2, parent, rank);
            minCost += sortedArray[i].distanceBetween;
            MST[j].sourceBomb = sortedArray[i].sourceBomb;
            MST[j].destinationBomb = sortedArray[i].destinationBomb;
            MST[j].distanceBetween = sortedArray[i].distanceBetween;
            ++j;
            printf("%d -- %d == %lf\n", MST[j].sourceBomb.mineNumber, MST[j].destinationBomb.mineNumber, MST[j].distanceBetween);
        }
    }

    printf("Minimum Cost Spanning Tree: %lf\n", minCost);
}

//Initialization of arrays for later use
void makeSet(int parent[], int rank[], int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

//Function to find the parent of a node
int findParent(int parent[], int component) {
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

//Function to unite two sets
void unionSet(int u, int v, int parent[], int rank[]) {
    //Finding the parents
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        //Since the rank increases if the ranks of two sets are same
        rank[u]++;
    }
}


//Finds the minimum spanning tree to later be used in christofides to make an efficient route
void makeMST(int edgeAmount, int bombAmount, double minCost, edge_s edgeArray[edgeAmount], edge_s MST[bombAmount-1]) {
    //First we sort the array of possible travelpoints so that we can access the minimum distance-costs
    bubbleSort(edgeAmount, edgeArray);

    //We then apply our sorted array to our kruskal algorithm to get a MST
    kruskalAlgo(edgeAmount, bombAmount, minCost, edgeArray, MST);
}

int *makeSubgraph(int **MST) {






}











//Main function to find the solution of TSP using Christofides
void christofides(mine_s bombs[], int bombAmount) {
    //Finds the amount of edges in edgeArray
    int edgeAmount = findEdgeAmount(bombAmount);

    //Build the complete graph of distances between bombs
    edge_s edgeArray[bombAmount];
    structToStruct(bombs, bombAmount, edgeAmount, edgeArray);

    //Step 1: Find Minimum Spanning Tree
    edge_s MST[bombAmount-1];
    double minCost = 0;
    makeMST(edgeAmount, bombAmount, minCost, edgeArray, MST);



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


    freeArray(edgeArray, edgeAmount);
}