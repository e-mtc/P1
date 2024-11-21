//
// Created by ramoj on 20/11/2024.
//

#include "GenerateRandomCluster.h"
#include "scanCords.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UPPER 50


// This function takes an input for a number of mines
// and generates random value no higher than UPPER for x and y from the struct in scanCords.h
// Then it prints a file that is defined in main with filename
void GenerateRandomCluster (char* filename) {

    // Adds a path specifier "src/" to filename
    // The name of the file can be no longer than the "length" in filepath[length]
    char filepath[20];
    sprintf(filepath, "src/%s", filename);

    // Variable for the number of mines in a cluster
    int NumberOfMines;

    // Input a value for number of mines in a cluster
    printf("Enter the number of mines in your cluster: ");
    scanf("%d", &NumberOfMines);

    // Variable for struct of mines based on the variable NumberOfMines
    mine_s mines[NumberOfMines];

    // Generate random numbers
    srand(time(NULL));

    // Assign random values for the x- and y-coordinates in the struct
    for (int i = 0; i < NumberOfMines; ++i) {
        mines[i].x = rand() % (UPPER + 1);
        mines[i].y = rand() % (UPPER + 1);
        //mines[i].t = rand() % (UPPER + 1);
    }

    // Open a file in write mode,
    // that should write x- and y-coordinates for a cluster of mines
    FILE *fp = fopen(filepath, "w");
    // Checks if the file is open
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    // Prints the assigned values from the struct into the file that fp is pointing to
    // Which in this case is the one filepath points to which is filename
    for (int i = 0; i < NumberOfMines; ++i) {
        fprintf(fp, "%u %u\n", mines[i].x, mines[i].y); /*mines[i].t; */
    }

    fclose(fp);

}
