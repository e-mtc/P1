
typedef struct {
    unsigned int x;
    unsigned int y;
} Mines;

// the usefull function
// @param mines the list of the mines in the minefield
// @param arraySize the number of mines in the minefield
// @return returns an array of the shortest path through the minefield
Mines *getShortestPath(const Mines *mines, unsigned int arraySize);

Mines **getPaths(const Mines *mines, unsigned int arrSize);

double calculateLength(Mines mine1, Mines mine2);

void findPaths(Mines **listOfPaths, const Mines *mines, Mines *path, unsigned int depth, const unsigned int arraySize, unsigned int *currentArray);

Mines *shortestPath(Mines **minefields, unsigned int minefieldscount, unsigned int arraySize);

double pathLength(const Mines *path, unsigned int arraySize);

unsigned int factorial(unsigned int num); 
