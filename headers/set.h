#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#include <stddef.h>

typedef struct LinkedList{
    int value;
    struct LinkedList *next;
}Node;

typedef struct {
    int size;
    int capacity;
    Node **array;
}set;

set *getNewSet(int capacity);
void freeNode(Node *node);
void freeSet(set *Set);
size_t getHashSet(int value);
void resizeSet(set *Set);
void addToSet(set *Set, int value);
int removeFromSet(set *Set, int value);
int setContains(set *Set, int value);
void printSet(set *Set);

#endif
