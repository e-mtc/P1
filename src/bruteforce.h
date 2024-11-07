
typedef struct {
    unsigned int x;
    unsigned int y;
} Mines;

/* 
 * @param mines the list of the mines in the minefield
 * @param arraySize the number of mines in the minefield
 * @return returns an array of the shortest path through the minefield
 */
Mines *getShortestPath(const Mines *mines, unsigned int arraySize);

/*
 * @param
 * @param
 * @param
 * @return
 */
Mines *shortestPath(Mines **minefields, unsigned int minefieldscount, unsigned int arraySize);

/*
 * @param mines       the mines in a minefield 
 * @param arraySize   the amount of mines in a minefield
 * @return a list of every path (2D array) 
 */
void **getPaths(void *elements, unsigned int elementSize, unsigned int arraySize);

/*
 * @param listOfPaths     2D list of possible paths
 * @param mines           the mines in the minefield
 * @param path            keeps track of the mines in current path (it changes)
 * @param depth           how deep in the path the function is
 * @param arraySize       amount of mines in minefield
 * @param currentArray    keeps track of how many paths have been found
 * @return void - changes values of listOfPaths
 */
void findPaths(void **listOfPaths, const void *elements, void *path, unsigned int elementSize, unsigned int depth, const unsigned int arraySize, unsigned int *currentArray);

/*
 * @param path       array of mines in path
 * @param arraySize  amount of mines in path
 * @return length of path (double)
 */
double pathLength(const Mines *path, unsigned int arraySize);

/*
 * @param mine1 & mine2   the mines to find the distance between 
 * @return the distance between two mines
 */
double calculateLength(Mines mine1, Mines mine2);

/*
 * @param number  the number to do the factorial calculation on
 * @return        factorial of the input number
 */
unsigned int factorial(unsigned int number); 
