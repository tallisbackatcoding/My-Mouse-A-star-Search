#ifndef BIT_FIELD_H_INCLUDED
#define BIT_FIELD_H_INCLUDED
#include <stdint.h>
#include "../headers/stack.h"
#include "../headers/queue.h"

typedef struct{
    int32_t *field;
}bitField;


bitField *getNewBitField(int size);
void copyToBitFieldFromStr(bitField *bf, char *str, int strSize, int bitsIndex, char info_string[], queue *entries, queue* exits);
void SetBit(bitField *bf, int k);
void ClearBit(bitField *bf, int k);
int TestBit(bitField *bf, int k);
void Set2Bits(bitField *bf, int k, int value /*from 0 to 3 */);
int Test2Bits(bitField *bf, int k);
void freeBitField(bitField *bf);
void printBitField(bitField *bf, int rows, int columns, char str_info[], int start, queue *path, queue *exits);
#endif
