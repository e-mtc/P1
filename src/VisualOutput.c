//
// Created by ramoj on 05/11/2024.
//

#include  "VisualOutput.h"
#include <stdio.h>


/*int main (void) {
    // Simulates a struct of mines with x and y coordinates. So 1.1, 2.2, 3.3, 4.4, 5.5 ... i,j is based on n.
    // Struct is in header file.
    int n = 7;
    struct input mine[n];
    int i;
    for (i = 0; i < n; i++) {
            mine[i].x = i;
            mine[i].y = i;
    }

    VisualOutput(7, 10, mine);

}*/


void VisualOutput(int row, int column, const struct input input[]) {

    // Initialize variables and matrix
    int i, j;
    char matrix [row][column];

    // Make the matrix with the amount called values for row and column. If the inputed struct has
    // the x and y value of j and i, an x will be printed instead of zero to symbolise a mine
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if ((input[j].x == j) && (input[j].y == i)) {
                matrix[i][j] = 'x';
            } else
            matrix[i][j] = '0';
        }
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