#define MAX 100

typedef struct
{
    int x; // x-coordinate of mine
    int y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
    int minenumber;
} mine_s;

void christofides(mine_s bombs[], int n, mine_s *sortedArray);
unsigned long long factorial(int n);
void eulerianToHamiltonian(int circuit[], int circuitSize, int path[], int *pathSize, int n, double graph[MAX][MAX]);
void eulerianCircuit(double graph[MAX][MAX], int n, int parent[], int matching[MAX][2], int matchCount, int circuit[], int *circuitSize);
void perfectMatching(double graph[MAX][MAX], int oddVertices[], int oddCount, int matching[MAX][2]);
void findOddVertices(int n, int parent[], int oddVertices[], int *oddCount);
void primMST(double graph[MAX][MAX], int n, int parent[]);
int findMinKey(double key[], double mstSet[], int n);
double calculateDistance(mine_s bomb1, mine_s bomb2);
void pathToStructArray(int *path, int bombAmount, mine_s *bombs, mine_s sortedArray[bombAmount]);