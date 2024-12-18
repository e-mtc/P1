#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "runFunctions.h"
#include "scanCords.h"
#include "VisualOutput.h"
#include "bruteforce.h"
#include "LowBoundTSP.h"

//Run fuction for main
void run() {
    unsigned int row = 0, column = 0;
    char filename[MAX_STR_LNGTH];

    //Gets filename
    getFilename(filename);

    unsigned int mineCount = countMines(filename);
    mine_s minefield[mineCount];

    //Scans coordinates in minefield
    scanCords(&row, &column, &mineCount, minefield, filename);


    //Run Bruteforce if within doable amount of mines
    double cpuTimeUsedBrute;
    double bruteLength;
    if (mineCount < 12) {
        initiateBruteforce(row, column, mineCount, &bruteLength, &cpuTimeUsedBrute, minefield);
    } else {
        printf("There are too many mines for bruteforce to run in a decent timespan and therefore wont be run\n");
    }


    //Run Christofides
    double cpuTimeUsedChristo;
    double christoLength;
    mine_s minefieldChristo[mineCount];
    initiateChristofides(row, column, mineCount, &christoLength, &cpuTimeUsedChristo, minefield, minefieldChristo);


    //Compare runtime of algorithms if bruteforce was run
    if (mineCount < 12) {
        compareAlgorithms(bruteLength, christoLength, cpuTimeUsedBrute, cpuTimeUsedChristo);
    }
}

//Gets and defines filename with the .txt added behind
void getFilename(char filename[MAX_STR_LNGTH]) {
    char tempFilename[MAX_STR_LNGTH-4];

    printf("Enter the name of the .txt file containing the set of mines:\n");
    scanf(" %s", tempFilename);
    if (strlen(tempFilename) > 26) {
        fprintf(stderr, "Error: Filename too long\n");
        exit(EXIT_FAILURE);
    }

    sprintf(filename, "%s.txt", tempFilename);
}

//Scans coordinates from given filename
void scanCords (unsigned int *row, unsigned int *column, unsigned int *mineCount, mine_s minefield[], char filename[MAX_STR_LNGTH]) {

    coordinatesScanInit(minefield, *mineCount, filename);

    /* Including/calling visualMinefieldSize */
    visualMinefieldSize(minefield, row, column, *mineCount);

    /* Including/calling VisualOutput */
    visualOutput(*row, *column, minefield, *mineCount); // HUSK: Generalisér størrelse af row og column

    printf("\n");
}

//Initiates and times the bruteforce algorithm whilst printing its results
void initiateBruteforce(unsigned int row, unsigned int column, unsigned int mineCount, double *bruteLength, double *cpuTimeUsedBrute, mine_s minefield[mineCount]) {
    // -----------------BRUTEFORCE---------------
    double start = clock();
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
    *bruteLength = truePathLength(shortest, mineCount);
    printf("%lf\n", *bruteLength);
    double end = clock();
    *cpuTimeUsedBrute = (end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n\n\n", *cpuTimeUsedBrute);
}

//Initiates and times the Christofides algorithm whilst printing its results
void initiateChristofides(unsigned int row, unsigned int column, unsigned int mineCount, double *christoLength, double *cpuTimeUsedChristo, mine_s minefield[mineCount], mine_s minefieldChristo[mineCount]) {
    //------------CHRISTOFIDES----------------
    printf("-----------------CHRISTOFIDES---------------\n");
    printf("Start point: (%u,%u)\n", minefield[0].x, minefield[0].y);

    double start = clock();
    christofides(mineCount, minefield, minefieldChristo);

    printf("\n");

    for (unsigned int i = 0; i < mineCount; i++) {
        printf("%c: (%u,%u)\n", i + 65, minefieldChristo[i].x, minefieldChristo[i].y);
    }
    printf("A: (%u,%u) - Returning to starting point (optional, not included in path length)\n", minefieldChristo[0].x, minefieldChristo[0].y);
    printf("\n");

    /* Including/calling Anas' version of VisualOutput */
    showMinefield(row, column, minefieldChristo, mineCount);
    printf("\n");

    printf("Length of the shortest path:\n");
    *christoLength = truePathLength(minefieldChristo, mineCount);
    printf("%lf\n", *christoLength);
    double end = clock();
    *cpuTimeUsedChristo = (end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n\n", *cpuTimeUsedChristo);
}


//Compares the two formerly run algorithms' runtime and results
void compareAlgorithms(double bruteLength, double christoLength, double cpuTimeUsedBrute, double cpuTimeUsedChristo) {
    //-------END OF ALGORITHMS----------
    printf("-----------------SUMMARY---------------");
    printf("\n");
    printf("Length of Brute-force algorithm: %.2lf\n", bruteLength);
    printf("Execution time of Brute-force algorithm: %.2lf\n\n", cpuTimeUsedBrute);

    printf("Length of Christofides algorithm: %.2lf\n", christoLength);
    printf("Execution time of Christofides algorithm: %.2lf\n\n", cpuTimeUsedChristo);

    if (christoLength < bruteLength) {
        printf("Brute-force is %.2lf times longer than Christofides.\n", bruteLength/christoLength);
    }
    else {
        printf("Christofides is %.2lf times longer than Brute-force.\n", christoLength/bruteLength);
    }
    printf("Christofides is %.2lf times faster than Brute-force.\n", cpuTimeUsedBrute/cpuTimeUsedChristo);
}