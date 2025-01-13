#include "jogo.h"


int main() {
    char* filename = "cacaPalavra.txt";
    char* words_filename = "palavras.txt";
    int dimensao = 0;
    int largura = -1;
    int altura = 01;

    // Carregar matriz
    printf("Carregando a matriz de caça-palavras...\n");
    char** matriz = carregarCacaPalavras(filename, &dimensao);
    if (matriz == NULL) {
        printf("Erro ao carregar a matriz de caça-palavras.\n");
        return 1;
    }
    printf("Matriz de dimensão %dx%d carregada com sucesso!\n", dimensao, dimensao);
    imprimirMatriz(matriz, dimensao);
    
    // Criar e popular o Trie
    printf("Criando o Trie com palavras...\n");
    trienode* root = NULL;

    carregarPalavras(words_filename, &root);
    //PRINT TRIE:
    printf("arvore atual:\n");
    printTries(root, "", 0);

    int quantidadePalavras = 5;
    char** palavras_econtradas = encontrarPalavrasNaTrie(matriz, 5, 5, root, &quantidadePalavras);
    printf("Quantidade de palavras encontradas: %d\n", quantidadePalavras);
    for(int i = 0; i < quantidadePalavras; i++) {
        printf("%s ENCONTRADA\n", palavras_econtradas[i]);
    }

    liberarMatriz(matriz, dimensao);
    liberarTrie(root);

    for(int i = 0; i < quantidadePalavras; i++) {
        free(palavras_econtradas[i]);
    }

    free(palavras_econtradas);
    return 0;
}
