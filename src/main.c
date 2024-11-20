#include <stdio.h>
#include <stdlib.h>
#include "scanCords.h"

int main(void)
{
    mine_s mines[7];
    char *filename = "cords.txt";

    coordinatesScanInit(mines, filename);

    return EXIT_SUCCESS;
}