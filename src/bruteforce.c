#include "bruteforce.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Mines *getShortestPath(const Mines *mines, unsigned int arraySize) {
    // gets every combination 
    Mines **paths = getPaths(mines, arraySize);
    // check if paths is empty:
    if (paths == NULL) return NULL;
    for (unsigned int idx = 0; idx < arraySize; idx++) 
        if (paths[idx] == NULL) return NULL;
    // -----------------------
    // calculate the number of possible paths
    unsigned int numberOfPaths = factorial(arraySize);
    // calculate the shortestPath and store the result
    Mines *result = shortestPath(paths, numberOfPaths, arraySize);
    // check if result is empty
    if (result == NULL) return NULL;
    // return the result = shortest path through the minefield
    return result;
}

Mines *shortestPath(Mines **minefields, unsigned int minefieldscount, unsigned int arraySize) {
    Mines *shortestRoute = (Mines *)malloc(sizeof(Mines) * arraySize);
    if (shortestRoute == NULL) {
        fprintf(stderr, "shortestRoute allocation failed");
        exit(EXIT_FAILURE);
    }
    unsigned int shortestPath = pathLength(minefields[0], arraySize);
    unsigned int temp = 0;
    unsigned int shrtpth = 0;

    for (unsigned int i = 1; i < minefieldscount; i++) {
        temp = pathLength(minefields[i], arraySize);
        if (temp < shortestPath) 
            shrtpth = i;
    }

    for (unsigned int idx = 0; idx < arraySize; idx++)
         shortestRoute[idx] = minefields[shrtpth][idx];
    return shortestRoute;    
}

// TODO make it so every path leads back to the starting one
Mines **getPaths(const Mines *mines, unsigned int arraySize) {
    // array over arrays of paths. Size of the arraypointer times the amount of arrays
    Mines **listOfPaths = (Mines **)malloc(factorial(arraySize) * sizeof(Mines *));
    if (listOfPaths == NULL) exit(EXIT_FAILURE);
    // currentPath will be a var for keeping track of which mines that have already been met 
    Mines *currentPath = (Mines *)malloc(arraySize * sizeof(Mines));
    if (currentPath == NULL) exit(EXIT_FAILURE);
    // index that keeås track of how many paths have been found
    unsigned int idx = 0;
    // find all the diffeneret paths
    findPaths(listOfPaths, mines, currentPath, 0, arraySize, &idx);

    free(currentPath);
    return listOfPaths;
}   

void findPaths(Mines **listOfPaths, const Mines *mines, Mines *path, unsigned int depth, const unsigned int arraySize, unsigned int *currentArray) {
    // depth starts at zero so arraySize - 1
    if (depth == arraySize - 1) {
        // make space for this path in the list of all paths
        listOfPaths[*currentArray] = (Mines *)malloc(arraySize * sizeof(Mines)); 
        if (listOfPaths[*currentArray] == NULL) {
            fprintf(stderr, "list of paths allocation failed");
            exit(EXIT_FAILURE);
        }
        // set last step to the remaining mine 
        path[depth] = mines[0];
        // saved the found path
        for (unsigned int i = 0; i < arraySize; i++)  
            listOfPaths[*currentArray][i] = path[i];
        // update the amount of paths found
        (*currentArray)++;
    }
    // make every mine a possible path
    for (unsigned int i = 0; i < arraySize - depth; i++) {
        // make the next step mine i
        path[depth] = mines[i];
        // allocate space for remaining mines of each path
        Mines *remainingMines = (Mines *)malloc(sizeof(Mines) * (arraySize - depth - 1));
        if (remainingMines == NULL) {
            fprintf(stderr, "remainingMines allocation failed");
            exit(EXIT_FAILURE);
        }
        // copy mines over in remaining mines but not the one already in the path
        int mineNr = 0;
        for (unsigned int j = 0; j < arraySize - depth; j++) { 
            if (j == i) continue;
            remainingMines[mineNr++] = mines[j];
        }
        // recursively call the function with the remaining mines and one step deeper
        findPaths(listOfPaths, remainingMines, path, depth + 1, arraySize, currentArray); 
        free(remainingMines);
    }
}

double pathLength(const Mines *path, unsigned int arraySize) {
    // variable that stores the length of the path
    double length = 0;
    // calculate the length of the entire path
    for (unsigned int idx = 1; idx < arraySize; idx++) 
        length += calculateLength(path[idx - 1], path[idx]); 
    return length;
}

double calculateLength(Mines mine1, Mines mine2) {
    Mines temp; // temp variable for swapping mine values
    // swapvalues to avoid negative numbers 
    if (mine1.x < mine2.x) {
        temp.x = mine1.x;
        mine1.x = mine2.x;
        mine2.x = temp.x;
    }
    if (mine1.y < mine2.y) {
        temp.y = mine1.y;
        mine1.y = mine2.y;
        mine2.y = temp.y;
    }
    // calculate distance between two mines and return
    return sqrt(pow(mine1.x - mine2.x, 2) + pow(mine1.y - mine2.y, 2));
}

unsigned int factorial(unsigned int number) {
    // variable for keeping track of product 
    unsigned int product = 1;
    for (unsigned int n = 1; n <= number; n++) 
        product *= n; // find the product of every number from 1 to number (input) 
    return product;
}
