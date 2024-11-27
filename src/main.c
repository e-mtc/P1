#include <stdio.h>
#include <stdlib.h>
#include "scanCords.h"

#include "VisualOutput.h"
#include "bruteforce.h"

int main(void) {

    /* Including/calling scanCords */
    char *filename = "cords.txt";
    unsigned int mineCount = countMines(filename);

    mine_s minefield[mineCount];
    coordinatesScanInit(minefield, mineCount, filename);

    /* Including/calling visualMinefieldSize */
    unsigned int row = 0, column = 0;
    visualMinefieldSize(minefield, &row, &column, mineCount);

    /* Including/calling VisualOutput */
    visualOutput(row, column, minefield, mineCount); // HUSK: Generalisér størrelse af row og column

    /* Including/calling bruteforce */
    mine_s *shortest = getShortestPath(minefield, mineCount);
    if (shortest == NULL) {
        exit(EXIT_FAILURE);
    }

    printf("\n");

    for (unsigned int i = 0; i < mineCount; i++) {
        printf("%u and %u \n", shortest[i].x, shortest[i].y);
    }
    printf("\n");

    /* Including/calling Anas' version of VisualOutput */
    showMinefield(row, column, shortest, mineCount); // HUSK: Generalisér størrelse af row og column + minecount (mineQuantity?)
    printf("\n");

    printf("Length of the shortest path:\n");
    printf("%lf\n", truePathLength(shortest, mineCount));
    return EXIT_SUCCESS;
}

