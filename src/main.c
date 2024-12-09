#include "LowBoundTSP.h"
#include <stdio.h>

int main() {
    int n;
    printf("Number of bombs: ");
    scanf("%d", &n);

    mine_s bombs[n];

    printf("enter coordinates of bombs:\n");
    for (int i = 0; i < n; i++) {
        printf("bomb %d (x y): ", i + 1);
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
        bombs[i].tw = 1;
        bombs[i].mineNumber = i;
        bombs[i].edgeAmount = 0;
    }

    mine_s sortedBombs[n];
    christofides(n, bombs, sortedBombs);

    //for (int i = 0; i < n; ++i) {
    //    printf("x: %d\ny: %d\nminenumber: %d\n", sortedBombs[i].x, sortedBombs[i].y, sortedBombs[i].mineNumber);
    //}

    return 0;
}
