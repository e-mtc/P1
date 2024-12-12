//
// Created by ramoj on 05/11/2024.
//
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "VisualOutput.h"
#include "scanCords.h"

//Rasmus' version
void visualOutput(int row, int column, const mine_s input[], unsigned int mineCount) {

    // Initialize variables and matrix
    char matrix[row][column];

    // Make the matrix with the amount called values for row and column. If the inputed struct has
    // the x and y value of j and i, an x will be printed instead of zero to symbolise a mine

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matrix[i][j] = '-';
        }
    }

    for (unsigned int i = 0; i < mineCount; ++i) { // HUSK: Generalisér antal miner ('7')
        matrix[(row-1)-input[i].y][input[i].x] = 'x';
    }

    // Print of the minefield
    printf("Minefield:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

// Anas' version
void showMinefield(int row, int column, const mine_s input[], unsigned int mineCount) {

    // Initialize variables and matrix
    char matrix[row][column];

    // Make the matrix with the amount called values for row and column. If the inputed struct has
    // the x and y value of j and i, an x will be printed instead of zero to symbolise a mine

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matrix[i][j] = '-';
        }
    }

    for (unsigned int i = 0; i < mineCount; ++i) {
        matrix[(row-1)-input[i].y][input[i].x] = i + 65; // only works with alphabet amount of numbers
    }

    // Print of the minefield
    printf("Minefield removal order:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void visualMinefieldSize(const mine_s input[], unsigned int *row, unsigned int *column, unsigned int mineCount) {
    // Go through every y coordinate and assign the biggest number to row
    for (int i = 0; i < mineCount; i++) {
        if (*row < input[i].y) {
            *row = input[i].y;
        }
    }
    // Go through every x coordinate and assign the biggest number to column
    for (int i = 0; i < mineCount; i++) {
        if (*column < input[i].x) {
            *column = input[i].x;
        }
    }
    // +2 due to array indexing for later use
    *row += 2;
    *column += 2;
}
