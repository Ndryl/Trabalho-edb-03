#ifndef JOGO_H
#define JOGO_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../trie/trie.h"

char** carregarCacaPalavras(char* filename, int* dimensao);
void liberarMatriz(char** matriz, int linhas);
void imprimirMatriz(char** matriz, int dimensao);
bool contemSubstring(const char *str, const char *sub);
bool findWord(char** matriz, int dimensao, trienode* root);
bool buscarPalavra(char** matriz, int dimensao, int x, int y, trienode* node, bool** visitado) ;
void normalizarString(const char* origem, char* destino);

bool isValid(int x, int y, int dimensao, bool** visitado);

#endif
