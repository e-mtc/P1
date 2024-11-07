//
// Created by ramoj on 07/11/2024.
//
#include <assert.h>
#include "VisualOutput.h"

int main(void) {

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

}

void test1 () {
    struct input mine[2];

}