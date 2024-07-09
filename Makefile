
CC=gcc
CFLAGS=-Wall -Wextra -ggdb -Iinclude
LIBS=-Llib -lraylib -lm

game: src/game.c
	$(CC) src/game.c -o game $(CFLAGS) $(LIBS)
