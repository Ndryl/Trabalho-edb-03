#include "jogo.h"


void normalizarString(const char* origem, char* destino) {
    const char* acentuados = "áàâãäéèêëíìîïóòôõöúùûüçÁÀÂÃÄÉÈÊËÍÌÎÏÓÒÔÕÖÚÙÛÜÇ";
    const char* nao_acentuados = "aaaaaeeeeiiiiooooouuuucAAAAAEEEEIIIIOOOOOUUUUC";

    int i, j;
    for (i = 0, j = 0; origem[i] != '\0'; i++) {
        char c = origem[i];
        const char* p = strchr(acentuados, c);
        if (p) {
            destino[j++] = nao_acentuados[p - acentuados];
        } else if (isalpha(c)) {
            destino[j++] = toupper(c);  // Converte para maiúscula
        }
    }
    destino[j] = '\0';  // Finaliza a string
}

char** carregarCacaPalavras(char* filename, int* altura, int* largura) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    // Lê a altura e largura da primeira linha do arquivo
    if (fscanf(file, "%d %d\n", altura, largura) != 2) {
        printf("Erro ao ler altura e largura do arquivo\n");
        fclose(file);
        return NULL;
    }

    char buffer[1030];
    char** matriz = NULL;
    int num_linhas = 0;

    // Lê o restante das linhas do arquivo
    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove o '\n' do final da linha
        buffer[strcspn(buffer, "\n")] = '\0';

        // Remove espaços da linha
        char* linha_sem_espacos = malloc(strlen(buffer) + 1);
        if (linha_sem_espacos == NULL) {
            printf("Erro ao alocar memória\n");
            fclose(file);
            liberarMatriz(matriz, num_linhas);
            return NULL;
        }

        int j = 0;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] != ' ') {
                linha_sem_espacos[j++] = buffer[i];
            }
        }
        linha_sem_espacos[j] = '\0';

        int tamanho = strlen(linha_sem_espacos);

        // Aloca memória para armazenar a linha na matriz
        matriz = realloc(matriz, sizeof(char*) * (num_linhas + 1));
        if (matriz == NULL) {
            printf("Erro ao alocar memória\n");
            fclose(file);
            free(linha_sem_espacos);
            liberarMatriz(matriz, num_linhas);
            return NULL;
        }

        matriz[num_linhas] = malloc((tamanho + 1) * sizeof(char));
        if (matriz[num_linhas] == NULL) {
            printf("Erro ao alocar memória\n");
            fclose(file);
            free(linha_sem_espacos);
            liberarMatriz(matriz, num_linhas);
            return NULL;
        }

        // Copia a linha sem espaços para a matriz
        strcpy(matriz[num_linhas], linha_sem_espacos);

        free(linha_sem_espacos); // Libera a memória temporária
        num_linhas++;
    }

    fclose(file);

    return matriz;
}

void carregarPalavras(char* filename, trienode** root) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    char normalizada[100];
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // ignora espaços, tabs e quebras de linha entre as palavras
        char* word = strtok(line, " \t\n");
        while (word) {
            normalizarString(word, normalizada);
            trieinsert(root, normalizada);
            word = strtok(NULL, " \t\n"); 
        }
    }
}

void liberarMatriz(char** matriz, int linhas) {
    if (matriz) {
        for (int i = 0; i < linhas; i++) {
            free(matriz[i]);
        }
        free(matriz);
    }
}
void imprimirMatriz(char** matriz, int dimensao) {
    for (int i = 0; i < dimensao; i++) {
        printf("%s\n", matriz[i]);
    }
}

void verificarDirecaoTrie(char **matriz, int largura, int altura, int x, int y, int dx, int dy, 
                          trienode *no, char *buffer, int profundidade, Node **avl, int start[]) {
    //adiciona palavra encontrada na AVL
    if (no->terminal) {
        buffer[profundidade] = '\0';
        int end[2] = {x - dx, y - dy};
        *avl = rInsert(*avl, buffer, start, end);
    }
    //verifica se a posição é válida
    if (x < 0 || x >= altura || y < 0 || y >= largura) {
        return;
    }
    //continua a busca
    int index = matriz[x][y] - 'A';
    if (no->children[index]) {
        buffer[profundidade] = matriz[x][y];
        verificarDirecaoTrie(matriz, largura, altura, x + dx, y + dy, dx, dy, no->children[index], buffer, profundidade + 1, avl, start);
    }
}

//função principal para procurar palavras na matriz 
void encontrarPalavrasNaTrie(char **matriz, int altura, int largura, trienode *raiz, Node **avl) {
    //direções
    int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};
    char buffer[altura * largura + 1];

    //percorre todas as posições da matriz e procura por palavras
    for (int x = 0; x < altura; x++) {
        for (int y = 0; y < largura; y++) {
            for (int d = 0; d < 8; d++) {
                int start[2] = {x, y};
                verificarDirecaoTrie(matriz, largura, altura, x, y, dx[d], dy[d], raiz, buffer, 0, avl, start);
            }
        }
    }
}
