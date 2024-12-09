#define VALUES 3
typedef struct
{
    int x; // x-coordinate of mine
    int y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
    int minenumber;
} mine_s;

int findEdgeAmount(int bombAmount);
double **make2DArray(int rows, int columns);
double **structTo2D(mine_s bombs[], int bombAmount, int edgeAmount);
double calculateDistance(mine_s bomb1, mine_s bomb2);
void bubbleSort(int paths, int a[paths][VALUES]);

int **kruskalAlgo(int paths, int sortedArray[paths][VALUES]);
    void makeSet(int parent[], int rank[], int n);
    int findParent(int parent[], int component);
    void unionSet(int u, int v, int parent[], int rank[]);





void christofides(mine_s bombs[], int bombamount);
    double **makeMST(int paths, int travelArray[paths][VALUES]);