
typedef struct {
    unsigned int x;
    unsigned int y;
} Mines;

double calculateLength(Mines mine1, Mines mine2);

Mines **allCombinations(Mines *mines, unsigned int arrSize);

void findPaths(Mines **listOfPaths, Mines *mines, Mines *path, unsigned int depth, unsigned int arraySize, unsigned int *currentArray);

unsigned int factorial(unsigned int num); 
