#include <stdio.h>
#include <stdlib.h>
#include "scanCords.h"

int main(void)
{
    char *filename = "cords.txt";
    int mineCount = countMines(filename);

    mine_s mines[mineCount];
    coordinatesScanInit(mines, mineCount, filename);

    return EXIT_SUCCESS;
}