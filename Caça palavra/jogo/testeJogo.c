#include "jogo.h"


int main() {
    // Exemplo de matriz fixa para testar a função findWord
    int dimensao = 5;
    char* matriz[5] = {
        "EXEMP",
        "EXAMP",
        "MPLAE",
        "PEMLO",
        "LOEXM"
    };
        char* matrizDois[5] = {
        "OXEMP",
        "EAAMP",
        "MPIAE",
        "PEMVO",
        "LOEXA"
    };
    
    

    // Palavra a ser procurada
    const char* palavra = "EXEMPLO"; // Troque para qualquer palavra que deseja buscar
      const char* palavraDois = "AVIAO";

    // Testa a função findWord
    if (findWord(matriz, dimensao, palavra)) {
        printf("A palavra '%s' foi encontrada!\n", palavra);
    } else {
        printf("A palavra '%s' não foi encontrada.\n", palavra);
    }
     if (findWord(matrizDois, dimensao, palavraDois)) {
        printf("A palavra '%s' foi encontrada!\n", palavraDois);
    } else {
        printf("A palavra '%s' não foi encontrada.\n", palavraDois);
    }


    return 0;
}
