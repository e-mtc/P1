#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LowBoundTSP.h"

#include <stdbool.h>

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
    return edgeAmount;
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
void kruskalAlgo(int edgeAmount, int bombAmount, double *minCost, edge_s sortedArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]) {
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
            *minCost += sortedArray[i].distanceBetween;

            //We note that these vertexes now have an edge in the MST for later use
            bombs[sortedArray[i].sourceBomb.mineNumber].edgeAmount++;
            bombs[sortedArray[i].destinationBomb.mineNumber].edgeAmount++;

            //Then save the destination in our MST
            MST[j].sourceBomb = sortedArray[i].sourceBomb;
            MST[j].destinationBomb = sortedArray[i].destinationBomb;
            MST[j].distanceBetween = sortedArray[i].distanceBetween;
            printf("%d -- %d == %lf\n", MST[j].sourceBomb.mineNumber, MST[j].destinationBomb.mineNumber, MST[j].distanceBetween);
            ++j;
        }
    }

    printf("Minimum Cost Spanning Tree: %lf\n", *minCost);
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
void makeMST(int edgeAmount, int bombAmount, double *minCost, edge_s edgeArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]) {
    //First we sort the array of possible travelpoints so that we can access the minimum distance-costs
    bubbleSort(edgeAmount, edgeArray);

    //We then apply our sorted array to our kruskal algorithm to get a MST
    kruskalAlgo(edgeAmount, bombAmount, minCost, edgeArray, MST, bombs);
}

//Identifies the odd vertices and saves them for later use
void findOddVertices(int bombAmount, int oddCount, mine_s bombs[bombAmount], mine_s oddVertices[oddCount]) {
    int oddsAdded = 0;

    for(int i = 0; i < bombAmount; i++) {
            if (bombs[i].edgeAmount % 2 == 1){
                oddVertices[oddsAdded].x = bombs[i].x;
                oddVertices[oddsAdded].y = bombs[i].y;
                oddVertices[oddsAdded].tw = bombs[i].tw;
                oddVertices[oddsAdded].mineNumber = bombs[i].mineNumber;
                oddVertices[oddsAdded].edgeAmount = bombs[i].edgeAmount;
                oddsAdded++;
        }
    }
}

//Counts the amount of odd vertices
int findOddAmount(int bombAmount, mine_s bombs[bombAmount]) {
    int oddCount = 0;

    for(int i = 0; i < bombAmount; i++) {
        if (bombs[i].edgeAmount % 2 == 1) {
            oddCount++;
        }
    }

    return oddCount;
}

//Finds perfect matching using greedy algorithm
void perfectMatching(int oddCount, int perfectSize, mine_s oddVertices[oddCount], edge_s perfectMatch[perfectSize]) {
    int addedCount = 0;
    int edgeAmount = findEdgeAmount(oddCount);

    edge_s oddEdgeArray[edgeAmount];
    structToStruct(oddVertices, oddCount, edgeAmount, oddEdgeArray);

    bubbleSort(edgeAmount, oddEdgeArray);

    for (int i = 0; i < oddCount/2; i++) {
        for (int j = 0+i; j < edgeAmount; j++) {
            if (!alreadyIncludedInPM(oddEdgeArray[j].sourceBomb, perfectSize, perfectMatch) && !alreadyIncludedInPM(oddEdgeArray[j].sourceBomb, perfectSize, perfectMatch)) {
                perfectMatch[addedCount] = oddEdgeArray[j];
                addedCount++;
            }
        }
    }
}

//Checks if the current value the greedy algorithm is looking at is already included
int alreadyIncludedInPM(mine_s bomb, int perfectSize, edge_s perfectMatchArray[perfectSize]) {

    for (int i = 0; i < perfectSize; i++) {
        if (bomb.mineNumber == perfectMatchArray[i].sourceBomb.mineNumber || bomb.mineNumber == perfectMatchArray[i].destinationBomb.mineNumber) {
            return true;
        }
    }
    return false;
}


void eulerianCircuit(int bombAmount, int perfectSize, int MSTSize, int eurelianSize, edge_s MST[MSTSize], edge_s perfectMatching[perfectSize], edge_s eurelianCircuit[eurelianSize]) {
    int eAdded = 0;

    eurelianCircuit[eAdded] = MST[0];
    eAdded++;

    for (int i = 0; i < eurelianSize; i++) {
        if (!checkIfPreviouslyIncluded(eurelianSize, eAdded, eurelianCircuit, ??)) {//Find ud af hvilken vi kigger på først
            if (!checkIfHasPerfectmatching) {
                addcorrectone;
            }
            addcorrectone;
        }
    }
}

int checkIfPreviouslyIncluded(int eurelianSize, int edgesAdded, edge_s eurelianCircuit[eurelianSize], edge_s testCase) {
    for (int i = 0; i < edgesAdded; i++) {
        if (testCase.sourceBomb.mineNumber == eurelianCircuit[i].sourceBomb.mineNumber && testCase.destinationBomb.mineNumber == eurelianCircuit[i].destinationBomb.mineNumber ||
            testCase.sourceBomb.mineNumber == eurelianCircuit[i].destinationBomb.mineNumber && testCase.destinationBomb.mineNumber == eurelianCircuit[i].sourceBomb.mineNumber) {
            return true;
        }
    }
    return true;
}





//Main function to find the solution of TSP using Christofides
void christofides(int bombAmount, mine_s bombs[bombAmount], mine_s sortedBombs[bombAmount]) {
    //Finds the amount of edges in edgeArray
    int edgeAmount = findEdgeAmount(bombAmount);

    //Build the complete graph of distances between bombs
    edge_s edgeArray[edgeAmount];
    structToStruct(bombs, bombAmount, edgeAmount, edgeArray);

    //Step 1: Find Minimum Spanning Tree
    edge_s MST[bombAmount-1];
    double minCost = 0;
    makeMST(edgeAmount, bombAmount, &minCost, edgeArray, MST, bombs);


    //Step 2: Find nodes with odd degree (Amount of edges)
    int oddCount = findOddAmount(bombAmount, bombs);
    mine_s oddVertices[oddCount];
    findOddVertices(bombAmount, oddCount, bombs, oddVertices);


    //Step 3: Perfect Matching
    int perfectSize = oddCount/2;
    edge_s perfectMatch[perfectSize];
    perfectMatching(oddCount, perfectSize, oddVertices, perfectMatch);

    //Step 4: Create Eurelian Circuit
    int eurelianSize = perfectSize+bombAmount-1;
    edge_s eurelianC[eurelianSize];
    eulerianCircuit(bombAmount, perfectSize, bombAmount-1, eurelianSize, MST, perfectMatch, eurelianC);

    //Step 5: Convert Eulerian to Hamiltonian
    //int path[MAX], pathSize = 0;
    //eulerianToHamiltonian(circuit, circuitSize, path, &pathSize, bombAmount, graph);


    //Convert path[] to struct array - Make the changes in sortedArray[]
    //pathToStructArray(path, bombAmount, bombs, sortedArray);


    //Free allocated memory
    free(oddVertices);
}