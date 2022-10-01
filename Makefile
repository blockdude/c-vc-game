# always use as many cores as possible
MAKEFLAGS = -j$(exec nproc)

# flags and compiler
CC = gcc

CFLAGS = -g -Wall -Wextra -std=c99 -ggdb3 -pedantic
LDLIBS = -lm -lSDL2
LDFLAGS = 

# directories and files
BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep

BIN := $(BIN_DIR)/main
SRC := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP := $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

# build
all: $(BIN)

# build and run
run: $(BIN)
	exec bin/main

# compile to binary
$(BIN): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDLIBS) -o $(BIN_DIR)/main $^

# generate object files
$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@mkdir -p $(@D:$(OBJ_DIR)%=$(DEP_DIR)%)
	$(CC) $(CFLAGS) -c -o $@ $<
	@$(CC) $(CFLAGS) -MG -MM -MP -MF $(<:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d) -MT $(<:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d) -MT $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $<

# generate dependency files
#$(DEP): $(DEP_DIR)/%.d: $(SRC_DIR)/%.c
#	@mkdir -p $(@D)
#	$(CC) $(CFLAGS) -MG -MM -MP -MF $@ -MT $@ -MT $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $<

# remove build files
clean:
	@rm -r $(BIN_DIR) $(OBJ_DIR) $(DEP_DIR) 2> /dev/null || true

-include $(DEP)

.PHONY: all clean run
