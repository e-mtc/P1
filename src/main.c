#include <stdio.h>
#include <stdlib.h>
#include "scanCords.h"

int main(void)
{
    mine_s mines[5];

    // Must define string size for use of sprintf()  in coordinatesScanInit()
    char filename[20] = "cords.txt";

    coordinatesScanInit(mines, filename);

    return EXIT_SUCCESS;
}
