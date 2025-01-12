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

    char* palavras_inserir[] = {"PAO", "AVIAO", "CRIA", "OVA"};
    for (int i = 0; i < 4; i++) {
        normalizarString(palavras_inserir[i], palavra_normalizada);
        trieinsert(&root, palavra_normalizada);
        printf("Palavra '%s' inserida no Trie.\n", palavras_inserir[i]);
    }

    // Verificar palavras na matriz
    printf("\nVerificando palavras na matriz...\n");
    char* palavras[] = {"CASA", "CARRO", "ÁRVORE", "GATO", "PAO", "AVIAO", "CRIA", "OVA"};
    int num_palavras = sizeof(palavras) / sizeof(palavras[0]);

    for (int i = 0; i < num_palavras; i++) {
        normalizarString(palavras[i], palavra_normalizada);
        if (findWord(matriz, dimensao, buscarNo(root, palavra_normalizada))) {
            printf("Palavra '%s' encontrada.\n", palavras[i]);
        } else {
            printf("Palavra '%s' NÃO encontrada.\n", palavras[i]);
        }
    }

    // Liberar memória
    liberarTrie(root);
    liberarMatriz(matriz, dimensao);

    return 0;
}
