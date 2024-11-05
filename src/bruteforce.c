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


Mines *allCombinations(Mines *mines, unsigned int arrSize) {
    Mines *list1 = (Mines *)malloc(sizeof(mines[0])*arrSize*factorial(arrSize));

    if (list1 == NULL)
        exit(EXIT_FAILURE);

    unsigned int currentList = 0;

    for (unsigned int i = 0; i < arrSize; i++) {
        for (unsigned int j = 0; j < arrSize; j++) {
            if (j == i) continue;
            for (unsigned int k = 0; k < arrSize; k++) {
                if (k == j || k == i) continue;
                list1[currentList++] = mines[i];
                list1[currentList++] = mines[j];
                list1[currentList++] = mines[k];
            }
        }
    }
    return list1;
}   


unsigned int factorial(unsigned int num) {
    unsigned int fact = 1;
    for (unsigned int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}
