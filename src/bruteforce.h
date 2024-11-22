#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include "scanCords.h"

/*
 * @param minefield: the array of mines that are on the minefield
 * @param arraySize: amount of miens on the minefield
 * @return the array with the shortest path through the minefield
 */
mine_s *getShortestPath(mine_s *minefield, unsigned int arraySize);

/*
 * @param shrt: the array that holds the current shortest path
 * @param minefield: the array of mines that are on the minefield
 * @param path: the current path
 * @param depth: the current amount steps (depth) that has been chosen
 * @param arraySize: the amount of mines
 */
void findShortestPath(mine_s *shrt, mine_s *minefield, mine_s *path, unsigned int depth, unsigned int arraySize);

/*
 * @param path       array of mines in path
 * @param arraySize  amount of mines in path
 * @return length of path (double)
 */
double pathLength(const mine_s *path, unsigned int arraySize);

/*
 * @param mine1 & mine2   the mines to find the distance between 
 * @return the distance between two mines
 */
double calculateLength(mine_s mine1, mine_s mine2);

/*
 * @param number  the number to do the factorial calculation on
 * @return factorial of the input number
 */
unsigned int factorial(unsigned int number); 

#endif
