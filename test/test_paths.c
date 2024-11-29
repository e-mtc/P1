#include "bruteforce.h"
#include <stdio.h>
#include <assert.h>


void testPathLength();
void testCalculateLength();
void testFactorial();

int main(void) {
    testPathLength();
    testCalculateLength();
    testFactorial();
    return 0;
}

void testPathLength() {
    mine_s mineList[3] = { {1,1,0.5}, {2,2,0.5}, {3,3,0.5} };
    double length = pathLength(mineList, 3);
    
    assert(2.8 <= length && length <= 2.9);
}

void testCalculateLength() {
    mine_s mine1 = {1, 1, 0.5};
    mine_s mine2 = {2, 2, 0.5};

    double length = calculateLength(mine1, mine2);

    assert(1.4 <= length && length <= 2.5);
}

void testFactorial() {
    int result,
        number = 10;

    result = factorial(number);
    assert(result == 3628800);
}
