# Repositório de Jogo de Caça-Palavras

Este repositório contém a implementação de um jogo de **Caça-Palavras** em C, com funções que permitem carregar uma matriz de palavras, normalizar as strings, imprimir a matriz, e realizar a busca por palavras tanto em linhas quanto em colunas, diagonais e em seus inversos.

## Funcionalidades

As principais funcionalidades incluem:

- **Carregar a matriz de caça-palavras** a partir de um arquivo de texto.
- **Normalizar as palavras** removendo acentuação e convertendo todas as letras para maiúsculas.
- **Buscar palavras** em diversas orientações: horizontal, vertical, diagonal e reversa.
- **Liberação da memória** alocada dinamicamente para evitar vazamentos.

## Estrutura do Projeto

O projeto contém os seguintes arquivos principais:

- **jogo.c**: Implementação das funções principais do jogo.
- **testeJogo.c**: Arquivo de testes para verificar o funcionamento das funções.
- **caca_palavras.txt**: Exemplo de arquivo com a matriz de caça-palavras (se necessário para testes).

### Funções principais

As funções utilizadas no projeto incluem:

1. **carregarCacaPalavras**:
   - Carrega o arquivo de texto e transforma as linhas em uma matriz de caracteres (strings), validando o formato e garantindo que a matriz seja quadrada.
   
2. **normalizar_string**:
   - Remove acentuação das letras e as converte para maiúsculas.

3. **liberarMatriz**:
   - Libera a memória alocada para a matriz de caça-palavras.

4. **imprimirMatriz**:
   - Imprime a matriz de caça-palavras na tela para visualização.

5. **contemSubstring**:
   - Verifica se uma substring existe dentro de uma string.

6. **findWord**:
   - Busca uma palavra na matriz em várias direções (horizontal, vertical, diagonal, e reversa).

## Teste Básico

O arquivo `testeJogo.c` contém um teste básico para verificar o funcionamento das funções principais, em especial a busca de palavras na matriz.

### Como executar:

1. Compile o código com o comando:

    ```bash
    gcc jogo.c testeJogo.c -o testeJogo
    ```

2. Execute o programa:

    ```bash
    ./testeJogo
    ```

### Exemplo de saída:

```bash
Matriz de Caça-Palavras:
EXEMP
EXAMP
MPLAE
PEMLO
LOEXM

A palavra 'EXEMPLO' foi encontrada!
