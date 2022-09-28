CC = gcc

CFLAGS = -g -Wall -Wextra -std=c99 -ggdb3 -pedantic
LIBS = -lm -lSDL2

SRC = $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

DEPS = $(M_SRC:%=%.h)

all: bin libs bin/main

bin:
	mkdir -p ./$(BIN)

libs:

bin/main: $(OBJ)
	$(CC) -o $(BIN)/main $^ $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
