#include "../headers/stack.h"

stack* getNewStack(size_t capacity){
    stack* newStack = malloc(sizeof(stack));
    newStack->array = malloc(sizeof(int) * capacity);
    newStack->size = 0;
    newStack->capacity = capacity;
    return newStack;
}

void freeStack(stack *stck){
    free(stck->array);
    free(stck);
}

bool isEmpty(stack *s){
    return s->size == 0;
}

void doubleCapacity(stack* s){
    stack *tempStack = getNewStack(s->capacity);
    for(size_t i = 0; i < s->size; i++){
        tempStack->array[i] =  s->array[i];
        tempStack->size++;
    }

    free(s->array);
    s->array = malloc(sizeof(int)*tempStack->capacity*2);
    s->capacity = tempStack->capacity*2;
    s->size = 0;

    for(size_t i = 0; i < tempStack->size; i++){
        s->array[i] = tempStack->array[i];
        s->size++;
    }
    freeStack(tempStack);
}

void push(stack *s, int ch){
    if(s->size == s->capacity){
        doubleCapacity(s);
    }
    s->array[s->size] = ch;
    s->size++;
}

int pop(stack *s){
    if(!isEmpty(s)){
        int ch = s->array[s->size-1];
        s->size--;
        return ch;
    }
    return -1;
}

int peek(stack *s){
    if(!isEmpty(s)){
        return s->array[s->size-1];
    }
    return -1;
}

void printStack(stack *s){
    for(size_t i = 0; i < s->size; i++){
        printf("%d", s->array[i]);
        if(i != s->size - 1){
            printf(", ");
        }
    }
    printf("\n");
}
