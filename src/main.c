#include "LowBoundTSP.h"
#include <stdio.h>

int main() {
    int n;
    printf("Number of bombs: ");
    scanf("%d", &n);
    
    mine_s bombs[MAX];
    
    printf("enter coordinates of bombs:\n");
    for (int i = 0; i < n; i++) {
        printf("bomb %d (x y): ", i + 1);
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
        bombs[i].tw = 1;
        bombs[i].minenumber = i;
    }


    mine_s *sortedBombs = christofides(bombs, n);

    for (int i = 0; i < n; ++i) {
        printf("x: %d\ny: %d\nminenumber: %d\n", sortedBombs[i].x, sortedBombs[i].y, sortedBombs[i].minenumber);
    }

    return 0;
}
