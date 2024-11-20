//
// Created by ramoj on 05/11/2024.
//
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "VisualOutput.h"
#include "scanCords.h"

//Rasmus' version
void visualOutput(int row, int column, const mine_s input[], int mineCount) {

    // Initialize variables and matrix
    int i, j;
    char matrix [row][column];

    // Make the matrix with the amount called values for row and column. If the inputed struct has
    // the x and y value of j and i, an x will be printed instead of zero to symbolise a mine

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            matrix[i][j] = '-';
        }
    }

    for (i = 0; i < mineCount; ++i) { // HUSK: Generalisér antal miner ('7')
        matrix[input[i].y][input[i].x] = 'x';
    }

    // Print of the minefield
    printf("Minefield:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

// Anas' version
void showMinefield(int row, int column, const mine_s input[], int mineCount) {

    // Initialize variables and matrix
    int i, j;
    char matrix [row][column];

    // Make the matrix with the amount called values for row and column. If the inputed struct has
    // the x and y value of j and i, an x will be printed instead of zero to symbolise a mine

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            matrix[i][j] = '-';
        }
    }

    for (i = 0; i < mineCount; ++i) { 
        matrix[input[i].y][input[i].x] = i + 65; // only works with 10 number ATM
    }

    // Print of the minefield
    printf("Minefield removal order:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}
