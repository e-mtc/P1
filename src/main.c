#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bruteforce.h"

int main(void) {
    int mines;
    int mineCounter = 1;
    int mineXY;
    int j = 0;
    int mineCoordinates[mines + 1];
    printf("How many landmines?");
    scanf("%d",&mines);
    for(int i = 0; i < mines; ++i) {
        printf("what is the coordinate of landmine number %d?", mineCounter);
        scanf("%d", &mineXY);
        printf("\n");
        j += 1;
        mineCoordinates[j-1] = mineXY;
        ++mineCounter;
        printf("%d\n", mineCoordinates[j-1]);
    }
    return 0;
}



