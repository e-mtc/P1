
typedef struct {
    unsigned int x;
    unsigned int y;
} Mines;

double calculateLength(Mines mine1, Mines mine2);

Mines **allCombinations(const Mines *mines, unsigned int arrSize);

void findPaths(Mines **listOfPaths, const Mines *mines, Mines *path, unsigned int depth, const unsigned int arraySize, unsigned int *currentArray);

Mines *shortestPath(Mines **minefields, unsigned int minefieldscount, unsigned int arraySize);

double pathLength(const Mines *path, unsigned int arraySize);

Mines *getShortestPath(const Mines *mines, unsigned int arraySize);

unsigned int factorial(unsigned int num); 
