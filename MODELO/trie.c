#include <stdio.h>    // Para funções de entrada/saída, como printf
#include <string.h>   // Para manipulação de strings, como strlen e memcpy
#include <stdbool.h>  // Para o tipo bool
#include <stdlib.h>   // Para alocação de memória, como malloc

#define NUM_CHARS 26  // Número de letras do alfabeto (somente minúsculas)

typedef struct trienode {
    struct trienode *children[NUM_CHARS];  // Array de ponteiros para os filhos, representando cada letra
    bool terminal;                        // Indica se o nó é o final de uma palavra (true) ou não (false)
} trienode;

// Função para criar um novo nó na trie
trienode *createnode() {
    // Aloca memória para um novo nó
    trienode *newnode = malloc(sizeof(*newnode));
    
    // Inicializa todos os filhos como NULL
    for (int i = 0; i < NUM_CHARS; i++) {
        newnode->children[i] = NULL;
    }
    
    // Marca o nó como não-terminal inicialmente
    newnode->terminal = false;
    return newnode;
}

/*
 * Função: trieinsert
 * Parâmetros:
 * - root: Ponteiro para o ponteiro da raiz da trie.
 * - word: Palavra a ser inserida na trie.
 * Retorno:
 * - true se a palavra foi inserida com sucesso.
 * - false se a palavra já estava na trie.
 *
 * Descrição:
 * Insere uma palavra na trie. Cria novos nós conforme necessário.
 * Retorna false se a palavra já existir.
 */
bool trieinsert(trienode **root, char *word) {
    if (*root == NULL) {
        *root = createnode();  // Cria a raiz se ainda não existir
    }

    unsigned char *text = (unsigned char *)word;  // Cast para manipulação de caracteres
    trienode *current = *root;                    // Começa na raiz
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        int index = text[i] - 'a';  // Calcula o índice da letra atual ('a' = 0, 'b' = 1, ..., 'z' = 25)

        if (index < 0 || index >= NUM_CHARS) {
            printf("Palavra contém caracteres inválidos: %s\n", word);
            return false; // Retorna false para palavras com caracteres fora do alfabeto
        }

        // Cria um novo nó se não existir
        if (current->children[index] == NULL) {
            current->children[index] = createnode();
        }

        // Avança para o próximo nó na trie
        current = current->children[index];
    }

    // Se já era terminal, significa que a palavra já existe
    if (current->terminal) {
        return false;
    } else {
        // Marca como terminal para indicar o final da palavra
        current->terminal = true;
        return true;
    }
}

/*
 * Função: printTries
 * Parâmetros:
 * - root: Raiz ou subárvore da trie para começar a impressão.
 * - prefix: Prefixo acumulado para formar palavras.
 * - length: Tamanho do prefixo atual.
 *
 * Descrição:
 * Percorre a trie recursivamente e imprime todas as palavras armazenadas.
 */
void printTries(trienode *root, char *prefix, int length) {
    if (root == NULL) return;  // Se o nó é nulo, retorna

    char newprefix[length + 2];      // Buffer para armazenar o novo prefixo
    memcpy(newprefix, prefix, length); // Copia o prefixo atual
    newprefix[length] = '\0';        // Adiciona o terminador de string

    if (root->terminal) {
        printf("%s\n", newprefix);  // Imprime o prefixo se for uma palavra completa
    }

    // Itera sobre todos os filhos do nó atual
    for (int i = 0; i < NUM_CHARS; i++) {
        if (root->children[i] != NULL) {
            // Adiciona a letra correspondente ao prefixo
            newprefix[length] = 'a' + i;
            printTries(root->children[i], newprefix, length + 1); // Chamada recursiva
        }
    }
}

/*
 * Função: main
 * Descrição:
 * Testa as funções de inserção e impressão da trie. Insere um conjunto de palavras
 * e imprime todas as palavras armazenadas.
 */
int main() {
    trienode *root = NULL;  // Inicializa a raiz da trie

    // Palavras para teste
    char *words[] = {"cat", "car", "cart", "dog", "dove", "door"};
    int numWords = sizeof(words) / sizeof(words[0]);

    printf("Inserindo palavras na trie:\n");
    for (int i = 0; i < numWords; i++) {
        if (trieinsert(&root, words[i])) {
            printf("Palavra '%s' inserida com sucesso.\n", words[i]);
        } else {
            printf("Palavra '%s' já existe.\n", words[i]);
        }
    }

    printf("\nPalavras armazenadas na trie:\n");
    printTries(root, "", 0);

    return 0;
}
