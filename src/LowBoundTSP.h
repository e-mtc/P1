#define VALUES 3
#define WEIGHT 2
void christofidesTSP(int paths, int travelArray[][VALUES]); //-------------------
    int **makeMST(int paths, int travelArray[paths][VALUES]); //------------------
        void bubbleSort(int paths, int a[paths][VALUES]);
        int **kruskalAlgo(int paths, int sortedArray[paths][VALUES]); //-----------------
            void makeSet(int parent[], int rank[], int n);
            int findParent(int parent[], int component);
            void unionSet(int u, int v, int parent[], int rank[]);
    int *makeSubgraph(int **MST);

int **make2DArray(int rows, int columns);
void freeArray(int** array, int rows);