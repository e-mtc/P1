#ifndef SCANCORDS_H
#define SCANCORDS_H
// Struct for mines
// Add index for mines (like a number unique to each mine)
typedef struct
{
    unsigned int x; // x-coordinate of mine
    unsigned int y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
} mine_s;

// Function to count no. mines
int countMines(char*filenavn);

// Function to read in the mines and their tw's into array of type mine_s
void coordinatesScanInit(mine_s* mines, int mineCount,  char* filenavn);
#endif
