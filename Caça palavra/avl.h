#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nó da AVL
typedef struct AvlNode {
    char *palavra;
    int start[2];  // Coordenadas de início [x, y]
    int end[2];    // Coordenadas de fim [x, y]
    struct AvlNode *lchild;
    struct AvlNode *rchild;
    int height;
} AvlNode;


int avlNodeHeight(AvlNode* p);
int balanceFactor(AvlNode* p);
AvlNode* LLRotation(AvlNode* p);
AvlNode* RRRotation(AvlNode* p);
AvlNode* LRRotation(AvlNode* p);
AvlNode* RLRotation(AvlNode* p);
AvlNode* inPre(AvlNode* p);
AvlNode* InSucc(AvlNode* p);
AvlNode* rInsert(AvlNode* p, char* key, int start[], int end[]);
AvlNode* delete(AvlNode* p, char* key);
void printInOrder(AvlNode* p);
void freeTree(AvlNode* p);

#endif 
