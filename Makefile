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

CLEAN = $(BLD_DIR)
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

PHONY = all
all: build test

# =============================



# =============================
# -----------------------------
# GLAD lib
# -----------------------------

INCLUDE += -I$(LIB_DIR)/glad/include
LDFLAGS += $(LIB_DIR)/glad/obj/glad.o
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
# CGLM lib
# -----------------------------

INCLUDE += -I$(LIB_DIR)/cglm/include
LDFLAGS += $(LIB_DIR)/cglm/libcglm.a
LIBS    += $(LIB_DIR)/cglm/libcglm.a

$(LIB_DIR)/cglm/libcglm.a:
	$(RUN_CMD_CC) (cd lib/cglm && cmake . -DCGLM_STATIC=ON && make)

CLEAN += clean_libcglm.a
PHONY += clean_libcglm.a
clean_libcglm.a:
	@(cd lib/cglm && make clean)

# =============================



# =============================
# -----------------------------
# MAIN GAME
# -----------------------------

PHONY += run
run: all
	@exec $(BIN)

PHONY += build
build: $(LIBS) $(DIRS) $(BIN)

PHONY += test
test: build
	#@(cd test; $(MAKE) clean)
	@(cd test; $(MAKE) test_all)

$(DIRS):
	$(RUN_CMD_MKDIR) mkdir -p $@

$(BIN): $(OBJ)
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
	@(cd test; $(MAKE) clean)

# =============================

-include $(DEP)

.PHONY: $(PHONY)
