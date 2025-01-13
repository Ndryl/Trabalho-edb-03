#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nó da AVL
typedef struct Node {
    char *word;
    int start[2];  // Coordenadas de início [x, y]
    int end[2];    // Coordenadas de fim [x, y]
    struct Node *lchild;
    struct Node *rchild;
    int height;
} Node;

// Funções para manipulação da árvore AVL
int NodeHeight(Node* p);
int BalanceFactor(Node* p);
Node* LLRotation(Node* p);
Node* RRRotation(Node* p);
Node* LRRotation(Node* p);
Node* RLRotation(Node* p);
Node* InPre(Node* p);
Node* InSucc(Node* p);
Node* rInsert(Node* p, char* key, int start[], int end[]);
Node* Delete(Node* p, char* key);
void Inorder(Node* p);
void FreeTree(Node* p);

#endif // AVL_H
