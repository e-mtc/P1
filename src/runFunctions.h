#ifndef RUNFUNCTIONS_H
#define RUNFUNCTIONS_H

#include "scanCords.h"
#define MAX_STR_LNGTH 30


void run();
void getFilename(char filename[MAX_STR_LNGTH]);
void scanCords (unsigned int *row, unsigned int *column, unsigned int *mineCount, mine_s minefield[], char filename[MAX_STR_LNGTH]);
void initiateBruteforce(unsigned int row, unsigned int column, unsigned int mineCount, double *bruteLength, double *cpuTimeUsedBrute, mine_s minefield[mineCount]);
void initiateChristofides(unsigned int row, unsigned int column, unsigned int mineCount, double *christoLength, double *cpuTimeUsedChristo, mine_s minefield[mineCount], mine_s minefieldChristo[mineCount]);
void compareAlgorithms(double bruteLength, double christoLength, double cpuTimeUsedBrute, double cpuTimeUsedChristo);

#endif // RUNFUNCTIONS_H
