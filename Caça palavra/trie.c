#include "trie.h"

TrieNode *createnode() {
    TrieNode *newnode = malloc(sizeof(*newnode));
    for (int i = 0; i < NUM_CHARS; i++) {
        newnode->children[i] = NULL;
    }
    

    newnode->terminal = false;
    return newnode;
}
void normalizar_string(const char* origem, char* destino) {
    const char* acentuados = "áàâãäéèêëíìîïóòôõöúùûüçÁÀÂÃÄÉÈÊËÍÌÎÏÓÒÔÕÖÚÙÛÜÇ";
    const char* nao_acentuados = "AAAAAEEEEIIIIOOOOOUUUUCAAAAAEEEEIIIIOOOOOUUUUC";

    int i, j;
    for (i = 0, j = 0; origem[i] != '\0'; i++) {
        char c = origem[i];
        const char* p = strchr(acentuados, c);
        if (p) {
            destino[j++] = toupper(nao_acentuados[p - acentuados]);
        } else {
            destino[j++] = toupper(c);
        }
    }
    destino[j] = '\0';  // Termina a string
}



bool trieinsert(TrieNode **raiz, char *palavra) {
    if (*raiz == NULL) {
        *raiz = createnode();  
    }

    char normalizada[100];  // Buffer para armazenar a palavra normalizada
    normalizar_string(palavra, normalizada);  // Normalizar a palavra (caps e sem acento)

    unsigned char *text = (unsigned char *)normalizada;  
    TrieNode *current = *raiz;                    
    int comprimento = strlen(normalizada);

    for (int i = 0; i < comprimento; i++) {
        int index = text[i] - 'A';  // Índice baseado em letras maiúsculas (A-Z)

        if (index < 0 || index >= NUM_CHARS) {
            printf("Palavra contém caracteres inválidos: %s\n", normalizada);
            return false; 
        }

        if (current->children[index] == NULL) {
            current->children[index] = createnode();
        }

        current = current->children[index];
    }

    if (current->terminal) {
        return false;  // Palavra já estava no trie
    } else {
        current->terminal = true;  // Marca a palavra como terminal
        return true;
    }
}


bool trieSearch(TrieNode *raiz, const char *palavra) {
    if (raiz == NULL) {
        return false;
    }

    TrieNode *current = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int index = palavra[i] - 'a';

        if (index < 0 || index >= NUM_CHARS || current->children[index] == NULL) {
            return false;
        }

        current = current->children[index];
    }

    return current->terminal;
}

void printTries(TrieNode *raiz, char *prefix, int comprimento) {
    if (raiz == NULL) return;  

    char newprefix[comprimento + 2];    
    memcpy(newprefix, prefix, comprimento); 
    newprefix[comprimento] = '\0';  

    if (raiz->terminal) {
        printf("%s\n", newprefix); 
    }

   
    for (int i = 0; i < NUM_CHARS; i++) {
        if (raiz->children[i] != NULL) {
         
            newprefix[comprimento] = 'A' + i;
            printTries(raiz->children[i], newprefix, comprimento + 1); 
        }
    }
}
void liberarTrie(TrieNode *raiz) {
    if (raiz == NULL) return;

    for (int i = 0; i < NUM_CHARS; i++) {
        liberarTrie(raiz->children[i]);
    }
    free(raiz);
}
TrieNode* buscarNo(TrieNode *raiz, const char *palavra) {
    if (raiz == NULL) {
        return NULL;
    }

    TrieNode *current = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int index = toupper(palavra[i]) - 'A';
        if (index < 0 || index >= NUM_CHARS || current->children[index] == NULL) {
            return NULL;
        }
        current = current->children[index];
    }
    return current;
}
