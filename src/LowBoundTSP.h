#define MAX 100

typedef struct {
    int x;
    int y;
} Bombs;

void christofides(Bombs bombs[], int n);
unsigned long long factorial(int n);
void eulerianToHamiltonian(int circuit[], int circuitSize, int path[], int *pathSize, int n, int graph[MAX][MAX]);
void eulerianCircuit(int graph[MAX][MAX], int n, int parent[], int matching[MAX][2], int matchCount, int circuit[], int *circuitSize);
void perfectMatching(int graph[MAX][MAX], int oddVertices[], int oddCount, int matching[MAX][2]);
void findOddnertices(int n, int parent[], int oddVertices[], int *oddCount);
void primMST(int graph[MAX][MAX], int n, int parent[]);
int findMinKey(int key[], int mstSet[], int n);
int calculateDistance(Bombs bomb1, Bombs bomb2);