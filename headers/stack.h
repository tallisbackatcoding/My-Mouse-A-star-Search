#ifndef MY_STACK_H_INCLUDED
#define MY_STACK_H_INCLUDED
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

typedef struct{
    size_t size;
    size_t capacity;
    int *array;
}stack;

stack* getNewStack(size_t capacity);
void freeStack(stack *s);
bool isEmpty(stack *s);
void doubleCapacity(stack* s);
void push(stack *s, int ch);
int pop(stack *s);
int peek(stack *s);
void printStack(stack *s);


#endif
