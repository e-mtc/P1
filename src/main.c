#include <stdio.h>
#include <stdlib.h>
#include "scanCords.h"
#include "VisualOutput.h"
#include "bruteforce.h"

int main(void) {

    /* Including/calling scanCords */
    mine_s minefield[7];  // HUSK: Skift 7 ud med givet antal miner i input - brug mineQuantity somehow?
    char *filename = "cords.txt";
    coordinatesScanInit(minefield, filename);

    unsigned int minefieldSize = sizeof(minefield) / sizeof(minefield[0]);

    /* Including/calling VisualOutput */
    visualOutput(10, 10, minefield, 7); // HUSK: Generalisér størrelse af row og column

    /* Including/calling bruteforce */
    mine_s *shortest = (mine_s*)(sizeof(mine_s)*minefieldSize);
    if (shortest == NULL) exit(EXIT_FAILURE);
    shortest = getShortestPath(minefield, minefieldSize);
    if (shortest == NULL) exit(EXIT_FAILURE);

    printf("\n");

    for (unsigned int i = 0; i < minefieldSize; i++) {
        printf("%u and %u \n", shortest[i].x, shortest[i].y);
    }
    printf("\n");

    /* Including/calling Anas' version of VisualOutput */
    showMinefield(10, 10, shortest, 7); // HUSK: Generalisér størrelse af row og column + minecount (mineQuantity?)
    printf("\n");

    printf("Length of the shortest path:\n");
    printf("%lf\n", pathLength(shortest, minefieldSize));
    return EXIT_SUCCESS;
}
