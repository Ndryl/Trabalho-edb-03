#ifndef JOGO_H
#define JOGO_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char** carregarCacaPalavras(char* filename, int* dimensao);
void normalizar_string(const char* origem, char* destino);
void liberarMatriz(char** matriz, int linhas);
void imprimirMatriz(char** matriz, int dimensao);
bool contemSubstring(const char *str, const char *sub);
bool findWord(char **matriz, int dimensao, const char *sub);

#endif
