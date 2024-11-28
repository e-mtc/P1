#ifndef VISUALOUTPUT_H
#define VISUALOUTPUT_H

#include "scanCords.h"

// Rasmus' version
void visualOutput(int row, int column, const mine_s input[], unsigned int mineCount);

// Anas' version
void showMinefield(int row, int column, const mine_s input[], unsigned int mineCount);

void visualMinefieldSize(const mine_s input[], unsigned int *row, unsigned int *column, unsigned int mineCount);

#endif