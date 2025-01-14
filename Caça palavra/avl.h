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


int AvlNodeHeight(AvlNode* p);
int BalanceFactor(AvlNode* p);
AvlNode* LLRotation(AvlNode* p);
AvlNode* RRRotation(AvlNode* p);
AvlNode* LRRotation(AvlNode* p);
AvlNode* RLRotation(AvlNode* p);
AvlNode* InPre(AvlNode* p);
AvlNode* InSucc(AvlNode* p);
AvlNode* rInsert(AvlNode* p, char* key, int start[], int end[]);
AvlNode* Delete(AvlNode* p, char* key);
void Inorder(AvlNode* p);
void FreeTree(AvlNode* p);

#endif 
