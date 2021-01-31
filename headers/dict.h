#ifndef DICT_H_INCLUDED
#define DICT_H_INCLUDED
#include <stddef.h>

typedef struct Pair_LL{
    int first;
    int second;
    struct Pair_LL *next;
}Pair;

typedef struct {
    int size;
    int capacity;
    Pair **array;
}dict;

dict *getNewDict(int capacity);
void freePair(Pair *pair);
void freeDict(dict *Dict);
size_t getHash(int key);
void resizeDict(dict *Dict);
int addToDict(dict *Dict, int key, int value);
int dictContains(dict *Dict, int key);
int getValueFromDict(dict *Dict, int key);
int removeFromDict(dict *Dict, int key);
void printDict(dict *Dict);

#endif
