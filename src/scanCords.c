#include <stdio.h>
#include "scanCords.h"


void coordinatesScanInit(mine_s *mines, char *filename)
{
    // Adding a path specifier to the filename
    char filepath[20];
    sprintf(filepath,"../%s",filename);

    // Declaring, initialising file pointer
    FILE *file = fopen(filepath,"r");

    // Prints error in case of a NULL file (empty)
    if (file == NULL)
    {
        perror("Error creating file");
    }

    // Calculating the number mines (number of newlines).
    int mineQuantity=0;
    char c = fgetc(file);
    while ((c != EOF))
    {
        if (c == '\n'){mineQuantity++;}
        c = fgetc(file);
    }
    mineQuantity += 1;

    printf("Antal: %d\n",mineQuantity);


    rewind(file); // Resets the position indicator to the start of the file
    for (int i = 0; i < mineQuantity; ++i)
    {
        fscanf(file, "%d %d", &mines[i].x, &mines[i].y);
        printf("%d and %d\n", mines[i].x, mines[i].y);
    }
    fclose(file);
}
