#include "trie.h"

trienode *createnode() {
    trienode *newnode = malloc(sizeof(*newnode));
    for (int i = 0; i < NUM_CHARS; i++) {
        newnode->children[i] = NULL;
    }
    

    newnode->terminal = false;
    return newnode;
}


bool trieinsert(trienode **root, char *word) {
    if (*root == NULL) {
        *root = createnode();  
    }

    unsigned char *text = (unsigned char *)word;  
    trienode *current = *root;                    
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        int index = text[i] - 'a';  

        if (index < 0 || index >= NUM_CHARS) {
            printf("Palavra contém caracteres inválidos: %s\n", word);
            return false; 
        }

      
        if (current->children[index] == NULL) {
            current->children[index] = createnode();
        }

        
        current = current->children[index];
    }

    if (current->terminal) {
        return false;
    } else {

        current->terminal = true;
        return true;
    }
}


void printTries(trienode *root, char *prefix, int length) {
    if (root == NULL) return;  

    char newprefix[length + 2];    
    memcpy(newprefix, prefix, length); 
    newprefix[length] = '\0';  

    if (root->terminal) {
        printf("%s\n", newprefix); 
    }

   
    for (int i = 0; i < NUM_CHARS; i++) {
        if (root->children[i] != NULL) {
         
            newprefix[length] = 'a' + i;
            printTries(root->children[i], newprefix, length + 1); 
        }
    }
}