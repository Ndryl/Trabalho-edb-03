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



bool trieinsert(TrieNode **root, char *word) {
    if (*root == NULL) {
        *root = createnode();  
    }

    char normalizada[100];  // Buffer para armazenar a palavra normalizada
    normalizar_string(word, normalizada);  // Normalizar a palavra (caps e sem acento)

    unsigned char *text = (unsigned char *)normalizada;  
    TrieNode *current = *root;                    
    int length = strlen(normalizada);

    for (int i = 0; i < length; i++) {
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


bool trieSearch(TrieNode *root, const char *word) {
    if (root == NULL) {
        return false;
    }

    TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (index < 0 || index >= NUM_CHARS || current->children[index] == NULL) {
            return false;
        }

        current = current->children[index];
    }

    return current->terminal;
}

void printTries(TrieNode *root, char *prefix, int length) {
    if (root == NULL) return;  

    char newprefix[length + 2];    
    memcpy(newprefix, prefix, length); 
    newprefix[length] = '\0';  

    if (root->terminal) {
        printf("%s\n", newprefix); 
    }

   
    for (int i = 0; i < NUM_CHARS; i++) {
        if (root->children[i] != NULL) {
         
            newprefix[length] = 'A' + i;
            printTries(root->children[i], newprefix, length + 1); 
        }
    }
}
void liberarTrie(TrieNode *root) {
    if (root == NULL) return;

    for (int i = 0; i < NUM_CHARS; i++) {
        liberarTrie(root->children[i]);
    }
    free(root);
}
TrieNode* buscarNo(TrieNode *root, const char *word) {
    if (root == NULL) {
        return NULL;
    }

    TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = toupper(word[i]) - 'A';
        if (index < 0 || index >= NUM_CHARS || current->children[index] == NULL) {
            return NULL;
        }
        current = current->children[index];
    }
    return current;
}
