#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _POSIX_SOURCE
#include <unistd.h>
#include "scanCords.h"


// MANUAL:
// 1. Declare and initialise array of type mine_s.
// 2. Create string (char array) containing name of .txt file with coordinates. E.g. "coordinates.txt."
// 3. Pass elements (from step 1 & 2) into coordinatesScanInit().





void coordinatesScanInit(mine_s* mines, char* filename)
{
    // Adding a path specifier "../" to filename

    char filepath[256];
    getcwd(filepath, sizeof(filepath));
    if (getcwd(filepath, sizeof(filepath)) == NULL)
    {
        perror("Error: cwd");
        exit(EXIT_FAILURE);
    }
    printf("Dir1: %s\n",filepath);

    chdir("..");
    printf("Dir2: %s\n",filepath);

    sprintf(filepath, "%s\\src\\%s", filepath, filename);
    printf("Dir3: %s\n",filepath);

    // Declaring and initialising file pointer
    FILE* file = fopen(filepath, "r");

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
        if ((c == '\n') && (isdigit(fgetc(file)))) { mineQuantity++; }
        c = fgetc(file);
    }

    // Mine count, adding 1 because not actual coordinates are counted, but number of newlines.
    mineQuantity += 1;
    printf("Antal: %d\n", mineQuantity);

    rewind(file); // Resets the position indicator to the start of the file
    for (int i = 0; i < mineQuantity; ++i)
    {
        // Printing error if misinput is detected.
        if (!isdigit(fgetc(file)) && (fgetc(file) != '\n'))
        {
            fseek(file, -2, SEEK_CUR);
            fprintf(stderr, "Error: Invalid input scanned at position %d\n", ftell(file));
            exit(EXIT_FAILURE);
        }
        fseek(file, -1, SEEK_CUR);

        // Scanning the coordinates
        fscanf(file, "%d %d", &mines[i].x, &mines[i].y);
        printf("%d and %d\n", mines[i].x, mines[i].y);
        fseek(file, 2, SEEK_CUR);
    }

    // Checking if last coordinate entry is a valid digit
    fseek(file, -3, SEEK_CUR);
    if (!isdigit(fgetc(file)))
    {
        fseek(file, -1, SEEK_CUR);
        fprintf(stderr, "Error: Invalid input scanned at position %d\n", ftell(file));
        exit(EXIT_FAILURE);
    }

    // Closing file
    fclose(file);
}
