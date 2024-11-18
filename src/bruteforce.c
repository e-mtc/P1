#include "bruteforce.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>


Mines *getShortestPath(Mines *mines, unsigned int arraySize) {
    // gets every combination 
    Mines **paths = (Mines **)getPaths(mines, sizeof(Mines), arraySize);
    if (paths == NULL) return NULL;
    for (unsigned int idx = 0; idx < arraySize; idx++) 
        if (paths[idx] == NULL) return NULL;

    // calculate the number of possible paths
    // calculate the shortestPath and store the result
    unsigned int numberOfPaths = factorial(arraySize - 2);
    Mines *result = shortestPath(paths, numberOfPaths, arraySize);
    if (result == NULL) return NULL;

    // return the result = shortest path through the minefield
    return result;
}

Mines *shortestPath(Mines **paths, unsigned int minefieldscount, unsigned int arraySize) {
    // variables for path number, the length of the shortest path and a temporary value
    unsigned int pathNr = 0;
    double shortest = pathLength(paths[0], arraySize);
    double temp = 0;

    // calculate the length of each path and save the shortest (or one of them)
    for (unsigned int i = 1; i < minefieldscount; i++) {
        temp = pathLength(paths[i], arraySize);

        if (temp < shortest) { 
            pathNr = i;
            shortest = temp;
        }
    }

    // return the path that results in the shortest path
    return paths[pathNr];    
}

void **getPaths(void *elements, unsigned int elementSize, unsigned int arraySize) {
    // calculate and allocate memory for every kind of combinations of paths
    // -2 because the first and last element should always be the same
    unsigned int combinations = factorial(arraySize - 2);  
    void **paths = (void **)malloc(sizeof(void *) * combinations);
    if (paths == NULL) fprintf(stderr, "paths err");

    // allocate memory for keeping track of current path
    void *currentPath = (void *)malloc(elementSize * arraySize);
    if (currentPath == NULL) fprintf(stderr, "currentPath err");

    // keep tracking of how many paths have been found (idx) 
    // and call the recursive function (findPaths)
    unsigned int idx = 0;
    findPaths(paths, elements, currentPath, elementSize, 0, arraySize, &idx);
    
    // free unused memory
    free(currentPath);

    return paths;
}   

void findPaths(void **paths, const void *elements, void *path, unsigned int elementSize, unsigned int depth, const unsigned int arraySize, unsigned int *currentArray) {
    // if all combinations have been gone through
    // -2 because two elements should always stay the same
    if (depth == arraySize - 2) {
        // allocate memory for this specific path
        paths[*currentArray] = (void *)malloc(arraySize * elementSize);
        if (paths[*currentArray] == NULL) fprintf(stderr, "currentArray err");

        // copy first mine into the first pos in path
        // add the last element to the path (should always be the same element)
        memcpy(path, elements, elementSize); 
        memcpy((char *)path + ((arraySize - 1) * elementSize), (char *)elements + elementSize, elementSize); 

        // copy this path over in paths and update how many paths have been found
        memcpy(paths[*currentArray], path, arraySize * elementSize);
        (*currentArray)++;
    }            
    
    // loop through every element in elements but not the first (i = 1) and last element (-1) 
    for (unsigned int i = 1; i < arraySize - depth - 1; i++) { 
        // copy this element (elements[i]) into this path
        memcpy((char *)path + ((depth + 1) * elementSize), (char *)elements + (i * elementSize), elementSize);

        // allocate memory for elements minus 1 element because it should shrink
        void *remainingElements = (void *)malloc(elementSize * (arraySize - depth - 1));
        if (remainingElements == NULL) fprintf(stderr, "remainingElements err");

        // copy the elements over into another array but not the one just added to the path
        unsigned int elementNr = 0;
        for (unsigned int j = 0; j < arraySize - depth; j++) {
            if (j == i) continue;
            memcpy((char *)remainingElements + (elementNr++ * elementSize), (char *)elements + (j * elementSize), elementSize);
        }

        // call findPaths recursively with +1 to depth
        findPaths(paths, remainingElements, path, elementSize, depth + 1, arraySize, currentArray);
        free(remainingElements);
    }
}

double pathLength(const Mines *path, unsigned int arraySize) {
    // the path must include 2 mines or this function will reference a non-existing element
    if (arraySize < 2) return 0;
    // variable that stores the length of the path
    double length = 0;
    // calculate the length of the entire path
    for (unsigned int idx = 1; idx < arraySize; idx++) 
        if (path[idx - 1] == NULL && path[idx] == NULL) return -1;
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
