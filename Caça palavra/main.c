#include "jogo.h"


int main() {
    char* filename = "cacaPalavra.txt";
    char* words_filename = "palavras.txt";
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
    trienode* root = NULL;

    carregarPalavras(words_filename, &root);
    //PRINT TRIE:
    printf("arvore atual:\n");
    printTries(root, "", 0);

    Node* avl = NULL;
    encontrarPalavrasNaTrie(matriz, altura, largura, root, &avl);

    printf("Palavras encontradas (em AVL):\n");
    Inorder(avl);

    liberarMatriz(matriz, dimensao);
    liberarTrie(root);
    FreeTree(avl);
    return 0;
}
