#ifndef SCANCORDS_H
#define SCANCORDS_H
// Struct for mines
// Add index for mines (like a number unique to each mine)
typedef struct
{
    unsigned x; // x-coordinate of mine
    unsigned y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
    int mineNumber; // Mine number on creation - Used to identify mine in functions
    int edgeAmount; // Edges in created tree MST
} mine_s;

// Function to count no. mines
unsigned int countMines(char*filenavn);

// Function to read in the mines and their tw's into array of type mine_s
void coordinatesScanInit(mine_s* mines, unsigned int mineCount,  char* filenavn);
#endif
