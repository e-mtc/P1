#include <stdio.h>
#include <assert.h>
#include "VisualoutputAnas.h"


/// funktion
void test_VisMinefelt() {
    punkter mine[5] = {

        {0, 1},
        {1, 3},
        {2, 4},
        {3, 5},
        {3, 3}
    };

    int minefelt[4][6]={0};

    for (int i = 0; i < 5; i++) {
        int x = mine[i].x;
        int y = mine[i].y;
        minefelt[x][y] = i + 1;
    }


// aserter om de følende værdier står på kordinaternes plads i 2d arrayet
    assert(minefelt[0][1] == 1);
    assert(minefelt[1][3] == 2);
    assert(minefelt[2][4] == 3);
    assert(minefelt[3][5] == 4);
    assert(minefelt[3][3] == 5);

}
//main for testing og kalder funktionen ind.
int main (void) {

    printf("Test completed sucessfully");
    test_VisMinefelt();


}
