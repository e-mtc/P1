typedef struct
{
    int x; // x-coordinate of mine
    int y; // y-coordinate of mine
    double tw; // Terrain-weight (coefficient) at mine location
    int minenumber;
} mine_s;

double **structTo2D(mine_s bombs[], int bombAmount);
double calculateDistance(mine_s bomb1, mine_s bomb2);






void christofides(mine_s bombs[], int bombamount);