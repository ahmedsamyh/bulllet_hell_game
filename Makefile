CC=gcc
CFLAGS=-Wall -Wextra -ggdb -Iinclude -Wno-unused-variable -Wswitch-enum
LIBS=-Llib -lraylib -lm
SOURCES=src/*.c

game: $(SOURCES)
	$(CC) $(SOURCES) -o game $(CFLAGS) $(LIBS)
