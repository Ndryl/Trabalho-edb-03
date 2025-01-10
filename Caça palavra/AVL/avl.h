#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nó da AVL
typedef struct Node {
    struct Node* lchild;
    char *word;
    struct Node* rchild;
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
Node* rInsert(Node* p, char* key);
Node* Delete(Node* p, char* key);
void Inorder(Node* p);
void FreeTree(Node* p);

#endif // AVL_H
