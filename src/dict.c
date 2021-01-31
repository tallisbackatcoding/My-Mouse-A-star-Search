#include <stdlib.h>
#include <stdio.h>
#include "dict.h"

#define INT_MIN -2147483648
#define INT_MAX  2147483647

dict *getNewDict(int capacity){
    dict *newDict = malloc(sizeof(dict));
    newDict->array = malloc(sizeof(Pair)*capacity);
    for(int i = 0; i < capacity; i++){
        newDict->array[i] = NULL;
    }
    newDict->capacity = capacity;
    newDict->size = 0;
    return newDict;
}

void freePair(Pair *head){
    if(head==NULL){
        return;
    }
    freePair(head->next);
    free(head);
    head = NULL;
}

void freeDict(dict *Dict){
    for(int i = 0; i < Dict->capacity; i++){
        if(Dict->array[i]){
            freePair(Dict->array[i]);
        }
    }
    free(Dict->array);
    free(Dict);
}

size_t getHash(int value){
    size_t hash = 0;
    while(value){
        hash = hash*19 + value%10;
        value /= 10;
    }
    return hash;
}

void resizeDict(dict *Dict){
    dict *newDict = getNewDict(Dict->capacity * 2);
    for(int i = 0; i < Dict->capacity; i++){
        Pair *currentPair = Dict->array[i];
        while(currentPair){
            addToDict(newDict, currentPair->first, currentPair->second);
            currentPair = currentPair->next;
        }
        freePair(Dict->array[i]);
    }
    free(Dict->array);
    *Dict = *newDict;
    free(newDict);
    //puts("DICTTTTTTTTTTTTTTTTTTTT\n");
}

int addToDict(dict *Dict, int key, int value){
    int index = getHash(key)%Dict->capacity;
    if(Dict->array[index] == NULL){
        Dict->array[index] = malloc(sizeof(Pair));
        Dict->array[index]->first = key;
        Dict->array[index]->second = value;
        Dict->array[index]->next = NULL;

    }else{

        Pair *currentPair = Dict->array[index];
        while(currentPair->next){
            if(currentPair->first == key){
                currentPair->second = value;
                return 1;
            }
            currentPair = currentPair->next;
        }
        if(currentPair->first == key){
            currentPair->second = value;
            return 1;
        }
        currentPair->next = malloc(sizeof(Pair));
        currentPair->next->first = key;
        currentPair->next->second = value;
        currentPair->next->next = NULL;

    }
    Dict->size++;
    if((float)Dict->size/Dict->capacity >= 2){
        resizeDict(Dict);
    }
    return 1;
}

int dictContains(dict *Dict, int key){
    size_t index = getHash(key)%Dict->capacity;
    Pair *currentPair = Dict->array[index];
    while(currentPair){
        if(currentPair->first == key){
            return 1;
        }
        currentPair = currentPair->next;
    }
    return 0;
}

int getValueFromDict(dict *Dict, int key){
    size_t index = getHash(key)%Dict->capacity;
    Pair *currentPair = Dict->array[index];
    while(currentPair){
        if(currentPair->first == key){
            return currentPair->second;
        }
        currentPair = currentPair->next;
    }
    return INT_MAX;
}

int removeFromDict(dict *Dict, int key){
    size_t index = getHash(key)%Dict->capacity;
    Pair *currentPair = Dict->array[index];
    if(currentPair && currentPair->first == key){
        Dict->array[index] = currentPair->next;
        free(currentPair);
        Dict->size--;
        return 1;
    }
    while(currentPair && currentPair->next){
        if(currentPair->next->first == key){
            Pair *temp = currentPair->next;
            currentPair->next = currentPair->next->next;
            free(temp);
            Dict->size--;
            return 1;
        }
        currentPair = currentPair->next;
    }
    return 0;
}

void printDict(dict *Dict){
    for(int i = 0; i < Dict->capacity; i++){
        printf("%d: ", i);
        Pair *currentPair = Dict->array[i];
        while(currentPair){
            printf("{%d: ", currentPair->first);
            printf("%d} ", currentPair->second);
            currentPair = currentPair->next;
        }
        printf("\n");
    }
}
