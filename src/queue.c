#include "queue.h"
#define INT_MAX 2147483647

queue* getNewQueue(size_t capacity){
    queue* newqueue = malloc(sizeof(queue));
    newqueue->array = malloc(sizeof(int) * capacity);
    newqueue->size = 0;
    newqueue->start = 0;
    newqueue->capacity = capacity;
    return newqueue;
}

void freeQueue(queue *q){
    free(q->array);
    free(q);
}

bool isEmptyQueue(queue *q){
    if(!q){
        return 1;
    }
    return q->size == 0;
}

void doubleCapacityQueue(queue* q){
    queue *newQueue = getNewQueue(q->capacity*2);
    size_t j = 0;
    for(size_t i = q->start; i < q->size + q->start; i++, j++){
        newQueue->array[j] =  q->array[i%q->capacity];
        newQueue->size++;
    }
    free(q->array);
    *q = *newQueue;
    free(newQueue);
}

void pushQueue(queue *q, int ch){
    if(q->size == q->capacity){
        doubleCapacityQueue(q);
    }
    q->array[(q->size+q->start)%q->capacity] = ch;
    q->size++;
}

int popQueue(queue *q){
    if(!isEmptyQueue(q)){
        int ch = q->array[q->start];
        q->size--;
        q->start = (q->start + 1)%q->capacity;
        return ch;
    }
    return INT_MAX;
}

int peekQueue(queue *q){
    if(!isEmptyQueue(q)){
        return q->array[q->start];
    }
    return INT_MAX;
}

void reverseQueue(queue *toReverse){
    queue *tempQueue = getNewQueue(toReverse->capacity);
    int len = toReverse->size;
    for(int i = 0; i < len; i++){
        tempQueue->array[i] = toReverse->array[i];
    }
    for(int i = 0; i < len; i++){
        toReverse->array[i] = tempQueue->array[len - i - 1];
    }
    freeQueue(tempQueue);
}

queue *copyQueue(queue *from){
    queue *to = getNewQueue(from->capacity);
    for(int i = 0; i < from->capacity; i++){
        to->array[i] = from->array[i];
    }
    to->size = from->size;
    to->start = from->start;
    return to;
}

void printQueue(queue *q){
    for(size_t i = q->start; i < q->size+q->start; i++){
        printf("%d", q->array[i%q->capacity]);
        if(i != q->size+q->start - 1){
            printf(", ");
        }
    }
    printf("\n");
}
int partition(queue *Q, int first, int last)
{
    int pivot = first;
    int up = first, down = last;
    while (up < down){
        while (Q->array[up] <= Q->array[pivot] && up < last){
            up++;
        }
        while (Q->array[down] > Q->array[pivot]){
            down--;
        }
        if (up < down){
            int temp = Q->array[up];
            Q->array[up] = Q->array[down];
            Q->array[down] = temp;
        }

    }
    int temp2 = Q->array[pivot];
    Q->array[pivot] = Q->array[down];
    Q->array[down]  = temp2;
    return down;
}
void sortQueue(queue *Q, int first, int last)
{
    if (first < last){
        int pivIndex = partition(Q, first, last);
        sortQueue(Q, first, pivIndex-1);
        sortQueue(Q, pivIndex+1, last);
    }
}
