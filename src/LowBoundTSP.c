#include "LowBoundTSP.h"
#include <stdio.h>

//Sorts the array
void bubbleSort(int paths, int a[paths][VALUES]){
    //Temporary values are intialized
    int tempSource, tempDestination, tempWeight;

    //We run through the 2D arrays weight value paths-1 times since the last postition is assumed correct if the rest is
    for (int i = 0; i < (paths - 1); ++i){
        //This is run through paths-1-i times since the comparison function is unneeded on already assumed correct values(i)
        for (int j = 0; j < paths - 1 - i; ++j ){
            //A single weight value (j) in the array is compared to the one following it - If larger we swap their places
            if (a[j][WEIGHT] > a[j+1][WEIGHT]){
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
void kruskalAlgo(int paths, int sortedArray[paths][VALUES]) {
    int parent[paths];
    int rank[paths];

    //Function to initialize parent[] and rank[]
    makeSet(parent, rank, paths);

    //To store the minimun cost
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
            printf("%d -- %d == %d\n", sortedArray[i][0],
                   sortedArray[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

//Initialization of arrays for later use
void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

//Function to find the parent of a node
int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component]
           = findParent(parent, parent[component]);
}

//Function to unite two sets
void unionSet(int u, int v, int parent[], int rank[])
{
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


//Finds the minimum spanning tree to later be used in christofides to make an effecient route
void makeMST(int paths, int travelArray[paths][VALUES]){
    //First we sort the array of possible travelpoints so that we can access the minimum distance-costs
    bubbleSort(paths, travelArray);

    //We then apply our sorted array to our kruskal algorithm to get a MST
    kruskalAlgo(paths, travelArray);
}




void christofidesTSP(int paths, int travelArray[][VALUES]){

    //First step is creating a minimum spanning tree
    makeMST(paths, travelArray);

    //Second step is creating a subgraph of odd-degree vertices in the MST
    makeSubgraph(travelArray);

    //Third step is calculating 'M?' - a minimum-weight perfect matching on the subgraph
    makeMinimumW(subgraph);

    //Create new path(Graph) 'Temporary?' by combining the edges/paths in M and the MST
    makePathTemp(subgraph, travelArray);

    //Create an euler tour around the new path X -- 'E?'
    createE(pathTemp);

    //Remove twice visited paths in E and replace while still maintaining a cycle of paths
    makeTSP(E);
}
