#ifndef TRIE_H
#define TRIE_H
#include <stdio.h>    
#include <string.h>   
#include <stdbool.h>  
#include <stdlib.h>   
#include <ctype.h>
#define NUM_CHARS 26  

typedef struct TrieAvlNode {
    struct TrieAvlNode *children[NUM_CHARS];  // Array de ponteiros para os filhos, representando cada letra
    bool terminal;                        // Indica se o nó é o final de uma palavra (true) ou não (false)
} TrieAvlNode;
TrieAvlNode *createAvlNode();
bool trieinsert(TrieAvlNode **raiz, char *palavra);
void printTrie(TrieAvlNode *raiz, char *prefix, int comprimento);
bool trieSearch(TrieAvlNode *raiz, const char *palavra);
void liberarTrie(TrieAvlNode *raiz);
TrieAvlNode* buscarNo(TrieAvlNode *raiz, const char *palavra);

#endif