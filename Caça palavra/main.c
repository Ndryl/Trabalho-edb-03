#include "jogo.h"


int main() {
    char* filename = "cacaPalavra.txt";
    char* palavras_filename = "palavras.txt";
    int dimensao = 0;
    int largura = -1;
    int altura = -1;

    // Carregar matriz
    printf("Carregando a matriz de caça-palavras...\n");
    char** matriz = carregarCacaPalavras(filename, &altura, &largura);
    if (matriz == NULL) {
        printf("Erro ao carregar a matriz de caça-palavras.\n");
        return 1;
    }
    printf("Matriz de dimensão %dx%d carregada com sucesso!\n", altura, largura);
    imprimirMatriz(matriz, dimensao);
    
    // Criar e popular o Trie
    printf("Criando o Trie com palavras...\n");
    TrieNode* raiz = NULL;

    carregarPalavras(palavras_filename, &raiz);
    //PRINT TRIE:
    printf("arvore atual:\n");
    printTrie(raiz, "", 0);

    Node* avl = NULL;
    encontrarPalavrasNaTrie(matriz, altura, largura, raiz, &avl);

    printf("Palavras encontradas (em AVL):\n");
    Inorder(avl);

    liberarMatriz(matriz, dimensao);
    liberarTrie(raiz);
    FreeTree(avl);
    return 0;
}
