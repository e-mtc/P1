#include <stdio.h>
#include <ctype.h>
#include "scanCords.h"

#include <stdlib.h>


void coordinatesScanInit(mine_s* mines, char* filename)
{
    // Adding a path specifier "../" to filename
    char filepath[20];
    sprintf(filepath, "../%s", filename);

    // Declaring and initialising file pointer
    FILE* file = fopen(filepath, "r");

    // Prints error in case of a NULL file (empty)
    if (file == NULL)
    {
        perror("Error creating file");
    }

    // Calculating the number of mines (number of newlines).
    int mineQuantity = 0;
    char c = fgetc(file);
    while ((c != EOF))
    {
        if ((c == '\n') && (isdigit(fgetc(file)))) { mineQuantity++; }
        c = fgetc(file);
    }
    mineQuantity += 1;
    printf("Antal: %d\n", mineQuantity);

    rewind(file); // Resets the position indicator to the start of the file
    for (int i = 0; i < mineQuantity; ++i)
    {
        if (!isdigit(fgetc(file)) && (fgetc(file) != '\n'))
        {
            fseek(file, -2, SEEK_CUR);
            fprintf(stderr, "Error: Invalid input scanned at position %d\n", ftell(file));
            exit(EXIT_FAILURE);
        }
        fseek(file, -1, SEEK_CUR);

        fscanf(file, "%d %d", &mines[i].x, &mines[i].y);
        printf("%d and %d\n", mines[i].x, mines[i].y);
        fseek(file, 2, SEEK_CUR);
    }
    fclose(file);
}
