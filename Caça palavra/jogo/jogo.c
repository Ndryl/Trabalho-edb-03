#include "jogo.h"


void normalizar_string(const char* origem, char* destino) {
    
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
        normalizar_string(buffer, matriz[num_linhas]);

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

bool findWord(char **matriz, int dimensao, const char *sub) {
    if (matriz == NULL || sub == NULL) {
        return false;
    }

    int sub_len = strlen(sub);

    // Verifica cada linha
    for (int i = 0; i < dimensao; i++) {
        if (contemSubstring(matriz[i], sub)) {
            return true;
        }

        char *inversa = malloc((strlen(matriz[i]) + 1) * sizeof(char));
        if (inversa == NULL) {
            printf("Erro ao alocar memória\n");
            return false;
        }
        strcpy(inversa, matriz[i]);
        strrev(inversa);  // Reverte a linha

        if (contemSubstring(inversa, sub)) {
            free(inversa);
            return true;
        }

        free(inversa);
    }

    // Verifica cada coluna
    for (int j = 0; j < dimensao; j++) {
        char *coluna = malloc((dimensao + 1) * sizeof(char));
        if (coluna == NULL) {
            printf("Erro ao alocar memória\n");
            return false;
        }

        for (int i = 0; i < dimensao; i++) {
            coluna[i] = matriz[i][j];
        }
        coluna[dimensao] = '\0';

        if (contemSubstring(coluna, sub)) {
            free(coluna);
            return true;
        }

        char *inversa = malloc((dimensao + 1) * sizeof(char));
        if (inversa == NULL) {
            printf("Erro ao alocar memória\n");
            return false;
        }
        strcpy(inversa, coluna);
        strrev(inversa);  // Reverte a coluna

        if (contemSubstring(inversa, sub)) {
            free(coluna);
            free(inversa);
            return true;
        }

        free(coluna);
        free(inversa);
    }

    // Diagonais principais
    for (int k = 0; k < dimensao; k++) {
        char diagonal[dimensao + 1];
        int idx = 0;

        // Diagonal iniciando em (k, 0)
        for (int i = k, j = 0; i < dimensao && j < dimensao; i++, j++) {
            diagonal[idx++] = matriz[i][j];
        }
        diagonal[idx] = '\0';
        if (contemSubstring(diagonal, sub)) {
            return true;
        }
        strrev(diagonal);
        if (contemSubstring(diagonal, sub)) {
            return true;
        }

        // Diagonal iniciando em (0, k)
        idx = 0;
        for (int i = 0, j = k; i < dimensao && j < dimensao; i++, j++) {
            diagonal[idx++] = matriz[i][j];
        }
        diagonal[idx] = '\0';
        if (contemSubstring(diagonal, sub)) {
            return true;
        }
        strrev(diagonal);
        if (contemSubstring(diagonal, sub)) {
            return true;
        }
    }

    // Diagonais secundárias
    for (int k = 0; k < dimensao; k++) {
        char diagonal[dimensao + 1];
        int idx = 0;

        // Diagonal iniciando em (k, dimensao-1)
        for (int i = k, j = dimensao - 1; i < dimensao && j >= 0; i++, j--) {
            diagonal[idx++] = matriz[i][j];
        }
        diagonal[idx] = '\0';
        if (contemSubstring(diagonal, sub)) {
            return true;
        }
        strrev(diagonal);
        if (contemSubstring(diagonal, sub)) {
            return true;
        }

        // Diagonal iniciando em (0, dimensao-1-k)
        idx = 0;
        for (int i = 0, j = dimensao - 1 - k; i < dimensao && j >= 0; i++, j--) {
            diagonal[idx++] = matriz[i][j];
        }
        diagonal[idx] = '\0';
        if (contemSubstring(diagonal, sub)) {
            return true;
        }
        strrev(diagonal);
        if (contemSubstring(diagonal, sub)) {
            return true;
        }
    }

    return false;
}





