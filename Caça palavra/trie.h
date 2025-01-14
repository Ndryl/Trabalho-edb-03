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
bool trieinsert(TrieNode **root, char *word);
void printTries(TrieNode *root, char *prefix, int length);
bool trieSearch(TrieNode *root, const char *word);
void liberarTrie(TrieNode *root);
TrieNode* buscarNo(TrieNode *root, const char *word);

#endif