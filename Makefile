# always use as many cores as possible
MAKEFLAGS = -j$(exec nproc)

# flags and compiler
CC = gcc

CFLAGS = -g -Wall -Wextra -std=c99 -ggdb3 -pedantic
LDLIBS = -lm -lSDL2
LDFLAGS = 

# directories
BLD_DIR := bld
SRC_DIR := src
BIN_DIR := $(BLD_DIR)/bin
OBJ_DIR := $(BLD_DIR)/obj
DEP_DIR := $(BLD_DIR)/dep

# entire build directory tree
BLD_DIRS := $(BIN_DIR) \
			$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(shell find $(SRC_DIR) -type d -not -path $(SRC_DIR))) \
			$(patsubst $(SRC_DIR)/%,$(DEP_DIR)/%,$(shell find $(SRC_DIR) -type d -not -path $(SRC_DIR)))

# files
BIN := $(BIN_DIR)/main
SRC := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP := $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

# build
all: $(BLD_DIRS) $(BIN)

# build and run
run: all
	exec $(BIN)

# create directories
$(BLD_DIRS):
	@mkdir -p $@

# compile to binary
$(BIN): $(OBJ)
	$(CC) $(LDLIBS) -o $(BIN_DIR)/main $^

# generate object files and dependencies
$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
	@$(CC) $(CFLAGS) -MG -MM -MP -MF $(<:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d) -MT $(<:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d) -MT $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $<

# remove build files
clean:
	@rm -r $(BLD_DIR) 2> /dev/null || true

-include $(DEP)

.PHONY: all clean run
