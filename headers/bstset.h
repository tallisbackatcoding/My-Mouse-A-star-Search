#include <stdio.h>
#include <stdlib.h>

typedef struct NodeBST_t{
    int value;
    int key;
    int height;
    struct NodeBST_t *left;
    struct NodeBST_t *right;
    struct NodeBST_t *parent;
}NodeBST;

typedef struct bstSet{
    int size;
    NodeBST *head;
    NodeBST *minNode;
}bstSet;

void freeNodeBST(NodeBST* NodeBST);

//binary tree with Set in each NodeBST
NodeBST *newNodeBST(int key, int value);
int height(NodeBST *NodeBST);
int max(int a, int b);
NodeBST *rightRotate(NodeBST *y);
NodeBST *leftRotate(NodeBST *x);
int getBalance(NodeBST *N);
NodeBST** find( NodeBST** n, int key, int value );
NodeBST *checkBalance(NodeBST *NodeBST, int value);
NodeBST* insert(bstSet *Set, NodeBST* NodeBST, int key, int value);
NodeBST* removeRightMost( NodeBST** from );
int removeFromTree(bstSet *Set, int key, int value);
void printTree(NodeBST * head);
bstSet *getNewBstSet();
void addToBstSet(bstSet *Set, int key, int value);
int removeFromBstSet(bstSet *Set, int key, int value);
void printBstSet(bstSet *Set);
void freeBstSet(bstSet *Set);
int *getMinFromBstSet(bstSet *Set);

