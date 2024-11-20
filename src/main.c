#include <stdio.h>
#include <stdlib.h>
#include "VisualOutput.h"
#include "bruteforce.h"

int main(void) {

    /* Including scanCords */
    mine_s minefield[7];  // HUSK: Skift 7 ud med givet antal miner i input
    char *filename = "cords.txt";
    coordinatesScanInit(minefield, filename);

    unsigned int minefieldSize = sizeof(minefield) / sizeof(minefield[0]);

    /* Including VisualOutput */
    VisualOutput(10, 10, minefield); // HUSK: Generalisér størrelse af row og column

    /* Including bruteforce */
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