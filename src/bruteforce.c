#include "bruteforce.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double calculateLength(Mines mine1, Mines mine2) {
    Mines temp;
    
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

    return sqrt(pow(mine1.x - mine2.x, 2) + pow(mine1.y - mine2.y, 2));
}


Mines **allCombinations(Mines *mines, unsigned int arraySize) {
    // array over arrays of paths. Size of the arraypointer times the amount of arrays
    Mines **listOfPaths = (Mines **)malloc(factorial(arraySize) * sizeof(Mines *));
    // check if malloc was a succes
    if (listOfPaths == NULL) exit(EXIT_FAILURE);
    // current path which is being found for in listOfMineFields
    // maybe no reason to have this. since its mines
    Mines *currentPath = (Mines *)malloc(arraySize * sizeof(Mines));
    if (currentPath == NULL) exit(EXIT_FAILURE);
    for (unsigned int i = 0; i < arraySize; i++)
        currentPath[i] = mines[i];
    // currentPath will be a var for keeping track of which mines that have already been met 
    unsigned int idx = 0;
    findPaths(listOfPaths, mines, currentPath, 0, arraySize, &idx);
    // the current path isnt needed any more only the list of mine fields
    free(currentPath);
    return listOfPaths;
}   

void findPaths(Mines **listOfPaths, Mines *mines, Mines *path, unsigned int depth, unsigned int arraySize, unsigned int *currentArray) {
    if (depth == arraySize) {
        // make space for this path in the list of all paths
        listOfPaths[*currentArray] = (Mines *)malloc(arraySize * sizeof(Mines)); 
        if (listOfPaths[*currentArray] == NULL) { // check if allocation was succesfull
            fprintf(stderr, "list of paths allocation failed");
            exit(EXIT_FAILURE);
        }
        // saved the found path
        for (unsigned int i = 0; i < arraySize; i++) 
            listOfPaths[*currentArray][i] = path[i];
        // update the amount of paths found
        (*currentArray)++;
        // path found so dont do anything in this path 
        return;
    }
    
    for (unsigned int i = 0; i < arraySize - depth; i++) {
        // allocate space for remaining mines of each path
        path[depth] = mines[i];
        Mines *remainingMines = (Mines *)malloc(sizeof(Mines) * (arraySize - depth - 1));
        if (remainingMines == NULL) {
            fprintf(stderr, "remainingMines allocation failed");
            exit(EXIT_FAILURE);
        }
        // copy mines over in remaining mines but not the one already in the path
        int mineNr = 0;
        for (unsigned int j = 0; j < arraySize - depth - 1; j++) { 
            if (j == i) continue;
            remainingMines[mineNr++] = mines[j];
        }
        findPaths(listOfPaths, remainingMines, path, depth + 1, arraySize - depth - 1, currentArray); 
        free(remainingMines);
    }
}

unsigned int factorial(unsigned int num) {
    unsigned int fact = 1;
    for (unsigned int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}
