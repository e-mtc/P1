#define VALUES 3
typedef struct
{
    int x; // x-coordinate of mine
    int y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
    int mineNumber;
    int edgeAmount;
} mine_s;

typedef struct {
    mine_s sourceBomb;
    mine_s destinationBomb;
    double distanceBetween;
} edge_s;

int findEdgeAmount(int bombAmount);
double **make2DArray(int rows, int columns);
void structToStruct(mine_s bombs[], int bombAmount, int , edge_s edgeArray[]);
double calculateDistance(mine_s bomb1, mine_s bomb2);
void bubbleSort(int edgeAmount, edge_s edgeArray[edgeAmount]);

void kruskalAlgo(int edgeAmount, int bombAmount, double *minCost, edge_s edgeArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]);
    void makeSet(int parent[], int rank[], int n);
    int findParent(int parent[], int component);
    void unionSet(int u, int v, int parent[], int rank[]);

void findOddVertices(int bombAmount, int oddCount, mine_s bombs[bombAmount], mine_s oddVertices[oddCount]);
int findOddAmount(int bombAmount, mine_s bombs[bombAmount]);

void perfectMatching(int oddCount, mine_s oddVertices[oddCount], edge_s perfectMatch[oddCount/2]);
int alreadyIncludedInPM(mine_s bomb, int perfectSize, edge_s perfectMatchArray[perfectSize]);


void christofides(int bombAmount, mine_s bombs[bombAmount], mine_s sortedBombs[bombAmount]);
    void makeMST(int edgeAmount, int bombAmount, double *minCost, edge_s edgeArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]);