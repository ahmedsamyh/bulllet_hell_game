
CC=gcc
CFLAGS=-Wall -Wextra -ggdb -Iinclude
LIBS=-Llib -lraylib -lm

game: src/game.c src/thing.c
	$(CC) src/game.c src/thing.c -o game $(CFLAGS) $(LIBS)
