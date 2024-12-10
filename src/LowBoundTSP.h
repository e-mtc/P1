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
    int included;
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

void perfectMatching(int oddCount, int perfectSize, mine_s oddVertices[oddCount], edge_s perfectMatch[perfectSize]);
int alreadyIncludedInPM(mine_s bomb, int perfectSize, edge_s perfectMatchArray[perfectSize]);

void eulerianCircuit(int bombAmount, int perfectSize, int MSTSize, int eurelianSize, edge_s MST[MSTSize], edge_s perfectMatching[perfectSize], edge_s eurelianCircuit[eurelianSize]);
int checkIfPreviouslyIncluded(int eurelianSize, int edgesAdded, edge_s eurelianCircuit[eurelianSize], edge_s testCase);
void mergePerfMatchMST(int MSTSize, int perfectSize, int eurelianSize, edge_s MST[MSTSize], edge_s perfectMatching[perfectSize], edge_s tempEdges[eurelianSize]);
int nextIsPerfMatch(int perfectSize, edge_s prevEdge, edge_s perfectMatching[perfectSize]);
void addPerfectMatchEdge(int edgesAdded, int perfectSize, edge_s perfectMatching[perfectSize], edge_s eurelianCircuit[]);


void christofides(int bombAmount, mine_s bombs[bombAmount], mine_s sortedBombs[bombAmount]);
    void makeMST(int edgeAmount, int bombAmount, double *minCost, edge_s edgeArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]);