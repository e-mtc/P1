// Struct for mines
// Add index for mines (like a number unique to each mine)
typedef struct
{
    unsigned int x;
    unsigned int y;
} mine_s;

int countMines(char*filenavn);

void coordinatesScanInit(mine_s* mines, int mineCount,  char* filenavn);
