#include "../headers/algo.h"
#include "../headers/set.h"
#include "../headers/dict.h"
#include "../headers/queue.h"
#include "../headers/dict.h"
#include "../headers/set.h"
#include "../headers/bit_field.h"
#include "../headers/bstset.h"

#define INT_MIN -2147483648
#define INT_MAX  2147483647

size_t heuristic(int start[], int end[]){
    float x, y, x_end, y_end;
    x     = start[1];
    y     = start[0];
    x_end = end[1];
    y_end = end[0];
    
    int x_difference = x - x_end;
    int y_difference = y_end - y ;

    
    if(x_difference < 0){
        x_difference *= -1;
    }
    if(y_difference < 0){
        y_difference *= -1;
    }
    return x_difference + y_difference;
}
queue *myAstar(bitField *bf, int rows, int columns, char info_string[], int start[], int end[]){

    dict *pathCost  = getNewDict(rows*columns/10);  //G cost
    dict *totalCost = getNewDict(rows*columns/10);  //F cost or G cost + heuristics
    dict *parent    = getNewDict(rows);
    //I use as cordinates for example x[i][j] ~ x[i*columns + j]
    //Or to convert back to get 'i' I divide total index by columns and for j I take modulus of columns
    addToDict(pathCost,  start[0]*columns + start[1], 0);
    addToDict(totalCost, start[0]*columns + start[1], heuristic(start, end));

    set *expandedCells    = getNewSet(rows*columns/10);
    set *fringe           = getNewSet(rows*columns/10);
    bstSet *fringeBST     = getNewBstSet();        //this for much faster performance of cell with lowest F cost

    addToBstSet(fringeBST, start[0]*columns + start[1], heuristic(start, end));
    addToSet(fringe, start[0]*columns + start[1]);
    int iterations = 0;
    while( fringe->size ){
        int *pair = getMinFromBstSet(fringeBST);
        int currentCell = pair[0];
        removeFromBstSet(fringeBST, pair[0], pair[1]);
        removeFromSet(fringe, currentCell);
        free(pair);

        //if we reached the exit we trace back to obtain our path using parent dict
        if(currentCell == end[0]*columns + end[1]){
            queue *path = getNewQueue(columns*10);
            pushQueue(path, currentCell);
            while(dictContains(parent, currentCell)){
                int temp = currentCell;
                currentCell = getValueFromDict(parent, currentCell);
                removeFromDict(parent, temp);
                pushQueue(path, currentCell);
            }
            //printDict(totalCost);
            freeDict(pathCost);
            freeDict(totalCost);
            freeDict(parent);
            freeSet(expandedCells);
            freeSet(fringe);
            freeBstSet(fringeBST);
			printf("Iterations: %d\n", iterations);
            
            return path;
        }else{
            //else if expand current cell and observe and update its children
            addToSet(expandedCells, currentCell);
            int currentRow = currentCell/columns;
            int currentColumn = currentCell%columns;
            int neighbourCell;
            
            for(int i = 0; i < 4; i++){
                neighbourCell = -1;
                if(i == 0 && currentRow - 1 > -1){
                    neighbourCell = currentCell - columns;
                }else if(i == 1 && currentRow + 1 < rows){
                    neighbourCell = currentCell + columns;
                }else if(i == 2 && currentColumn + 1 < columns){
                    neighbourCell = currentCell + 1;
                }else if(i == 3 && currentColumn - 1 > -1){
                    neighbourCell = currentCell - 1;
                }
                if(TestBit(bf, neighbourCell)){
                    neighbourCell = - 1;
                }
                if(neighbourCell != -1){
                    int neighbourCellArr[] = {neighbourCell/columns, neighbourCell%columns};
                    int tentativeScore = getValueFromDict(pathCost, currentCell) + 1;
                    if(tentativeScore < getValueFromDict(pathCost, neighbourCell)){
                        addToDict(parent, neighbourCell, currentCell);
                        addToDict(pathCost, neighbourCell, tentativeScore);
                        addToDict(totalCost, neighbourCell, tentativeScore + heuristic(neighbourCellArr, end));
                        if(!setContains(fringe, neighbourCell)){
                            addToSet(fringe, neighbourCell);
                            addToBstSet(fringeBST, neighbourCell, tentativeScore + heuristic(neighbourCellArr, end));
                        }
                    }
                
                }
            }
        }
        iterations++;
    }
    //frees..
    freeDict(pathCost);
    freeDict(totalCost);
    freeDict(parent);
    freeSet(expandedCells);
    freeSet(fringe);
    freeBstSet(fringeBST);
    return NULL;
}
