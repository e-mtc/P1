#include "bruteforce.h"
#include <stdio.h>
#include <assert.h>

#define THREEMINES 3

void test3Mines();
void testPathLength();
void testFactorial();

int main(void) {

    test3Mines();
    testPathLength();
    return 0;
}

void test3Mines() {
    Mines mineList[THREEMINES] = { {1,1}, {2,2}, {3,3} }; 
    
    Mines **paths = getPaths(mineList, THREEMINES);

    assert(paths != NULL);

    for (int i = 0; i < 0; i++)
        assert(paths[i] != NULL);
    
    assert(paths[0][0].x == 1 && paths[0][0].y == 1);
    assert(paths[0][1].x == 2 && paths[0][1].y == 2);
    assert(paths[0][2].x == 3 && paths[0][2].y == 3);

    assert(paths[1][0].x == 1 && paths[1][0].y == 1);
    assert(paths[1][1].x == 3 && paths[1][1].y == 3);
    assert(paths[1][2].x == 2 && paths[1][2].y == 2);

    assert(paths[2][0].x == 2 && paths[2][0].y == 2);
    assert(paths[2][1].x == 1 && paths[2][1].y == 1);
    assert(paths[2][2].x == 3 && paths[2][2].y == 3);

    assert(paths[3][0].x == 2 && paths[3][0].y == 2);
    assert(paths[3][1].x == 3 && paths[3][1].y == 3);
    assert(paths[3][2].x == 1 && paths[3][2].y == 1);

    assert(paths[4][0].x == 3 && paths[4][0].y == 3);
    assert(paths[4][1].x == 1 && paths[4][1].y == 1);
    assert(paths[4][2].x == 2 && paths[4][2].y == 2);
    
    assert(paths[5][0].x == 3 && paths[5][0].y == 3);
    assert(paths[5][1].x == 2 && paths[5][1].y == 2);
    assert(paths[5][2].x == 1 && paths[5][2].y == 1);
}

void testPathLength() {
    Mines mineList[THREEMINES] = { {1,1}, {2,2}, {3,3} }; 
    double length = pathLength(mineList, 3);
    
    assert(2.8 <= length && length <= 2.9);
}
void testFactorial() {
    int result,
        number = 10;

    result = factorial(number);
    assert(result == 3628800);
}
