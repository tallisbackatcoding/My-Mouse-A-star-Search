#ifndef MY_QUEUE_H_INCLUDED
#define MY_QUEUE_H_INCLUDED
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    size_t start;
    size_t size;
    size_t capacity;
    int *array;
}queue;

queue* getNewQueue(size_t capacity);
void freeQueue(queue *s);
bool isEmptyQueue(queue *s);
void doubleCapacityQueue(queue* s);
void pushQueue(queue *s, int ch);
int popQueue(queue *s);
int peekQueue(queue *s);
void reverseQueue(queue *toReverse);
queue *copyQueue(queue *from);
void printQueue(queue *s);
int partition(queue *Q, int first, int last);
void sortQueue(queue *Q, int first, int last);


#endif
