#include <stdio.h>
#include <stdlib.h>

#include "bruteforce.h"

int main(void) {
    mine_s minefield[5];
    char *filename = "cords.txt";
    coordinatesScanInit(minefield, filename);

    unsigned int minefieldSize = sizeof(minefield) / sizeof(minefield[0]);

    mine_s *shortest = (mine_s*)(sizeof(mine_s)*minefieldSize);
    if (shortest == NULL) exit(EXIT_FAILURE);
    shortest = getShortestPath(minefield, minefieldSize);
    if (shortest == NULL) exit(EXIT_FAILURE);

    printf("\n");

    for (unsigned int i = 0; i < minefieldSize; i++) {
        printf("%ld and %ld \n", shortest[i].x, shortest[i].y);
    }

    printf("%lf\n", pathLength(shortest, minefieldSize));
    return EXIT_SUCCESS;
}