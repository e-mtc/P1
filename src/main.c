#include "LowBoundTSP.h"
#include <stdio.h>

int main() {
    int n;
    printf("Number of bombs: ");
    scanf("%d", &n);
    
    Bombs bombs[MAX];
    
    printf("enter coordinates of bombs:\n");
    for (int i = 0; i < n; i++) {
        printf("bomb %d (x y): ", i + 1);
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }

    christofides(bombs, n);
    return 0;
}
