#include <math.h>
#include "LowBoundTSP.h"
#include <stdbool.h>

// Calculate distance between two bombs
double calculateDistance(mine_s bomb1, mine_s bomb2) {
    mine_s temp; // temp variable for swapping mine values
    // swap values to avoid negative numbers
    if (bomb1.x < bomb2.x) {
        temp.x = bomb1.x;
        bomb1.x = bomb2.x;
        bomb2.x = temp.x;
    }
    if (bomb1.y < bomb2.y) {
        temp.y = bomb1.y;
        bomb1.y = bomb2.y;
        bomb2.y = temp.y;
    }
    // calculate distance between two mines and return
    return sqrt(pow(bomb1.x - bomb2.x, 2) + pow(bomb1.y - bomb2.y, 2)) * (bomb1.tw + bomb2.tw);
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
            edgeArray[pathsMade].included = false;
            pathsMade++;
        }
    }
}

//Sorts the array
void bubbleSort(int edgeAmount, edge_s edgeArray[edgeAmount]){
    //Temporary values are initialized
    mine_s tempSource, tempDestination;
    double tempDistance;

    //We run through the 2D arrays weight value edgeAmount-1 times since the last position is assumed correct if the rest is
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

//Runs the kruskal algorithm to make a minimum spanning tree from a distance-sorted index of travel points
void kruskalAlgo(int edgeAmount, int bombAmount, double *minCost, edge_s sortedArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]) {
    int parent[edgeAmount];
    int rank[edgeAmount];
    int j = 0;

    //Function to initialize parent[] and rank[]
    makeSet(parent, rank, edgeAmount);

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
            MST[j].included = false;
            ++j;
        }
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

//Finds the minimum spanning tree to later be used in Christofides to make an efficient route
void makeMST(int edgeAmount, int bombAmount, double *minCost, edge_s edgeArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]) {
    //First we sort the array of possible travel points so that we can access the minimum distance-costs
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
            if (!alreadyIncludedInPM(oddEdgeArray[j].sourceBomb, perfectSize, perfectMatch) && !alreadyIncludedInPM(oddEdgeArray[j].destinationBomb, perfectSize, perfectMatch)) {
                perfectMatch[addedCount] = oddEdgeArray[j];
                addedCount++;
                break;
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

//Makes an eulerian circuit from the precalculated MST and perfectMatching graphs
void eulerianCircuit(int perfectSize, int MSTSize, int eurelianSize, edge_s MST[], edge_s perfectMatching[], edge_s eurelianCircuit[]) {
    int eAdded = 0;
    int wasUsed;

    MST[0].included = true;
    eurelianCircuit[eAdded] = MST[0];
    eAdded++;

    for (int i = 1; i < eurelianSize; i++) {
        wasUsed = false;
        if (nextIsPerfMatch(perfectSize, eurelianCircuit[eAdded-1], perfectMatching)) {
            addPerfectMatchEdge(eAdded, perfectSize, eurelianSize, &wasUsed, perfectMatching, eurelianCircuit[eAdded-1], eurelianCircuit);
        }

        if (!wasUsed) {
            addMSTEdge(eAdded, MSTSize, eurelianSize, MST, eurelianCircuit[eAdded-1], eurelianCircuit);
        }

        //Checks if we are ending a cycle
        if (eurelianCircuit[eAdded].sourceBomb.mineNumber != eurelianCircuit[eAdded-1].destinationBomb.mineNumber) {
            for (int j = 0; j < perfectSize; j++) {
                for (int k = 0; k < eAdded-1; k++)
                {
                    if ((eurelianCircuit[k].destinationBomb.mineNumber == perfectMatching[j].sourceBomb.mineNumber && perfectMatching[j].included == false) ||
                        (eurelianCircuit[k].destinationBomb.mineNumber == perfectMatching[j].destinationBomb.mineNumber && perfectMatching[j].included == false)) {

                        if (eurelianCircuit[k].destinationBomb.mineNumber == perfectMatching[j].destinationBomb.mineNumber) {
                            mine_s tempMine;

                            tempMine = perfectMatching[j].destinationBomb;
                            perfectMatching[j].destinationBomb = perfectMatching[j].sourceBomb;
                            perfectMatching[j].sourceBomb = tempMine;
                        }

                        rearrangeEulerian(k, eAdded, eurelianSize, eurelianCircuit);

                        perfectMatching[j].included = true;
                        eurelianCircuit[eAdded] = perfectMatching[j];
                        wasUsed = true;
                        break;
                    }
                }
                if (wasUsed == true) {
                    break;
                }
            }

            if (!wasUsed) {
                for (int j = 0; j < MSTSize; j++) {
                    for (int k = 0; k < eAdded; k++)
                    {
                        if ((eurelianCircuit[k].destinationBomb.mineNumber == MST[j].sourceBomb.mineNumber && MST[j].included == false) ||
                            (eurelianCircuit[k].destinationBomb.mineNumber == MST[j].destinationBomb.mineNumber && MST[j].included == false)) {

                            if (eurelianCircuit[k].destinationBomb.mineNumber == MST[j].destinationBomb.mineNumber) {
                                mine_s tempMine;


                                tempMine = MST[j].destinationBomb;
                                MST[j].destinationBomb = MST[j].sourceBomb;
                                MST[j].sourceBomb = tempMine;
                            }

                            rearrangeEulerian(k, eAdded, eurelianSize, eurelianCircuit);

                            MST[j].included = true;
                            eurelianCircuit[eAdded] = MST[j];
                            wasUsed = true;
                            break;
                        }
                    }
                    if (wasUsed == true) {
                        break;
                    }
                }
            }
        }
        eAdded++;
    }
}

//Rearranges the eulerian tour if there is a cycle detected, so that it is still in order
void rearrangeEulerian(int connectingIndex, int edgesAdded, int eurelianSize, edge_s eurelianCircuit[eurelianSize]) {
    edge_s tempEdge;

    for (int i = connectingIndex; i < edgesAdded-1; i++) {
        tempEdge = eurelianCircuit[edgesAdded-1];

        for (int j = edgesAdded; 0 < j; j--) {

            eurelianCircuit[j] = eurelianCircuit[j-1];
        }

        eurelianCircuit[0] = tempEdge;
    }
}

//Figures out if the current destination point is included in the perfect match subgraph
int nextIsPerfMatch(int perfectSize, edge_s prevEdge, edge_s perfectMatching[perfectSize]) {
    for (int i = 0; i < perfectSize; i++) {
        if (prevEdge.destinationBomb.mineNumber == perfectMatching[i].sourceBomb.mineNumber ||
            prevEdge.destinationBomb.mineNumber == perfectMatching[i].destinationBomb.mineNumber) {
            return true;
        }
    }
    return false;
}

//Adds an edge to Eurelian Circuit if the next is one located in perfectMatching[] and also is not already in the circuit
void addPerfectMatchEdge(int edgesAdded, int perfectSize, int eurelianSize, int *wasAdded, edge_s perfectMatching[perfectSize], edge_s previousEdge, edge_s eurelianCircuit[eurelianSize]) {
    mine_s tempMine;

    for (int i = 0; i < perfectSize; i++) {
        //Checks if an individual edge is connected and also not already included
        if ((perfectMatching[i].sourceBomb.mineNumber == previousEdge.destinationBomb.mineNumber && perfectMatching[i].included == false) ||
            (perfectMatching[i].destinationBomb.mineNumber == previousEdge.destinationBomb.mineNumber && perfectMatching[i].included == false)) {

            //Swamps mine location so source matches previous destination
            if (perfectMatching[i].destinationBomb.mineNumber == previousEdge.destinationBomb.mineNumber) {
                tempMine = perfectMatching[i].destinationBomb;
                perfectMatching[i].destinationBomb = perfectMatching[i].sourceBomb;
                perfectMatching[i].sourceBomb = tempMine;
            }
            perfectMatching[i].included = true;
            eurelianCircuit[edgesAdded] = perfectMatching[i];
            *wasAdded = true;
            break;
        }
    }
}

//Adds an edge to Eurelian Circuit if the next is one located in MST[] and also is not already in the circuit
void addMSTEdge(int edgesAdded, int MSTSize, int eurelianSize, edge_s MST[MSTSize], edge_s previousEdge, edge_s eurelianCircuit[eurelianSize]) {
    mine_s tempMine;

    for (int i = 0; i < MSTSize; i++) {
        //Checks if an individual edge is connected and also not already included
        if ((MST[i].sourceBomb.mineNumber == previousEdge.destinationBomb.mineNumber && MST[i].included == false) ||
            (MST[i].destinationBomb.mineNumber == previousEdge.destinationBomb.mineNumber && MST[i].included == false)) {

            //Swamps mine location so source matches previous destination
            if (MST[i].destinationBomb.mineNumber == previousEdge.destinationBomb.mineNumber) {
                tempMine = MST[i].destinationBomb;
                MST[i].destinationBomb = MST[i].sourceBomb;
                MST[i].sourceBomb = tempMine;
            }
            MST[i].included = true;
            eurelianCircuit[edgesAdded] = MST[i];
            break;
        }
    }
}

//Shortcuts the Eurelian Cycle
void eulerianShortcut(int shortcutSize, int eurelianSize, double *shortcutCost, edge_s eurelianCircuit[eurelianSize], edge_s eurelianShortcut[shortcutSize]) {
    edge_s tempEdge;
    int eAdded = 0;

    resetIncluded(eurelianSize, eurelianCircuit);

    eurelianCircuit[0].included = true;
    eurelianShortcut[eAdded] = eurelianCircuit[0];
    *shortcutCost += eurelianCircuit[eAdded].distanceBetween;
    eAdded++;

    for (int i = 1; i < shortcutSize; i++){
        //Finds next edge for the shortcut circuit
        findNextPath(eurelianSize, shortcutSize, eAdded, &tempEdge, eurelianCircuit, eurelianShortcut[eAdded-1], eurelianShortcut);
        //Adds edge to circuit
        eurelianShortcut[eAdded] = tempEdge;
        *shortcutCost += eurelianShortcut[eAdded].distanceBetween;
        eAdded++;
    }
}

//Resets 'included'
void resetIncluded(int eurelianSize, edge_s eurelianCircuit[eurelianSize]) {
    for (int i = 0; i < eurelianSize; i++) {
        eurelianCircuit[i].included = false;
    }
}

//Finds next edge for the shortcut circuit
void findNextPath(int eurelianSize, int shortcutSize, int edgesAdded, edge_s *tempEdge, edge_s eurelianCircuit[eurelianSize], edge_s previousEdge, edge_s eurelianShortcut[shortcutSize]) {

    for (int i = 0; i < eurelianSize; i++) {
        //Makes sure we are considering the right edge for next addition
        if (eurelianCircuit[i].sourceBomb.mineNumber == previousEdge.destinationBomb.mineNumber && eurelianCircuit[i].included == false) {
            eurelianCircuit[i].included = true;
            //Checks if we are returning to an already visited vertices if using the found edge
            if (returningToUsedVertex(shortcutSize, edgesAdded, eurelianCircuit[i], eurelianShortcut)) {

                createShortcut(eurelianSize, edgesAdded, tempEdge, eurelianCircuit, eurelianCircuit[i]);
                break;
            }
            *tempEdge = eurelianCircuit[i];
            break;
        }
    }
}

//Checks if we are returning to an already used vertex
int returningToUsedVertex (int shortcutSize, int edgesAdded, edge_s consideredVertex, edge_s eurelianShortcut[shortcutSize]) {
    for (int i = 0; i < edgesAdded; i++) {
        if ((consideredVertex.destinationBomb.mineNumber == eurelianShortcut[i].destinationBomb.mineNumber) || (consideredVertex.destinationBomb.mineNumber == eurelianShortcut[0].sourceBomb.mineNumber) && (edgesAdded != shortcutSize-1)) {
            return true;
        }
    }
    return false;
}

//Creates a shortcut in the eurelian circuit so that the edges do not visit same vertices twice
void createShortcut(int eurelianSize, int edgesAdded, edge_s *newEdge, edge_s eurelianCircuit[eurelianSize], edge_s consideredEdge) {
        for (int i = 0; i < eurelianSize; i++) {
            if (consideredEdge.destinationBomb.mineNumber == eurelianCircuit[i].sourceBomb.mineNumber && eurelianCircuit[i].included == false) {
                newEdge->sourceBomb = consideredEdge.sourceBomb;
                newEdge->destinationBomb = eurelianCircuit[i].destinationBomb;
                newEdge->distanceBetween = calculateDistance(newEdge->sourceBomb, newEdge->destinationBomb);
                newEdge->included = true;
                break;
            }
        }
}

//Convert tsp solution from edge_s array to mine_s array so that it can be printed
void tspToMineArray(int bombAmount, edge_s eurelianShortcut[bombAmount], mine_s sortedBombs[bombAmount]) {
    for (int i = 0; i < bombAmount; i++) {
        sortedBombs[i] = eurelianShortcut[i].sourceBomb;
    }
}

// Find the index of the desired start point(mine) in the array containing the calculated path (tsp solution)
int findDesiredStartIndex(int bombAmount, mine_s sortedBombs[bombAmount])
{
    int startIndex = 0;

    for (int i = 0; i < bombAmount; i++) {
        if (sortedBombs[i].mineNumber == 0) {
            startIndex = i;
            break;
        }
    }

    return startIndex;
}

// Rearranging mine_s struct array such that the start point is the first mine
void rearrangeArray(int bombAmount, mine_s sortedBombs[bombAmount])
{
    int startIndex = findDesiredStartIndex(bombAmount, sortedBombs);

    mine_s tempMine;

    for (int i = startIndex; i > 0; i--)
    {
        tempMine = sortedBombs[0];

        for (int j = 0; j < bombAmount-1; j++)
        {
            sortedBombs[j] = sortedBombs[j+1];
        }
        sortedBombs[bombAmount-1] = tempMine;
    }
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
    eulerianCircuit(perfectSize, bombAmount-1, eurelianSize, MST, perfectMatch, eurelianC);

    //Step 5: Shortcut edges that repeat to already visited vertices
    edge_s eurelianShortcut[bombAmount];
    double shortcutCost = 0;
    eulerianShortcut(bombAmount, eurelianSize, &shortcutCost, eurelianC, eurelianShortcut);

    //Convert eurelianShortcut[] to mine_s struct array so that it can be used for printing - Make the changes in sortedArray[]
    tspToMineArray(bombAmount, eurelianShortcut, sortedBombs);

    // Rearranging mine_s struct array such that the start point is the first mine
    rearrangeArray(bombAmount, sortedBombs);
}