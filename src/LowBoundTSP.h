typedef struct
{
    int x; // x-coordinate of mine
    int y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
    int mineNumber; // Mine number on creation - Used to identify mine in functions
    int edgeAmount; // Edges in created tree MST
} mine_s;

typedef struct // Edge between two vertices moving from vertex 1 to vertex 2
{
    mine_s sourceBomb; // Vertex 1
    mine_s destinationBomb; // Vertex 2
    double distanceBetween; // Distance between Vertex 1 and 2
    int included; // Boolean logic used in creating Eurelian Cycle
} edge_s;

int findEdgeAmount(int bombAmount);
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

void eulerianCircuit(int perfectSize, int MSTSize, int eurelianSize, edge_s MST[], edge_s perfectMatching[], edge_s eurelianCircuit[]);
int nextIsPerfMatch(int perfectSize, edge_s prevEdge, edge_s perfectMatching[perfectSize]);
void addPerfectMatchEdge(int edgesAdded, int perfectSize, int eurelianSize, int *wasAdded, edge_s perfectMatching[perfectSize], edge_s previousEdge, edge_s eurelianCircuit[eurelianSize]);
void addMSTEdge(int edgesAdded, int MSTSize, int eurelianSize, edge_s MST[MSTSize], edge_s previousEdge, edge_s eurelianCircuit[]);


void eulerianShortcut(int shortcutSize, int eurelianSize, double *shortcutCost, edge_s eurelianCircuit[eurelianSize], edge_s eurelianShortcut[shortcutSize]);
void resetIncluded(int eurelianSize, edge_s eurelianCircuit[eurelianSize]);
void findNextPath(int eurelianSize, int shortcutSize, int edgesAdded, edge_s *tempEdge, edge_s eurelianCircuit[eurelianSize], edge_s previousEdge, edge_s eurelianShortcut[shortcutSize]);
int returningToUsedVertex (int shortcutSize, int edgesAdded, edge_s cosideredVertex, edge_s eurelianShortcut[shortcutSize]);
void createShortcut(int eurelianSize, int edgesAdded, edge_s *newEdge, edge_s eurelianCircuit[eurelianSize], edge_s consideredEdge);
void rearrageEulerian(int connectingIndex, int edgesAdded, int eurelianSize, edge_s eurelianCircuit[eurelianSize]);



void christofides(int bombAmount, mine_s bombs[bombAmount], mine_s sortedBombs[bombAmount]);
    void makeMST(int edgeAmount, int bombAmount, double *minCost, edge_s edgeArray[edgeAmount], edge_s MST[bombAmount-1], mine_s bombs[bombAmount]);