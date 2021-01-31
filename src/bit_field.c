#include <stdlib.h>
#include <stdio.h>
#include "../headers/bit_field.h"

bitField* getNewBitField(int size){
    bitField *newBitField = malloc(sizeof(bitField));

    //we are using 32bit ints and allocate 2 times more bits since we need 2 of them for every cell
    int arraySize = size/32 + 1;
    newBitField->field = malloc(sizeof(int)*arraySize);
    printf("array size %d \n", arraySize);
    return newBitField;
}

void SetBit(bitField *bf, int k){
     (bf->field[(k/32)] |= (1 << (k%32)));
}

void ClearBit(bitField *bf, int k){
    bf->field[(k/32)] &= ~(1 << (k%32)) ;
}

int TestBit(bitField *bf, int k){
    return bf->field[(k/32)] & (1 << (k%32));
}

void copyToBitFieldFromStr(bitField *bf, char *str, int strSize, int bitsIndex, char info_string[], queue *entries, queue* exits){
    char full, empty, entry, exit;
    full  = info_string[0];
    empty = info_string[1];
    entry = info_string[2];
    exit  = info_string[3];

    for(int i = 0; i < strSize; i++){
        int k = bitsIndex+i;
        if(str[i] == full){
            SetBit(bf, k);
        }else if(str[i] == entry){
            pushQueue(entries, k);
            SetBit(bf, k);
        }else if(str[i] == exit){
            pushQueue(exits, k);
            ClearBit(bf, k);
        }else if(str[i] == empty){
            ClearBit(bf, k);
        }
    }
}

void printBitField(bitField *bf, int rows, int columns, char info_string[], int start, queue *path, queue *exits){
    char full, empty, entry, exit, character;
    full       = info_string[0];
    empty      = info_string[1];
    entry      = info_string[2];
    exit       = info_string[3];
    character  = info_string[4];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            int k = columns*i + j;
            int testBit = TestBit(bf, k);
            if(k == peekQueue(exits)){
                printf("%c", exit);
                popQueue(exits);
            }
            else if(k == peekQueue(path)){
                printf("%c", character);
                popQueue(path);
            }
            else if(start == k){
                printf("%c", entry);
            }else if(testBit){
                printf("%c", full);
            }else if(!testBit){
                printf("%c", empty);
            }
        }
        printf("\n");
    }
}

void freeBitField(bitField *bf){
    free(bf->field);
    free(bf);
}

