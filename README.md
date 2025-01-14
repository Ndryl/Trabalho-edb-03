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
- **main.c**: Arquivo principal para rodar o programa.
- **avl.c**: Implementação da árvore AVL.
- **trie.c**: Implementação da Trie.
- **cacaPalavra.txt**: Exemplo de arquivo com a matriz de caça-palavra.
- **palavras**: Exemplo de arquivo com palavras a serem buscadas na matriz.

### Funções principais

As funções utilizadas no projeto incluem:

1. **carregarCacaPalavras**:
   - Carrega o arquivo de texto e transforma as linhas em uma matriz de caracteres (strings), validando o formato e garantindo que a matriz seja quadrada.
   
2. **normalizar_string**:
   - Remove acentuação das letras e as converte para maiúsculas.

3. **encontrarPalavrasNaMatriz**:
   - Procurar as palavras na matriz e inserir na árvore AVL.

4. **carregarPalavras**:
   - Carrega o arquivo de texto com as palavras e insere na Trie.

### Como executar:

1. Compile o código com o comando:

    ```bash
    make
    ```

2. Execute o programa:

    ```bash
    ./jogo
    ```


