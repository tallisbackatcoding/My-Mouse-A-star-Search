#include "../headers/bstset.h"

void freeNodeBST(NodeBST* NodeBST){
    if(!NodeBST){
        return;
    }
    freeNodeBST(NodeBST->left);
    freeNodeBST(NodeBST->right);
    free(NodeBST);
}

//binary tree with Set in each NodeBST
NodeBST *newNodeBST(int key, int value){
    NodeBST* Node = malloc(sizeof(NodeBST));
    if(!Node){
        return NULL;
    }
    Node->key = key;
    Node->value = value;
    Node->right = NULL;
    Node->parent = NULL;
    Node->left = NULL;
    Node->height = 1;
    return Node;
}

int height(NodeBST *NodeBST)
{
    if (NodeBST == NULL)
        return 0;
    return NodeBST->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

NodeBST *rightRotate(NodeBST *y)
{
    NodeBST *x = y->left;
    if(!x){
        return y;
    }
    NodeBST *T2 = x->right;

    
    x->right = y;
    y->left = T2;

    if(T2){
        T2->parent = y;
    }
    y->parent = x;

    x->parent = NULL;

    
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    
    return x;
}

NodeBST *leftRotate(NodeBST *x)
{
    NodeBST *y = x->right;
    if(!y){
        return x;
    }
    NodeBST *T2 = y->left;

    
    y->left = x;
    x->right = T2;

    x->parent = y;
    if(T2){
        T2->parent = x;
    }

    y->parent = NULL;
    
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    
    return y;
}

int getBalance(NodeBST *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

NodeBST** find( NodeBST** n, int key, int value )
{

    if((*n) == NULL)
    {
        return n;
    }
    else if((*n)->value == value && (*n)->key == key)
    {
        return n;
    }else if((*n)->value == value){
        return find(&((*n)->left), key, value);
    }
    else if(value < (*n)->value)
    {
        return find(&((*n)->left), key, value);
    }
    else
    {
        return find(&((*n)->right), key, value);
    }
}


NodeBST* insert(bstSet *Set, NodeBST* Node, int key, int value)
{
    
    if (Node == NULL){
        
        NodeBST *newNode = newNodeBST(key, value);
        if(Set->minNode == NULL){
            Set->minNode = newNode;
        }else{
            if( (Set->minNode)->value > newNode->value){
                Set->minNode = newNode;
            }
        }
        return newNode;
    }
    else if (value < Node->value){
        Node->left  = insert(Set, Node->left, key, value);
        Node->left->parent = Node;
    }
    else if (value > Node->value){
        Node->right = insert(Set, Node->right, key, value);
        Node->right->parent = Node;
    }
    else{
        if(Node->key == key && Node->value == value){
            return Node;
        }
        Node->right = insert(Set, Node->right, key, value);
    }

    Node->height = 1 + max(height(Node->left),
                           height(Node->right));
    int balance = getBalance(Node);

    if (balance > 1 && value < Node->left->value){

        return rightRotate(Node);
    }

    if (balance < -1 && value > Node->right->value){
        return leftRotate(Node);
    }

    if (balance > 1 && value > Node->left->value)
    {
        Node->left =  leftRotate(Node->left);
        return rightRotate(Node);
    }

    if (balance < -1 && value < Node->right->value)
    {
        Node->right = rightRotate(Node->right);
        return leftRotate(Node);
    }

    return Node;
}

NodeBST* removeRightMost( NodeBST** from )
{
    if((*from)->right == NULL)
    {
        return *from;
    }
    return removeRightMost(&((*from)->right));
}

void updateMinNode(bstSet *Set);

int removeFromTree(bstSet *Set, int key, int value)
{
    NodeBST **del = find(&(Set->head), key, value);
    if((*del) == NULL)
    {
        return 0;
    }

    if((*del)->left == NULL && (*del)->right == NULL)
    {
        updateMinNode(Set);
        free(*del);
        *del = NULL;
        return 1;
    }
    else if((*del)->left == NULL)
    {
        updateMinNode(Set);
        NodeBST *tempParent = (*del)->parent;
        NodeBST *temp = *del;
        *del = (*del)->right;
        (*del)->parent = tempParent;
        free(temp);
        temp = NULL;
        return 1;
    }
    else if((*del)->right == NULL)
    {
        updateMinNode(Set);
        NodeBST *temp = *del;
        NodeBST *tempParent = (*del)->parent;
        *del = (*del)->left;
        (*del)->parent = tempParent;
        free(temp);
        temp = NULL;
        return 1;
    }
    else
    {
        NodeBST *right = removeRightMost(&((*del)->left));
        int temp_key   = right -> key;
        int temp_value = right -> value;
        removeFromTree(Set, temp_key, temp_value);
        (*del)->key = temp_key;
        (*del)->value = temp_value;
        return 1;
    }
    return 1;
}


void updateMinNode(bstSet *Set){
    
    if(!Set->head || !Set->minNode){
        return;
    }
    if(Set->minNode->right){
        NodeBST *currentNode = Set->minNode->right;
        if(!currentNode->left){
            Set->minNode = currentNode;
        }else{
            while(currentNode->left){
                currentNode = currentNode->left;
            }
            Set->minNode = currentNode;
        }
    }else{
        if(Set->minNode->parent){
            Set->minNode = Set->minNode->parent;
        }
        else{
            Set->minNode = NULL;
        }
    }
}

void printTree(NodeBST * head) {
    if(head == NULL)
        return;
    printTree(head->left);
    printf("%d ", head->key);
    printf("%d, ", head->value);
    printTree(head->right);
}

bstSet *getNewBstSet(){
    bstSet *newSet = malloc(sizeof(bstSet));
    newSet->head = NULL;
    newSet->size = 0;
    newSet->minNode = NULL;
    return newSet;
}

void addToBstSet(bstSet *Set, int key, int value){
    Set->head = insert(Set, Set->head, key, value);
}

int removeFromBstSet(bstSet *Set, int key, int value){
    return removeFromTree(Set, key, value);
}

void printBstSet(bstSet *Set){
    printTree(Set->head);
}

void freeBstSet(bstSet *Set){
    freeNodeBST(Set->head);
    free(Set);
}


int *getMinFromBstSet(bstSet *Set){
    
    int *pair = malloc(sizeof(int)*2);
    pair[0] = Set->minNode->key;
    pair[1] = Set->minNode->value;
    return pair;
    NodeBST *currentNodeBST = Set->head;
    if(!currentNodeBST){
        return NULL;
    }
    if(!(currentNodeBST->left)){
        int *result = malloc(sizeof(int)*2);
        result[0] = currentNodeBST->key;
        result[1] = currentNodeBST->value;
        return result;
    }
    while(currentNodeBST->left){
        currentNodeBST = currentNodeBST->left;
    }
    int *result = malloc(sizeof(int)*2);
    result[0] = currentNodeBST->key;
    result[1] = currentNodeBST->value;
    return result;
}

