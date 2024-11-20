#include "VisualoutputAnas.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"



/// @param minefelt Som er et 2d array på 4 rækker og 6 kolonner

void VisMinefelt(int minefelt[4][6]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (minefelt[i][j] > 0) {
                printf("%d ", minefelt[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}



int main() {

//I set the minefield array to 0 så that nothing is written in the spaces.
    int minefelt[4][6]={0};

    // This is where we insert the coordinates of the mines in the array struct
punkter mine[5] = {

    {0, 1},
    {1, 3},
    {2, 4},
    {3, 5},
    {3, 3}
};

// For loop that saves each of the array structs to the variable int  X and Y.
// We then insert a new value to that coordinates position which is from 1 to 5.


for (int i = 0; i < 5; i++) {
    int x = mine[i].x;
    int y = mine[i].y;
    minefelt[x][y] = i + 1;
}

//  text that shows the minefield:
    printf("Minefelt:\n");

// Here we call the function Visminefelt in main and as a parameter minefelt.
    VisMinefelt(minefelt);

    return 0;
}