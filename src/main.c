#include "LowBoundTSP.h"
#include <stdio.h>

int main() {
    int n = 11;
    // printf("Number of bombs: ");
    // scanf("%d", &n);

    mine_s bombs[n];

    // printf("enter coordinates of bombs:\n");
    // for (int i = 0; i < n; i++) {
    //     printf("bomb %d (x y): ", i + 1);
    //     scanf("%d %d", &bombs[i].x, &bombs[i].y);
    //     bombs[i].tw = 1;
    //     bombs[i].mineNumber = i;
    //     bombs[i].edgeAmount = 0;
    // }


    bombs[0].x = 8;
    bombs[0].y = 0;
    bombs[0].tw = 9.5;
    bombs[0].mineNumber = 0;
    bombs[0].edgeAmount = 0;

    bombs[1].x = 1;
    bombs[1].y = 7;
    bombs[1].tw = 2.8;
    bombs[1].mineNumber = 1;
    bombs[1].edgeAmount = 0;

    bombs[2].x = 2;
    bombs[2].y = 4;
    bombs[2].tw = 2.1;
    bombs[2].mineNumber = 2;
    bombs[2].edgeAmount = 0;

    bombs[3].x = 6;
    bombs[3].y = 1;
    bombs[3].tw = 7.4;
    bombs[3].mineNumber = 3;
    bombs[3].edgeAmount = 0;

    bombs[4].x = 7;
    bombs[4].y = 5;
    bombs[4].tw = 2.3;
    bombs[4].mineNumber = 4;
    bombs[4].edgeAmount = 0;

    bombs[5].x = 6;
    bombs[5].y = 7;
    bombs[5].tw = 5.9;
    bombs[5].mineNumber = 5;
    bombs[5].edgeAmount = 0;

    bombs[6].x = 6;
    bombs[6].y = 2;
    bombs[6].tw = 7.0;
    bombs[6].mineNumber = 6;
    bombs[6].edgeAmount = 0;

    bombs[7].x = 9;
    bombs[7].y = 2;
    bombs[7].tw = 8.2;
    bombs[7].mineNumber = 7;
    bombs[7].edgeAmount = 0;

    bombs[8].x = 4;
    bombs[8].y = 8;
    bombs[8].tw = 0.4;
    bombs[8].mineNumber = 8;
    bombs[8].edgeAmount = 0;

    bombs[9].x = 3;
    bombs[9].y = 7;
    bombs[9].tw = 1.5;
    bombs[9].mineNumber = 9;
    bombs[9].edgeAmount = 0;

    bombs[10].x = 4;
    bombs[10].y = 9;
    bombs[10].tw = 0.6;
    bombs[10].mineNumber = 10;
    bombs[10].edgeAmount = 0;



    mine_s sortedBombs[n];
    christofides(n, bombs, sortedBombs);

    //for (int i = 0; i < n; ++i) {
    //    printf("x: %d\ny: %d\nminenumber: %d\n", sortedBombs[i].x, sortedBombs[i].y, sortedBombs[i].mineNumber);
    //}

    return 0;
}
