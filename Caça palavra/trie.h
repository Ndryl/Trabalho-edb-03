#ifndef AVL_H
#define AVL_H
#include <stdio.h>    
#include <string.h>   
#include <stdbool.h>  
#include <stdlib.h>   
#include <ctype.h>
#define NUM_CHARS 26  

typedef struct trienode {
    struct trienode *children[NUM_CHARS];  // Array de ponteiros para os filhos, representando cada letra
    bool terminal;                        // Indica se o nó é o final de uma palavra (true) ou não (false)
} trienode;
trienode *createnode();
bool trieinsert(trienode **root, char *word);
void printTries(trienode *root, char *prefix, int length);
bool trieSearch(trienode *root, const char *word);
void liberarTrie(trienode *root);
trienode* buscarNo(trienode *root, const char *word);







#endif