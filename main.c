#include "jogo.h"

void printOpcoes();

int main() {
    char* filename = "cacaPalavra.txt";
    char* palavras_filename = "palavras.txt";
    int largura = -1;
    int altura = -1;

    // Carregar matriz
    char** matriz = carregarCacaPalavras(filename, &altura, &largura);
    if (matriz == NULL) {
        printf("Erro ao carregar a matriz de caça-palavras.\n");
        return 1;
    }
    
    // Criar e popular o Trie
    TrieAvlNode* raiz = NULL;

    carregarPalavras(palavras_filename, &raiz);

    // Criar avl
    AvlNode* avl = NULL;
    encontrarPalavrasNaMatriz(matriz, altura, largura, raiz, &avl);


    int escolha = -1;
    while (escolha != 0) {
        printOpcoes();
        scanf("%d", &escolha);
        switch (escolha) {
            case 0:
                break;
            case 1:
                imprimirMatriz(matriz, altura);
                break;
            case 2:
                printf("Palavras na trie:\n");
                printTrie(raiz, "", 0);
                break;
            case 3:
                printf("Palavras encontradas:\n");
                printInOrder(avl);
                break;
            case 4:
                printf("Digite a palavra que deseja excluir: ");
                char palavra[100];
                scanf("%s", palavra);
                char normalizada[100];
                normalizarString(palavra, normalizada);
                avl = delete(avl, normalizada);
                printf("palavra %s excluída\n", normalizada);
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }
    liberarMatriz(matriz, altura);
    liberarTrie(raiz);
    freeTree(avl);
    return 0;
}

void printOpcoes() {
    printf("Escolha uma opção:\n");
    printf("0 - Sair\n");
    printf("1 - Mostrar matriz\n");
    printf("2 - Mostrar palavras na trie\n");
    printf("3 - Mostrar palavras na avl (palavras encontradas)\n");
    printf("4 - Excluir palavra da avl\n");
    printf("Opção: ");
}
