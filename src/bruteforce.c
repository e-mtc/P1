#include "bruteforce.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

mine_s *getShortestPath(mine_s *minefield, unsigned int arraySize) {
    // allocate memory for the array that hold the shortest path
    mine_s *shortestPath = (mine_s *)malloc(sizeof(mine_s) * arraySize);
    if (shortestPath == NULL) {
        return NULL;
    }
    
    // assume the first path is the shortest (shrts can't be NULL later)
    memcpy(shortestPath, minefield, sizeof(mine_s) * arraySize); 
    if (shortestPath == NULL) {
        return NULL;
    }
    
    // allocate memory for the current path through the minefield
    mine_s *path = (mine_s *)malloc(sizeof(mine_s) * arraySize);
    if (path == NULL) {
        return NULL;
    }

    // try all combinations and save the shortest in the shortestPath pointer
    findShortestPath(shortestPath, minefield, path, 0, arraySize);

    free(path); // free the path pointer as it will not be used anymore
    return shortestPath;
}

void findShortestPath(mine_s *shortestPath, mine_s *minefield, mine_s *path, unsigned int depth, unsigned int arraySize) {
    // when there are no mines left
    if (depth == arraySize - 2) {
        // set the first and last mine to be the first and last in the current path
        memcpy(path, minefield, sizeof(mine_s)); 
        memcpy(path + arraySize - 1, minefield + 1, sizeof(mine_s)); 
        
        // if the current path is shorter than the shortest path
        // replace the shortest path with the current path
        if (pathLength(path, arraySize) < pathLength(shortestPath, arraySize)) {
            memcpy(shortestPath, path, sizeof(mine_s) * arraySize);
        }    
    }
    
    // loops through all possible mines
    // set the next step to be that mine 
    // and call function again but where that mines cannot be the next step
    for (unsigned int i = 1; i < arraySize - depth - 1; i++) {
        // make the current mine (path[i]) the next step
        memcpy(path + depth + 1, minefield + i, sizeof(mine_s));

        // allocate space for the remaining mines
        mine_s *remainingMinefield = (mine_s *)malloc(sizeof(mine_s) * (arraySize - depth - 1));
        if (remainingMinefield == NULL) { 
            fprintf(stderr, "remainingMinefield err");
        }

        // copy all mines that are not the current chosen mine into an array of the remaining mines
        // mineNr -> index for filling every spot in the remainingMinefield array
        // j -> index for every mine in the current minefield
        unsigned int mineNr = 0;
        for (unsigned int j = 0; j < arraySize - depth; j++) { 
            if (j == i) continue;
            memcpy(remainingMinefield + mineNr++, minefield + j, sizeof(mine_s));
        }

        // call recursively -> choose next mine in path 
        // stop if every mine in the field is already in the path 
        findShortestPath(shortestPath, remainingMinefield, path, depth + 1, arraySize);
        free(remainingMinefield); // free remaningMinefield since it will not be used beyond this point
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
    return length;
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
    return sqrt(pow(mine1.x - mine2.x, 2) + pow(mine1.y - mine2.y, 2)) * (mine1.tw + mine2.tw);
}

unsigned int factorial(unsigned int number) {
    // variable for keeping track of product 
    unsigned int product = 1;
    for (unsigned int n = 1; n <= number; n++) {
        product *= n; // find the product of every number from 1 to number (input) 
    }
    return product;
}
