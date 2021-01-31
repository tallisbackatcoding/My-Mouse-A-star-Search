#include <stdlib.h>
#include <stdio.h>
#include "../headers/set.h"

#define INT_MAX  2147483646

set *getNewSet(int capacity){
    set *newset = malloc(sizeof(set));
    newset->array = malloc(sizeof(Node)*capacity);
    for(int i = 0; i < capacity; i++){
        newset->array[i] = NULL;
    }
    newset->capacity = capacity;
    newset->size = 0;
    return newset;
}

void freeNode(Node *node){
    if(node==NULL){
        return;
    }
    freeNode(node->next);
    free(node);
    node = NULL;
}

void freeSet(set *set){
    for(int i = 0; i < set->capacity; i++){
        if(set->array[i]){
            freeNode(set->array[i]);
        }
    }
    free(set->array);
    free(set);
}

size_t getHashSet(int value){
   size_t hash = 0;
   while(value){
       hash = hash*19 + value%10;
       value /= 10;
   }
   return hash;
}

void resizeSet(set *Set){
    set *newSet = getNewSet(Set->capacity * 2);
    for(int i = 0; i < Set->capacity; i++){
        Node *currentNode = Set->array[i];
        while(currentNode){
            addToSet(newSet, currentNode->value);
            currentNode = currentNode->next;
        }
        freeNode(Set->array[i]);
    }
    free(Set->array);
    *Set = *newSet;
    free(newSet);
    //puts("SETTTTTTTTTTTT\n");
}

void addToSet(set *set, int value){
    int index = getHashSet(value)%set->capacity;
    if(set->array[index] == NULL){
        set->array[index] = malloc(sizeof(Node));
        set->array[index]->value = value;
        set->array[index]->next = NULL;
    }else{
        Node *currentNode = set->array[index];
        if(currentNode->value == value){
            return;
        }
        while(currentNode->next){
            if(currentNode->value == value){
                return;
            }
            currentNode = currentNode->next;
        }
        currentNode->next = malloc(sizeof(Node));
        currentNode->next->value = value;
        currentNode->next->next = NULL;
    }
    set->size++;
    if((float)set->size/set->capacity >= 2){
        resizeSet(set);
    }
}

int removeFromSet(set *Set, int value){
    size_t index = getHashSet(value)%Set->capacity;
    Node *currentNode = Set->array[index];
    if(currentNode && currentNode->value == value){
        Set->array[index] = currentNode->next;
        free(currentNode);
        Set->size--;
        return 1;
    }
    while(currentNode && currentNode->next){
        if(currentNode->next->value == value){
            Node *temp = currentNode->next;
            currentNode->next = currentNode->next->next;
            free(temp);
            Set->size--;
            return 1;
        }
        currentNode = currentNode->next;
    }
    return 0;
}

int setContains(set *set, int value){
    size_t index = getHashSet(value)%set->capacity;
    Node *currentNode = set->array[index];
    while(currentNode){
        if(currentNode->value == value){
            return 1;
        }
        currentNode = currentNode->next;
    }
    return 0;
}

void printSet(set *set){
    for(int i = 0; i < set->capacity; i++){
        printf("%d: ", i);
        Node *currentNode = set->array[i];
        while(currentNode){
            printf("%d ", currentNode->value);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}
