#include "jogo.h"


int main() {
    char* filename = "cacaPalavra.txt";
    int dimensao = 0;

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
    char palavra_normalizada[100];

    char* palavras_inserir[] = {"PAO", "AVIAO", "CRIA", "OVA", "teste", "oicio"};
    int tam = 6;
    for (int i = 0; i < tam; i++) {
        normalizarString(palavras_inserir[i], palavra_normalizada);
        trieinsert(&root, palavra_normalizada);
        printf("Palavra '%s' inserida no Trie.\n", palavra_normalizada);
    }

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
