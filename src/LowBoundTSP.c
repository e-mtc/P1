#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "LowBoundTSP.h"

// Calculate distance between two bombs
double calculateDistance(mine_s bomb1, mine_s bomb2) {
    return (sqrt(pow(bomb1.x - bomb2.x, 2) + pow(bomb1.y - bomb2.y, 2))) * (bomb1.tw + bomb2.tw);
}

int findEdgeAmount(int bombAmount) {
    int edgeAmount = 0;
    for (int i = bombAmount-1; 0 < i; i--) {
        edgeAmount += i;
    }
    return bombAmount;
}

double **structTo2D(mine_s bombs[], int bombAmount, int edgeAmount) {
    double **edgeArray = make2DArray(edgeAmount, 3);

    int pathsMade = 0;
    for (int i = 0; i < bombAmount; i++) {
        for (int j = 1+i; j < bombAmount; j++) {
            edgeArray[pathsMade][0] = i;
            edgeArray[pathsMade][1] = j;
            edgeArray[pathsMade][2] = calculateDistance(bombs[i], bombs[j]);
            pathsMade++;
        }
    }

    return edgeArray;
}

//Sorts the array
void bubbleSort(int paths, int a[paths][VALUES]){
    //Temporary values are intialized
    int tempSource, tempDestination, tempWeight;

    //We run through the 2D arrays weight value paths-1 times since the last postition is assumed correct if the rest is
    for (int i = 0; i < (paths - 1); ++i){
        //This is run through paths-1-i times since the comparison function is unneeded on already assumed correct values(i)
        for (int j = 0; j < paths - 1 - i; ++j ){
            //A single weight value (j) in the array is compared to the one following it - If larger we swap their places
            if (a[j][2] > a[j+1][2]){
                tempSource = a[j+1][0];
                tempDestination = a[j+1][1];
                tempWeight = a[j+1][2];


                a[j+1][0] = a[j][0];
                a[j+1][1] = a[j][1];
                a[j+1][2] = a[j][2];


                a[j][0] = tempSource;
                a[j][1] = tempDestination;
                a[j][2] = tempWeight;
            }
        }
    }
}

//Runs the kruskal algorithm to make a minimum spanning tree from a distance-sorted index of travelpoints
int **kruskalAlgo(int paths, int sortedArray[paths][VALUES]) {
    int parent[paths];
    int rank[paths];

    int **MST = make2DArray(paths-1, 2);
    int j = 0;

    //Function to initialize parent[] and rank[]
    makeSet(parent, rank, paths);

    //To store the minimum cost
    int minCost = 0;

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < paths; ++i) {
        int v1 = findParent(parent, sortedArray[i][0]);
        int v2 = findParent(parent, sortedArray[i][1]);
        int wt = sortedArray[i][2];

        //If the parents are different that means they are in different sets so we union them
        if (v1 != v2) {
            unionSet(v1, v2, parent, rank);
            minCost += wt;
            MST[j][0] = sortedArray[i][0];
            MST[j][1] = sortedArray[i][1];
            ++j;
            printf("%d -- %d == %d\n", sortedArray[i][0], sortedArray[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
    if(MST == NULL) {
        return EXIT_FAILURE;
    } else {
        return MST;
    }
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
double **makeMST(int paths, int travelArray[paths][VALUES]) {
    //First we sort the array of possible travelpoints so that we can access the minimum distance-costs
    bubbleSort(paths, travelArray);

    //We then apply our sorted array to our kruskal algorithm to get a MST
    int **MST = kruskalAlgo(paths, travelArray);

    if (MST == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return MST;
    }
}

int *makeSubgraph(int **MST) {






}




//Mallocs space for a 2D array to be used later
double **make2DArray(int rows, int columns) {
    double **result = malloc(rows * sizeof(double*));

    for(int i = 0; i < rows; i++) {
        result[i] = malloc(columns*sizeof(double));
    }

    return result;
}

void freeArray(double **array, double rows) {
    for (int i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);
}








//Main function to find the solution of TSP using Christofides
void christofides(mine_s bombs[], int bombAmount) {
    //Finds the amount of edges in edgeArray
    int edgeAmount = findEdgeAmount(bombAmount);

    //Build the complete graph of distances between bombs
    double **edgeArray = structTo2D(bombs, bombAmount, edgeAmount);

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


    freeArray(edgeArray, edgeAmount);
}