#ifndef JOGO_H
#define JOGO_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "avl.h"
#include "trie.h"


char** carregarCacaPalavras(char* filename, int* altura, int* largura);
void carregarPalavras(char* filename, TrieAvlNode **raiz);
void liberarMatriz(char** matriz, int linhas);
void imprimirMatriz(char** matriz, int dimensao);
void normalizarString(const char* origem, char* destino);

void encontrarPalavrasNaMatriz(char **matriz, int altura, int largura, TrieAvlNode *raiz, AvlNode **avl);
void buscarPalavrasEmUmaDirecao(char **matriz, int largura, int altura, int x, int y, int dx, int dy, 
                          TrieAvlNode *no, char *buffer, int profundidade, AvlNode **avl, int start[]);

#endif
