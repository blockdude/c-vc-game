# always use as many cores as possible
MAKEFLAGS = -j$(exec nproc) --no-print-directory

# directories
BLD_DIR ?= .bld
SRC_DIR ?= src
LIB_DIR ?= lib
BIN_DIR := $(BLD_DIR)/bin
OBJ_DIR := $(BLD_DIR)/obj
DEP_DIR := $(BLD_DIR)/dep

# directory tree
DIRS := $(BLD_DIR) $(BIN_DIR) $(OBJ_DIR) $(DEP_DIR) \
		$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(shell find $(SRC_DIR) -type d -not -path $(SRC_DIR))) \
		$(patsubst $(SRC_DIR)/%,$(DEP_DIR)/%,$(shell find $(SRC_DIR) -type d -not -path $(SRC_DIR)))

# files
BIN := $(BIN_DIR)/main
SRC := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP := $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

# flags and compiler
SHELL		= /bin/sh
CC			= gcc
LINKER		= $(CC)
INCLUDE		= -I$(SRC_DIR) -I$(LIB_DIR)/glad/include
CPPFLAGS	= -DLOG_USE_COLOR
CFLAGS		= -g -Wall -Wextra -std=c11 -ggdb3 -pedantic
LDFLAGS		= $(LIB_DIR)/glad/obj/glad.o
LDLIBS		= -lm -ldl -lSDL2

# echo output
RUN_CMD_MKDIR  = @echo "  MKDIR " $@;
RUN_CMD_AR     = @echo "  AR    " $@;
RUN_CMD_CC     = @echo "  CC    " $@;
RUN_CMD_CXX    = @echo "  CXX   " $@;
RUN_CMD_LTLINK = @echo "  LTLINK" $@;
RUN_CMD_RANLIB = @echo "  RANLIB" $@;
RUN_CMD_RC     = @echo "  RC    " $@;
RUN_CMD_GEN    = @echo "  GEN   " $@;

all: bld test

bld: $(LIB_DIR)/glad/obj/glad.o $(DIRS) $(BIN)

$(LIB_DIR)/glad/obj/glad.o:
	@(cd $(LIB_DIR)/glad && mkdir -p obj && $(CC) -Iinclude -o obj/glad.o -c src/glad.c)

test: bld
	@(cd test; $(MAKE) test_all)

# build and run
run: all
	@exec $(BIN)

# create directories
$(DIRS):
	$(RUN_CMD_MKDIR) mkdir -p $@

# link to binary
$(BIN): $(OBJ)
	$(RUN_CMD_LTLINK) $(LINKER) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# generate object files and dependencies
$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d) -MT $@ -o $@ -c $<

# remove build files
clean:
	@rm -r $(BLD_DIR) 2> /dev/null || true
	@rm -r $(LIB_DIR)/glad/obj 2> /dev/null || true
	@(cd test; $(MAKE) clean)

-include $(DEP)

.PHONY: all clean run test bld libs
