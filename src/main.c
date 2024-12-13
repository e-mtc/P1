#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "scanCords.h"

#include "VisualOutput.h"
#include "bruteforce.h"
#include "LowBoundTSP.h"

#define MAX_STR_LNGTH 30

int main(void) {
    double start, end;
    /* Including/calling scanCords */
    char filename[MAX_STR_LNGTH];

    printf("Enter the name of the .txt file containing the set of mines:\n");
    scanf(" %s", filename);
    if (strlen(filename) > 30) fprintf(stderr, "Error: Filename too long\n");

    unsigned int mineCount = countMines(filename);

    mine_s minefield[mineCount];
    coordinatesScanInit(minefield, mineCount, filename);

    /* Including/calling visualMinefieldSize */
    unsigned int row = 0, column = 0;
    visualMinefieldSize(minefield, &row, &column, mineCount);

    /* Including/calling VisualOutput */
    visualOutput(row, column, minefield, mineCount); // HUSK: Generalisér størrelse af row og column

    printf("\n");

    // -----------------BRUTEFORCE---------------
    start = clock();
    printf("-----------------BRUTEFORCE---------------");
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
    showMinefield(row, column, shortest, mineCount);
    printf("\n");

    printf("Length of the shortest path:\n");
    double bruteLength = truePathLength(shortest, mineCount);
    printf("%lf\n", bruteLength);
    end = clock();
    double cpu_time_used_brute = (end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n\n", cpu_time_used_brute);

    //------------CHRISTOFIDES----------------
    start = clock();
    printf("-----------------CHRISTOFIDES---------------");
    mine_s minefieldChristo[mineCount];
    christofides(mineCount, minefield, minefieldChristo);

    printf("\n");

    for (unsigned int i = 0; i < mineCount; i++) {
        printf("%c: (%u,%u)\n", i + 65, minefieldChristo[i].x, minefieldChristo[i].y);
    }
    printf("\n");

    /* Including/calling Anas' version of VisualOutput */
    showMinefield(row, column, minefieldChristo, mineCount);
    printf("\n");

    printf("Length of the shortest path:\n");
    double christoLength = truePathLength(minefieldChristo, mineCount);
    printf("%lf\n", christoLength);
    end = clock();
    double cpu_time_used_christo = (end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n\n", cpu_time_used_christo);

    //-------END OF ALGORITHMS----------
    printf("-----------------SUMMARY---------------");
    printf("\n");
    printf("Length of Brute-force algorithm: %.2lf\n", bruteLength);
    printf("Execution time of Brute-force algorithm: %.2lf\n\n", cpu_time_used_brute);

    printf("Length of Christofides algorithm: %.2lf\n", christoLength);
    printf("Execution time of Christofides algorithm: %.2lf\n\n", cpu_time_used_christo);

    if (christoLength < bruteLength) {
        printf("Brute-force is %.2lf times longer than Christofides.\n", bruteLength/christoLength);
    }
    else {
        printf("Christofides is %.2lf times longer than Brute-force.\n", christoLength/bruteLength);
    }
    printf("Christofides is %.2lf times faster than Brute-force.\n", cpu_time_used_brute/cpu_time_used_christo);

    return EXIT_SUCCESS;
}