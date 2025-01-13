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

void verificarDirecaoTrie(char **matriz, int largura, int altura, int x, int y, int dx, int dy, trienode *no, char *buffer, int profundidade, char **resultado, int *resultadoCount) {
    if (no->terminal) {
        buffer[profundidade] = '\0';
        // Verifica se a palavra já está nos resultados
        bool encontrada = false;
        for (int i = 0; i < *resultadoCount; i++) {
            if (strcmp(resultado[i], buffer) == 0) {
                encontrada = true;
                break;
            }
        }
        if (!encontrada) {
            resultado[*resultadoCount] = strdup(buffer);
            (*resultadoCount)++;
        }
    }

    if (x < 0 || x >= altura || y < 0 || y >= largura) {
        return;
    }

    int index = matriz[x][y] - 'A';
    if (no->children[index]) {
        buffer[profundidade] = matriz[x][y];
        verificarDirecaoTrie(matriz, largura, altura, x + dx, y + dy, dx, dy, no->children[index], buffer, profundidade + 1, resultado, resultadoCount);
    }
}

// Função principal para encontrar palavras da Trie no caça-palavras
// Por enquanto, não adiciona em uma avl, apenas retorna um array de strings de palavras encontradas
char **encontrarPalavrasNaTrie(char **matriz, int largura, int altura, trienode *raiz, int *quantidadePalavras) {
    // Vetores para as 8 direções possíveis
    int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

    char buffer[altura * largura + 1];

    // Array de resultados
    char **resultado = (char **)malloc(altura * largura * sizeof(char *));
    *quantidadePalavras = 0;

    for (int x = 0; x < altura; x++) {
        for (int y = 0; y < largura; y++) {
            for (int d = 0; d < 8; d++) {
                verificarDirecaoTrie(matriz, largura, altura, x, y, dx[d], dy[d], raiz, buffer, 0, resultado, quantidadePalavras);
            }
        }
    }

    return resultado;
}
