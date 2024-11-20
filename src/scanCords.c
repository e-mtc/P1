#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #define _POSIX_SOURCE
// #include <unistd.h>
#include "scanCords.h"

#define MAX_STR_LNGTH 256

// MANUAL:
// 1. Get no. mines with countMines().
// 2. Declare and initialise array of type mine_s. Set size to no. mines.
// 3. Create string (char array) containing name of .txt file with coordinates. E.g. "coordinates.txt."
// 4. Pass elements (from step 1 & 2) into coordinatesScanInit().


int countMines(char *filename)
{
    // Adding a path specifier "../" to filename
    char filepath[MAX_STR_LNGTH];
    sprintf(filepath, "src/%s", filename);


    // Declaring and initialising file pointer
    FILE* file = fopen("src/cords.txt", "r");

    // Prints error in case of a NULL file (empty)
    if (file == NULL)
    {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    // Calculating the number of mines (number of newlines).
    int mineQuantity = 0;
    char c = fgetc(file);
    while ((c != EOF))
    {
        if ((c == '\n') && ((fgetc(file)) != 10)){ mineQuantity++;}
        c = fgetc(file);
    }
    fclose(file);

    // Mine count, adding 1 because not actual coordinates are counted, but number of newlines.
    mineQuantity += 1;
    printf("Antal: %d\n", mineQuantity);

    return mineQuantity;
}

void coordinatesScanInit(mine_s* mines, int mineCount, char* filename)
{
    // Adding a path specifier "../" to filename
    char filepath[MAX_STR_LNGTH];
    sprintf(filepath, "src/%s", filename);

    // Declaring and initialising file pointer
    FILE* file = fopen(filepath, "r");

    // Prints error in case of a NULL file (empty)
    if (file == NULL)
    {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < mineCount; ++i)
    {
        // Printing error if misinput is detected.
        if (!isdigit(fgetc(file)) && (fgetc(file) != '\n'))
        {
            fseek(file, -2, SEEK_CUR);
            fprintf(stderr, "Error: Invalid input scanned at position %d\n", ftell(file));
            exit(EXIT_FAILURE);
        }
        // Going back only 1 because it's an AND-condition which short circuits,
        // thus only fgetc() is used (indicator is only advanced by 1).
        fseek(file, -1, SEEK_CUR);

        // Scanning the coordinates
        fscanf(file, "%d %d %lf", &mines[i].x, &mines[i].y, &mines[i].tw);
        printf("%d and %d tw: %0.1lf\n", mines[i].x, mines[i].y, mines[i].tw);
        fseek(file, 2, SEEK_CUR); // Going to next line
    }

    // Checking if last coordinate entry is a valid digit

    fseek(file, -9, SEEK_CUR);
    if (!isdigit(fgetc(file)))
    {
        fseek(file, -1, SEEK_CUR);
        fprintf(stderr, "Error: Invalid input scanned at position %d\n", ftell(file));
        exit(EXIT_FAILURE);
    }

    // Closing file
    fclose(file);
}
