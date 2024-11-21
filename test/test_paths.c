#include "bruteforce.h"
#include <stdio.h>
#include <assert.h>


void testGetShortestPath(); // also test shortestPath as it is part of it
void test5Mines(); // also testes findPaths as it is part of it
void testPathLength();
void testCalculateLength();
void testFactorial();

int main(void) {
    test5Mines();
    testPathLength();
    testCalculateLength();
    testFactorial();
    return 0;
}

void testGetShortestPath() {
    mine_s minefield[6] = { {3,2}, {4,3}, {8,4}, {6,2}, {1,1}, {3,2} };

    mine_s *shrt = getShortestPath(minefield, 6);
    assert(shrt == NULL);

    double length = pathLength(shrt, 6);

    assert(15.69 <= length && length <= 15.71);
}

void test5Mines() {
    mine_s mineList[5] = { {1,1}, {3,3}, {2,2}, {1,4}, {1,1} };
    
    mine_s **paths = (mine_s **)getPaths(mineList, sizeof(mine_s), 5);

    assert(paths != NULL);
    for (int i = 0; i < 5; i++)
        assert(paths[i] != NULL);
    
    assert(paths[0][0].x == 1 && paths[0][0].y == 1);
    assert(paths[0][1].x == 3 && paths[0][1].y == 3);
    assert(paths[0][2].x == 2 && paths[0][2].y == 2);
    assert(paths[0][3].x == 1 && paths[0][3].y == 4);
    assert(paths[0][4].x == 1 && paths[0][4].y == 1);

    assert(paths[1][0].x == 1 && paths[1][0].y == 1);
    assert(paths[1][1].x == 3 && paths[1][1].y == 3);
    assert(paths[1][2].x == 1 && paths[1][2].y == 4);
    assert(paths[1][3].x == 2 && paths[1][3].y == 2);
    assert(paths[1][4].x == 1 && paths[1][4].y == 1);

    assert(paths[2][0].x == 1 && paths[2][0].y == 1);
    assert(paths[2][1].x == 2 && paths[2][1].y == 2);
    assert(paths[2][2].x == 3 && paths[2][2].y == 3);
    assert(paths[2][3].x == 1 && paths[2][3].y == 4);
    assert(paths[2][4].x == 1 && paths[2][4].y == 1);

    assert(paths[3][0].x == 1 && paths[3][0].y == 1);
    assert(paths[3][1].x == 2 && paths[3][1].y == 2);
    assert(paths[3][2].x == 1 && paths[3][2].y == 4);
    assert(paths[3][3].x == 3 && paths[3][3].y == 3);
    assert(paths[3][4].x == 1 && paths[3][4].y == 1);

    assert(paths[4][0].x == 1 && paths[4][0].y == 1);
    assert(paths[4][1].x == 1 && paths[4][1].y == 4);
    assert(paths[4][2].x == 3 && paths[4][2].y == 3);
    assert(paths[4][3].x == 2 && paths[4][3].y == 2);
    assert(paths[4][4].x == 1 && paths[4][4].y == 1);
   
    assert(paths[5][0].x == 1 && paths[5][0].y == 1);
    assert(paths[5][1].x == 1 && paths[5][1].y == 4);
    assert(paths[5][2].x == 2 && paths[5][2].y == 2);
    assert(paths[5][3].x == 3 && paths[5][3].y == 3);
    assert(paths[5][4].x == 1 && paths[5][4].y == 1);
}

void testPathLength() {
    mine_s mineList[3] = { {1,1}, {2,2}, {3,3} };
    double length = pathLength(mineList, 3);
    
    assert(2.8 <= length && length <= 2.9);
}

void testCalculateLength() {
    mine_s mine1 = {1, 1};
    mine_s mine2 = {2, 2};

    double length = calculateLength(mine1, mine2);

    assert(1.4 <= length && length <= 2.5);
}

void testFactorial() {
    int result,
        number = 10;

    result = factorial(number);
    assert(result == 3628800);
}
