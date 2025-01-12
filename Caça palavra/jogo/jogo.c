#include "jogo.h"


void normalizarString(const char* origem, char* destino) {
    
    const char* acentuados = "áàâãäéèêëíìîïóòôõöúùûüçÁÀÂÃÄÉÈÊËÍÌÎÏÓÒÔÕÖÚÙÛÜÇ";
    const char* nao_acentuados = "aaaaaeeeeiiiiooooouuuucAAAAAEEEEIIIIOOOOOUUUUC";

    int i, j;
    for (i = 0, j = 0; origem[i] != '\0'; i++) {
        char c = origem[i];
        const char* p = strchr(acentuados, c);
        if (p) {
            // Substitui o caractere acentuado pelo correspondente sem acento
            destino[j++] = toupper(nao_acentuados[p - acentuados]);
        } else {
            // Converte para maiúscula
            destino[j++] = toupper(c);
        }
    }
    destino[j] = '\0'; // Termina a string
}
void strrev(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
bool contemSubstring(const char *str, const char *sub) {
    return strstr(str, sub) != NULL; // Retorna true se encontrar a substring
}
char** carregarCacaPalavras(char* filename, int* dimensao) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    char buffer[1030];
    char** matriz = NULL;
    int num_linhas = 0;
    int max_colunas = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove o '\n' do final da linha
        buffer[strcspn(buffer, "\n")] = '\0';

        int len = strlen(buffer);
        if (num_linhas == 0) {
            max_colunas = len; // Define o número de colunas na primeira linha
        }

        // Verifica se o comprimento das linhas é consistente
        if (len != max_colunas) {
            printf("Caça-palavras formato errado\n");
            fclose(file);
            liberarMatriz(matriz, num_linhas);
            return NULL;
        }

        // Aloca memória para armazenar a linha na matriz
        matriz = realloc(matriz, sizeof(char*) * (num_linhas + 1));
        if (matriz == NULL) {
            printf("Erro ao alocar memória\n");
            fclose(file);
            liberarMatriz(matriz, num_linhas);
            return NULL;
        }

        matriz[num_linhas] = malloc((len + 1) * sizeof(char));
        if (matriz[num_linhas] == NULL) {
            printf("Erro ao alocar memória\n");
            fclose(file);
            liberarMatriz(matriz, num_linhas);
            return NULL;
        }

        // Normaliza e copia a linha para a matriz
        normalizarString(buffer, matriz[num_linhas]);

        num_linhas++;
    }

    fclose(file);

    // Verifica se o número de linhas é igual ao número de colunas
    if (num_linhas != max_colunas) {
        printf("Caça-palavras formato errado\n");
        liberarMatriz(matriz, num_linhas);
        return NULL;
    }

    *dimensao = num_linhas; // Define a dimensão para o chamador
    return matriz;
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

bool isValid(int x, int y, int dimensao, bool** visitado) {
    return x >= 0 && x < dimensao && y >= 0 && y < dimensao && !visitado[x][y];
}

// Busca recursiva a partir de uma célula
bool buscarPalavra(char** matriz, int dimensao, int x, int y, trienode* node, bool** visitado) {
    if (node == NULL) {
        return false;
    }

    if (node->terminal) {
        return true;
    }

    if (!isValid(x, y, dimensao, visitado)) {
        return false;
    }

    int index = matriz[x][y] - 'A';
    if (node->children[index] == NULL) {
        return false;
    }

    visitado[x][y] = true;

    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        if (buscarPalavra(matriz, dimensao, x + dx[i], y + dy[i], node->children[index], visitado)) {
            return true;
        }
    }

    visitado[x][y] = false; // Marca como não visitado para outras buscas
    return false;
}


// Função principal para verificar se a palavra existe na matriz
bool findWord(char** matriz, int dimensao, trienode* root) {
    bool** visitado = (bool**)malloc(dimensao * sizeof(bool*));
    for (int i = 0; i < dimensao; i++) {
        visitado[i] = (bool*)calloc(dimensao, sizeof(bool));
    }

    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (buscarPalavra(matriz, dimensao, i, j, root, visitado)) {
                for (int k = 0; k < dimensao; k++) {
                    free(visitado[k]);
                }
                free(visitado);
                return true;
            }
        }
    }

    for (int i = 0; i < dimensao; i++) {
        free(visitado[i]);
    }
    free(visitado);
    return false;
}





