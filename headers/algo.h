#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED

#include "../headers/bit_field.h"
#include "../headers/queue.h"
#include "../headers/dict.h"
#include "../headers/set.h"

size_t heuristic(int start[], int end[]);
queue *getChildren(bitField *bf, int y, int x, int rows, int columns);
queue *myAstar(bitField *bf, int rows, int columns, char info_string[], int start[], int end[]);
#endif
