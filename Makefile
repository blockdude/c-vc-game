MAKEFLAGS = -j$(exec nproc) --no-print-directory

# directories
BLD_DIR ?= .bld
SRC_DIR ?= src
LIB_DIR ?= lib
BIN_DIR := $(BLD_DIR)/bin
OBJ_DIR := $(BLD_DIR)/obj
DEP_DIR := $(BLD_DIR)/dep

# files
BIN := $(BIN_DIR)/main
SRC := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP := $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

TEST_BLD_DIR := $(BLD_DIR)/test
TEST_SRC_DIR := test
TEST_BIN_DIR := $(TEST_BLD_DIR)/bin
TEST_OBJ_DIR := $(TEST_BLD_DIR)/obj
TEST_DEP_DIR := $(TEST_BLD_DIR)/dep

TEST_SRC := $(shell find $(TEST_SRC_DIR) -type f -name '*.c')
TEST_OBJ := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)
TEST_DEP := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_DEP_DIR)/%.d)
TEST_BIN := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_BIN_DIR)/%)
TEST     := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=%)

# directory tree
DIRS := $(BLD_DIR) $(BIN_DIR) $(OBJ_DIR) $(DEP_DIR) \
		$(TEST_BLD_DIR) $(TEST_BIN_DIR) $(TEST_OBJ_DIR) $(TEST_DEP_DIR) \
		$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(shell find $(SRC_DIR) -type d -not -path $(SRC_DIR))) \
		$(patsubst $(SRC_DIR)/%,$(DEP_DIR)/%,$(shell find $(SRC_DIR) -type d -not -path $(SRC_DIR)))
# build directory tree
$(shell mkdir -p $(DIRS))

PHONY =
CLEAN =
LIBS  =

# flags and compiler
SHELL		= /bin/sh
CC			= gcc
LINKER		= $(CC)
INCLUDE		= -I$(SRC_DIR)
CPPFLAGS	= -DLOG_USE_COLOR
CFLAGS		= -g -Wall -Wextra -std=c11 -ggdb3 -pedantic
LDFLAGS		= 
LDLIBS		= -lm -ldl -lSDL2

# echo output
RUN_CMD_MKDIR  = @echo "  MKDIR " $@;
RUN_CMD_RM     = @echo "  RM    " $@;

RUN_CMD_AR     = @echo "  AR    " $@;
RUN_CMD_CC     = @echo "  CC    " $@;
RUN_CMD_CXX    = @echo "  CXX   " $@;
RUN_CMD_LTLINK = @echo "  LTLINK" $@;
RUN_CMD_RANLIB = @echo "  RANLIB" $@;
RUN_CMD_RC     = @echo "  RC    " $@;
RUN_CMD_GEN    = @echo "  GEN   " $@;



# =============================
# -----------------------------
# ENTRY POINT
# -----------------------------

PHONY += all
all: build test

# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

INCLUDE += -I$(LIB_DIR)/glad/include
#LDFLAGS += $(LIB_DIR)/glad/obj/glad.o
LIBS    += $(LIB_DIR)/glad/obj/glad.o

$(LIB_DIR)/glad/obj/glad.o:
	$(RUN_CMD_CC) (cd $(LIB_DIR)/glad && mkdir -p obj && $(CC) -Iinclude -o obj/glad.o -c src/glad.c)

CLEAN += clean_glad.o
PHONY += clean_glad.o
clean_glad.o:
	@rm -r $(LIB_DIR)/glad/obj 2> /dev/null || true

# =============================



# =============================
# -----------------------------
# CGLM LIB
# -----------------------------

INCLUDE += -I$(LIB_DIR)/cglm/include
#LDFLAGS += $(LIB_DIR)/cglm/libcglm.a
LIBS    += $(LIB_DIR)/cglm/libcglm.a

$(LIB_DIR)/cglm/libcglm.a:
	$(RUN_CMD_AR) (cd lib/cglm && cmake . -DCGLM_STATIC=ON && make)

CLEAN += clean_libcglm.a
PHONY += clean_libcglm.a
clean_libcglm.a:
	@(cd lib/cglm && make clean)

# =============================



# =============================
# -----------------------------
# UNIT TESTS
# -----------------------------

PHONY += test
test: $(TEST_BIN)
	@exec $(TEST_BIN_DIR)/test_all --enable-mixed-units

$(TEST): %: $(TEST_BIN_DIR)/%
	@exec $(TEST_BIN_DIR)/$@ --enable-mixed-units

$(TEST_BIN): $(TEST_BIN_DIR)/%: $(TEST_OBJ_DIR)/%.o $(OBJ:$(OBJ_DIR)/main.o=) $(LIBS)
	$(RUN_CMD_LTLINK) $(LINKER) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TEST_OBJ): $(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) -I$(TEST_SRC_DIR) $(CPPFLAGS) -DINSTANTIATE_MAIN $(CFLAGS) -MMD -MP -MF $(<:$(TEST_SRC_DIR)/%.c=$(TEST_DEP_DIR)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# MAIN GAME
# -----------------------------

PHONY += run
run: all
	@exec $(BIN)

PHONY += build
build: $(BIN)

$(BIN): $(OBJ) $(LIBS)
	$(RUN_CMD_LTLINK) $(LINKER) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# CLEAN BUILD FILES
# -----------------------------

PHONY += clean
clean: $(CLEAN)
	@rm -r $(BLD_DIR) 2> /dev/null || true

# =============================

-include $(TEST_DEP) $(DEP)

.PHONY: $(PHONY)
