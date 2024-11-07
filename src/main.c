#include "LowBoundTSP.h"

int main(void){

    int paths = 5;


    int test[][VALUES] = {   { 0, 1, 10 },
                       { 0, 2, 6 },
                       { 0, 3, 5 },
                       { 1, 3, 15 },
                       { 2, 3, 4 } };



    christofidesTSP(paths, test);


    return 0;
}
