CC=gcc
CFLAGS=-Wall -Wextra -ggdb -Iinclude
LIBS=-Llib -lraylib -lm

game: src/game.c src/sprite.c include/sprite.h
	$(CC) src/game.c src/sprite.c -o game $(CFLAGS) $(LIBS)
