CC=gcc
CFLAGS=-Wall -Wextra -ggdb -Iinclude
LIBS=-Llib -lraylib -lm
SOURCES=src/*.c

game: $(SOURCES)
	$(CC) $(SOURCES) -o game $(CFLAGS) $(LIBS)
