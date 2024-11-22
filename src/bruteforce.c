#include "bruteforce.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>



Mines *getShortestPath(Mines *minefield, unsigned int arraySize) {
    // allocate memory for the array that hold the shortest path
    Mines *shrts = (Mines *)malloc(sizeof(Mines) * arraySize);
    if (shrts == NULL) {
        return NULL;
    }
    
    // assume the first path is the shortest (shrts can't be NULL later)
    memcpy(shrts, minefield, sizeof(Mines) * arraySize); 
    if (shrts == NULL) {
        return NULL;
    }
    
    // allocate memory for the current path through the minefield
    Mines *path = (Mines *)malloc(sizeof(Mines) * arraySize);

    // try all combinations and safe the shortest in 
    findShortestPath(shrts, minefield, path, 0, arraySize);

    free(path);
    return shrts;
}

void findShortestPath(Mines *shrt, Mines *minefield, Mines *path, unsigned int depth, unsigned int arraySize) {
    // when the current combinations have been found
    // check if this path is shorter than the current in shrt
    if (depth == arraySize - 2) {
        // copy the first and last element into the first and last sport of path
        memcpy(path, minefield, sizeof(Mines)); 
        memcpy(path + arraySize - 1, minefield + 1, sizeof(Mines)); 
        
        // if this path is shorter than the current shortest
        // replace shrt with the current path
        if (pathLength(path, arraySize) < pathLength(shrt, arraySize)) {
            memcpy(shrt, path, sizeof(Mines) * arraySize);
        }    
    }
    
    // chose a mine as the next in the path
    // call the function again but where that mine cannot be chosen
    for (unsigned int i = 1; i < arraySize - depth - 1; i++) {
        memcpy(path + depth + 1, minefield + i, sizeof(Mines));

        // allocate space for the remaining mines
        Mines *remainingMinefield = (Mines *)malloc(sizeof(Mines) * (arraySize - depth - 1));
        if (remainingMinefield == NULL) { 
            fprintf(stderr, "remainingMinefield err");
        }

        // copy element that are not the current chosen one 
        // into the remaining mines
        unsigned int mineNr = 0;
        for (unsigned int j = 0; j < arraySize - depth; j++) { 
            if (j == i) continue;
            memcpy(remainingMinefield + mineNr++, minefield + j, sizeof(Mines));
        }

        // call recursively -> find next mine in path 
        // stop if every mine in the field is already in the path 
        findShortestPath(shrt, remainingMinefield, path, depth + 1, arraySize);
        free(remainingMinefield); 
    }
}   

double pathLength(const mine_s *path, unsigned int arraySize) {
    // the path must include 2 mines or this function will reference a non-existing element
    if (arraySize < 2) {
        return 0;
    }
    // variable that stores the length of the path
    double length = 0;
    // calculate the length of the entire path
    for (unsigned int idx = 1; idx < arraySize; idx++) {
        length += calculateLength(path[idx - 1], path[idx]);
    }
    return length + path[arraySize].tw;
}

double calculateLength(mine_s mine1, mine_s mine2) {
    mine_s temp; // temp variable for swapping mine values
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
    return sqrt(pow(mine1.x - mine2.x, 2) + pow(mine1.y - mine2.y, 2) * (mine1.tw + mine2.tw));
}

unsigned int factorial(unsigned int number) {
    // variable for keeping track of product 
    unsigned int product = 1;
    for (unsigned int n = 1; n <= number; n++) {
        product *= n; // find the product of every number from 1 to number (input) 
    }
    return product;
}
