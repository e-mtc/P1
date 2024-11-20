#ifndef SCANCORDS_H
#define SCANCORDS_H
// Struct for mines
// Add index for mines (like a number unique to each mine)
typedef struct {
    unsigned int x;
    unsigned int y;
} mine_s;

void coordinatesScanInit(mine_s* mines, char* filename);
#endif 
