#define VALUES 3
#define WEIGHT 2
void BubbleSort(int paths, int a[paths][VALUES]);
void kruskalAlgo(int paths, int sortedArray[paths][VALUES]);
void makeSet(int parent[], int rank[], int n);
int findParent(int parent[], int component);
void unionSet(int u, int v, int parent[], int rank[]);
void makeMST(int paths, int travelArray[paths][VALUES]);