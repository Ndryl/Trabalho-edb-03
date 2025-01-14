CC = gcc
CFLAGS = -Wall -g
EXEC = jogo

$(EXEC): main.c jogo.c avl.c trie.c
	$(CC) $(CFLAGS) main.c jogo.c avl.c trie.c -o $(EXEC)

clean:
	rm -f $(EXEC)