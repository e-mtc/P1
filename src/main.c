#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanCords.h"
#include "VisualOutput.h"
#include "bruteforce.h"

#define MAX_STR_LNGTH 30

int main(void) {

    /* Including/calling scanCords */
    char filename[MAX_STR_LNGTH];

    printf("Enter the name of the .txt file containing the set of mines:\n");
    scanf(" %s", filename);
    if (strlen(filename) > 30) fprintf(stderr, "Error: Filename too long\n");

    unsigned int mineCount = countMines(filename);

    mine_s minefield[mineCount];
    coordinatesScanInit(minefield, mineCount, filename);
    
    /* Including/calling VisualOutput */
    visualOutput(10, 10, minefield, mineCount); // HUSK: Generalisér størrelse af row og column

    /* Including/calling bruteforce */
    mine_s *shortest = getShortestPath(minefield, mineCount);
    if (shortest == NULL) {
        exit(EXIT_FAILURE);
    }

    printf("\n");

    for (unsigned int i = 0; i < mineCount; i++) {
        printf("%c: (%u,%u)\n", i + 65, shortest[i].x, shortest[i].y);
    }
    printf("\n");

    /* Including/calling Anas' version of VisualOutput */
    showMinefield(10, 10, shortest, mineCount); // HUSK: Generalisér størrelse af row og column + minecount (mineQuantity?)
    printf("\n");

    printf("Length of the shortest path: %lf\n", truePathLength(shortest, mineCount));
    return EXIT_SUCCESS;
}

