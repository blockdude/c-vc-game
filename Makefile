CC = gcc

CFLAGS = -g -Wall -Wextra -std=c99 -ggdb3 -pedantic
LIBS = -lm -lSDL2

BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = obj

BIN = $(BIN_DIR)/main
SRC = $(patsubst $(SRC_DIR)/%,%,$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/**/**/*.c) $(wildcard $(SRC_DIR)/**/**/**/*.c))
DEP = $(patsubst $(SRC_DIR)/%,%,$(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/**/*.h) $(wildcard $(SRC_DIR)/**/**/*.h) $(wildcard $(SRC_DIR)/**/**/**/*.h))
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LIBS) -o $(BIN_DIR)/main $^

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(BIN)
	@exec bin/main

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: clean run
