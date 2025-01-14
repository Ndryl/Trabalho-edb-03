#ifndef TRIE_H
#define TRIE_H
#include <stdio.h>    
#include <string.h>   
#include <stdbool.h>  
#include <stdlib.h>   
#include <ctype.h>
#define NUM_CHARS 26  

typedef struct TrieNode {
    struct TrieNode *children[NUM_CHARS];  // Array de ponteiros para os filhos, representando cada letra
    bool terminal;                        // Indica se o nó é o final de uma palavra (true) ou não (false)
} TrieNode;
TrieNode *createnode();
bool trieinsert(TrieNode **raiz, char *palavra);
void printTrie(TrieNode *raiz, char *prefix, int comprimento);
bool trieSearch(TrieNode *raiz, const char *palavra);
void liberarTrie(TrieNode *raiz);
TrieNode* buscarNo(TrieNode *raiz, const char *palavra);

#endif