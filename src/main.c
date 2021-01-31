#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "../headers/bit_field.h"
#include "../headers/algo.h"
#include "../headers/queue.h"

int intLength(int number){
    if(number == 0){
        return 1;
    }
    int i = 0;
    while(number){
        number /= 10;
        i++;
    }
    return i;
}

int parseInt(char *str){
    int number = 0;
    for(int i = 0; str[i]; i++){
        if(str[i] >= 48 && str[i] <= 57){
            number = number*10 + str[i] - 48;
        }else{
            return number;
        }
    }
    return -1;
}

void mazeGenerator(int rows, int columns){
    time_t t;
    srand((unsigned) time(&t));

    FILE *f = fopen("a.txt", "w");
    fprintf(f, "%dx%d* o12\n", rows, columns);
    int flag = 0;
    int flag1 = 1;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(i == 0){
                if(j > columns/2 && flag1){
                    putc('1', f);
                    flag1 = 0;
                }else{
                    putc('*', f);
                }
            }else if(i == 1 && j != 0 && j != columns-1){
                putc(' ', f);
            }
            else if(i == rows-2 && j != 0 && j != columns-1){
                putc(' ', f);
            }else if(j == 0){
                putc('*', f);
            }else if(i == rows-1){
                if(j > columns/3 &&(flag == 0 || (flag < 1 && rand()%100 > 95))){
                    putc('2', f);
                    flag++;
                }else{
                    putc('*', f);
                }

            }else if(j == columns-1){
                putc('*', f);
            }else{
                if(rand()%100 > 80){
                    putc('*', f);
                }else{
                    putc(' ', f);
                }
            }

        }
        putc('\n', f);
    }
    fclose(f);
}

int main()
{
    
    
    mazeGenerator(5000, 5000);
    int fd = open("a.txt", O_RDONLY);
    char *info     = my_readline(fd);
    int  rows      = parseInt(info);
    int  columns   = parseInt(info + intLength(rows) + 1);
    char full      = info[intLength(rows) + intLength(columns) + 1];
    char empty     = info[intLength(rows) + intLength(columns) + 2];
    char character = info[intLength(rows) + intLength(columns) + 3];
    char entry     = info[intLength(rows) + intLength(columns) + 4];
    char exit      = info[intLength(rows) + intLength(columns) + 5];
    free(info);
    //printf("%d%d%c%c%c%c%c\n", rows, columns, full, empty, character, entry, exit);

    char info_string[6];
    info_string[0] = full;
    info_string[1] = empty;
    info_string[2] = entry;
    info_string[3] = exit;
    info_string[4] = character;
    info_string[5] = 0;

    //reopening because lseek 'pointer' is not on second line
    close(fd);
    fd = open("a.txt", O_RDONLY);

    int index = intLength(rows) + intLength(columns) + 6;
    //reading exactly number of chars that are on 1st row (basically skipping first line because we already have info)
    char *stringLine = readWithSize(fd, index);

    free(stringLine);

    bitField *bf   = getNewBitField(columns*rows);

    queue *entries = getNewQueue(4);
    queue *exits   = getNewQueue(16);

    int bitsIndex  = 0;

    while(stringLine){
        stringLine = readWithSize(fd, columns);
        if(stringLine == NULL) break;
        copyToBitFieldFromStr(bf, stringLine, columns, bitsIndex, info_string, entries, exits);
        free(stringLine);
        bitsIndex += columns;
    }


    int start[] = {peekQueue(entries)/columns, peekQueue(entries)%columns};
    
    queue *finalPath = NULL;
    queue *currentPath = NULL;

    for(int i = 0; i < exits->size; i++){
        int end[] = {exits->array[i]/columns, exits->array[i]%columns};
        currentPath = myAstar(bf, rows, columns, info_string, start, end);
        if(!currentPath){
            continue;
        }
        printf("Path size:%ld\n", currentPath->size);
        //reverseQueue(currentPath);
        int len = currentPath->size;
        if(finalPath == NULL){
            finalPath = copyQueue(currentPath);
        }else if(len < finalPath->size){
            freeQueue(finalPath);
            finalPath = copyQueue(currentPath);
        }else if(len == finalPath->size){
            int currentPathExit = currentPath->array[len-1];
            int finalPathExit   = finalPath->array[len-1];
            if(currentPathExit%columns < finalPathExit%columns){
                freeQueue(finalPath);
                finalPath = copyQueue(currentPath);
            }
        }
        //
        
        //
        freeQueue(currentPath);
        //printf("im here\n");
    }
    sortQueue(exits, 0, exits->size - 1);
    if(!finalPath){
        printf("MAP ERROR\n");
        //printBitField(bf, rows, columns, info_string, peekQueue(entries), finalPath, exits);
    }else{
        sortQueue(finalPath, 0, finalPath->size-1);
        //printQueue(finalPath);
        //printBitField(bf, rows, columns, info_string, peekQueue(entries), finalPath, exits);
        freeQueue(finalPath);
    }
    freeBitField(bf);
    freeQueue(entries);
    freeQueue(exits);
    close(fd);
    return 0;
}
