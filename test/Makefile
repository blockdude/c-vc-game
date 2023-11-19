# always use as many cores as possible
MAKEFLAGS = -j$(exec nproc)

# directories
BLD_DIR ?= ../.bld
SRC_DIR ?= ../src
LIB_DIR ?= ../lib
BIN_DIR := $(BLD_DIR)/bin
OBJ_DIR := $(BLD_DIR)/obj
DEP_DIR := $(BLD_DIR)/dep

# files
BIN := $(BIN_DIR)/main
SRC := $(shell find $(SRC_DIR) -type f -name '*.c' $(BIN:$(BIN_DIR)/%=-not -name '%.c'))
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP := $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

TEST_BLD_DIR := build
TEST_BIN_DIR := $(TEST_BLD_DIR)/bin
TEST_OBJ_DIR := $(TEST_BLD_DIR)/obj
TEST_DEP_DIR := $(TEST_BLD_DIR)/dep

TEST_DIRS := $(TEST_BLD_DIR) $(TEST_BIN_DIR) $(TEST_OBJ_DIR) $(TEST_DEP_DIR)

TEST_SRC := $(shell find . -type f -name '*.c' | sed 's|^./||')
TEST_OBJ := $(TEST_SRC:%.c=$(TEST_OBJ_DIR)/%.o)
TEST_DEP := $(TEST_SRC:%.c=$(TEST_DEP_DIR)/%.d)
TEST_BIN := $(TEST_SRC:%.c=$(TEST_BIN_DIR)/%)
TEST     := $(TEST_SRC:%.c=%)

# flags and compiler
SHELL		= /bin/sh
CC			= gcc
LINKER		= $(CC)
INCLUDE		= -I$(SRC_DIR) -I./
CPPFLAGS	= -DLOG_USE_COLOR -DINSTANTIATE_MAIN
CFLAGS		= -g -Wall -Wextra -std=c11 -ggdb3 -pedantic
LDFLAGS		=
LDLIBS		= -lm -lSDL2

# echo output
RUN_CMD_MKDIR  = @echo "  MKDIR " $@;
RUN_CMD_AR     = @echo "  AR    " $@;
RUN_CMD_CC     = @echo "  CC    " $@;
RUN_CMD_CXX    = @echo "  CXX   " $@;
RUN_CMD_LTLINK = @echo "  LTLINK" $@;
RUN_CMD_RANLIB = @echo "  RANLIB" $@;
RUN_CMD_RC     = @echo "  RC    " $@;
RUN_CMD_GEN    = @echo "  GEN   " $@;

# build
all: $(TEST_DIRS) $(TEST_BIN)

# create directories
$(TEST_DIRS):
	$(RUN_CMD_MKDIR) mkdir -p $@

$(TEST): all
	@exec $(TEST_BIN_DIR)/$@ --enable-mixed-units

# link to binary
$(TEST_BIN): $(TEST_BIN_DIR)/%: $(TEST_OBJ_DIR)/%.o
	$(RUN_CMD_LTLINK) $(LINKER) -o $@ $^ $(OBJ) $(LDFLAGS) $(LDLIBS)

# generate object files and dependencies
$(TEST_OBJ): $(TEST_OBJ_DIR)/%.o: %.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:%.c=$(TEST_DEP_DIR)/%.d) -MT $@ -o $@ -c $<

# remove build files
clean:
	@rm -r $(TEST_BLD_DIR) 2> /dev/null || true

-include $(TEST_DEP) $(DEP)

.PHONY: all clean test run
