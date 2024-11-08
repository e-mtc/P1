#include "bruteforce.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>


Mines *getShortestPath(Mines *mines, unsigned int arraySize) {
    // gets every combination 
    Mines **paths = (Mines **)getPaths(mines, sizeof(Mines), arraySize);
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
    double shortestPath = pathLength(minefields[0], arraySize);
    double temp = 0;
    unsigned int shrtpth = 0;

    for (unsigned int i = 1; i < minefieldscount; i++) {
        temp = pathLength(minefields[i], arraySize);
        if (temp < shortestPath) { 
            shrtpth = i;
            shortestPath = temp;
        }
    }

    for (unsigned int idx = 0; idx < arraySize; idx++)
         shortestRoute[idx] = minefields[shrtpth][idx];
    return shortestRoute;    
}

void **getPaths(void *elements, unsigned int elementSize, unsigned int arraySize) {
    unsigned int combinations = factorial(arraySize);

    void **paths = (void **)malloc(sizeof(void *) * combinations);
    if (paths == NULL) fprintf(stderr, "paths err");

    void *currentPath = (void *)malloc(elementSize * arraySize);
    if (currentPath == NULL) fprintf(stderr, "currentPath err");

    unsigned int idx = 0;
    findPaths(paths, elements, currentPath, elementSize, 0, arraySize, &idx);
    
    free(currentPath);
    return paths;
}   

void findPaths(void **listOfPaths, const void *elements, void *path, unsigned int elementSize, unsigned int depth, const unsigned int arraySize, unsigned int *currentArray) {
    if (depth == arraySize) {
        listOfPaths[*currentArray] = (void *)malloc(arraySize * elementSize);
        if (listOfPaths[*currentArray] == NULL) fprintf(stderr, "currentArray err");
        memcpy(listOfPaths[*currentArray], path, arraySize * elementSize);
        (*currentArray)++;
    }            
    
    for (unsigned int i = 0; i < arraySize - depth; i++) {
        memcpy((char *)path + (depth * elementSize), (char *)elements + (i * elementSize), elementSize);

        void *remainingElements = (void *)malloc(elementSize * (arraySize - depth - 1));
        if (remainingElements == NULL) fprintf(stderr, "remainingElements err");

        unsigned int elementNr = 0;
        for (unsigned int j = 0; j < arraySize - depth; j++) {
            if (j == i) continue;
            memcpy((char *)remainingElements + (elementNr++ * elementSize), (char *)elements + (j * elementSize), elementSize);
        }

        findPaths(listOfPaths, remainingElements, path, elementSize, depth + 1, arraySize, currentArray);
        free(remainingElements);
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
