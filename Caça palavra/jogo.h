#ifndef JOGO_H
#define JOGO_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "trie.h"

char** carregarCacaPalavras(char* filename, int* altura, int* largura);
void carregarPalavras(char* filename, trienode **root);
void liberarMatriz(char** matriz, int linhas);
void imprimirMatriz(char** matriz, int dimensao);
bool contemSubstring(const char *str, const char *sub);
void normalizarString(const char* origem, char* destino);

char **encontrarPalavrasNaTrie(char **matriz, int altura, int largura, trienode *raiz, int *quantidadePalavras);
void verificarDirecaoTrie(char **matriz, int largura, int altura, int x, int y, int dx, int dy, trienode *no, char *buffer, int profundidade, char **resultado, int *resultadoCount);

bool isValid(int x, int y, int dimensao, bool** visitado);

#endif
