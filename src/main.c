#include "LowBoundTSP.h"

int main(void){

    int paths = 13;


    int test[][VALUES] = {   {1, 2, 1},
                       {1, 6, 9},
                       {1, 7, 7},
                       {2, 3, 2},
                       {2, 6, 6},
                       {3, 4, 4},
                       {3, 6, 5},
                       {4, 7, 12},
                       {5, 6, 2},
                       {5, 7, 15},
                       {5, 8, 6},
                       {6, 7, 3},
                       {6, 8, 4}};



    christofidesTSP(paths, test);


    return 0;
}
