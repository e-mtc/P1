//
// Created by ramoj on 20/11/2024.
//
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct{
    unsigned int x;
    unsigned int y;
    double t;
} mine_s;


void TestTextFile(char* filename, int NumberOfMines) {
    NumberOfMines = 11;
    // Struct for NumberOfMines
    mine_s mines[NumberOfMines];

    // Adds a path specifier "src/" to filename
    // The name of the file can be no longer than the "length" in filepath[length]
    char filepath[20];
    sprintf(filepath, "src/%s", filename);

    // Opens file in read mode
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    // Reads a given file with the written format
    for (int i = 0; i < NumberOfMines; ++i) {
        fscanf(fp, "%u %u %lf\n", mines[i].x, mines[i].y, mines[i].t);
    }

    // Closes file
    fclose(fp);

    // Loop for different tests
    for (int i = 0; i < NumberOfMines; ++i) {
        // Checks if the coordinate is a negative number
        assert(mines[i].x >= 0 && mines[i].y >= 0 && mines[i].t >= 0 &&
            "There is a coordinate with a negative number");
        // Checks if the coordinate is a digit
        assert(isdigit(mines[i].x && mines[i].y && mines[i].t) &&
            "There is a coordinate that is not a digit");
    }






}
