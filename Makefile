MAKEFLAGS = -j$(exec nproc) --no-print-directory

ifeq ($(OS),Windows_NT)
    UNAME := Windows
    MKDIR = mkdir
    RMDIR = rmdir
    RM = del
else
    UNAME := $(shell uname -s)
    MKDIR = mkdir
    RMDIR = rm -r
    RM = rm
endif

# flags and compiler
SHELL		= /bin/sh
CC			= gcc
LINKER		= $(CC)
INCLUDE		= -I$(SRC_DIR)
CPPFLAGS	= -DLOG_USE_COLOR
CFLAGS		= -g -Wall -Wextra -std=c11 -ggdb3 -pedantic
LDFLAGS		= 
LDLIBS		= -lm

# directories
BLD_DIR ?= .bld
SRC_DIR ?= src
LIB_DIR ?= lib
BIN_DIR := $(BLD_DIR)/bin
OBJ_DIR := $(BLD_DIR)/obj
DEP_DIR := $(BLD_DIR)/dep

# files
BIN := $(BIN_DIR)/main
SRC := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/**/**/*.c) $(wildcard $(SRC_DIR)/**/**/**/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP := $(SRC:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

TEST_BLD_DIR := $(BLD_DIR)/test
TEST_SRC_DIR := test
TEST_BIN_DIR := $(TEST_BLD_DIR)/bin
TEST_OBJ_DIR := $(TEST_BLD_DIR)/obj
TEST_DEP_DIR := $(TEST_BLD_DIR)/dep

TEST_SRC := $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJ := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)
TEST_DEP := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_DEP_DIR)/%.d)
TEST_BIN := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_BIN_DIR)/%)
TEST     := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=%)

# directory tree
DIRS := $(BLD_DIR) $(BIN_DIR) $(OBJ_DIR) $(DEP_DIR) \
		$(TEST_BLD_DIR) $(TEST_BIN_DIR) $(TEST_OBJ_DIR) $(TEST_DEP_DIR) \
		$(dir $(OBJ)) $(dir $(DEP))

# build directory tree
$(shell mkdir -p $(DIRS))

PHONY =
CLEAN =
LIBS  =
SO    =

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
# SDL LIB
# -----------------------------

ifeq ($(UNAME),Windows)
    #INCLUDE += -I$(LIB_DIR)/sdl2/include
    #LDFLAGS += -L$(LIB_DIR)/sdl2/lib
    #LDLIBS += -lmingw32 -lSDL2main -lSDL2
    #$(shell cp $(LIB_DIR)/sdl2/bin/SDL2.dll $(BIN_DIR))
    #$(shell cp $(LIB_DIR)/sdl2/bin/SDL2.dll $(TEST_BIN_DIR))
else
    #SDLBLD = $()
endif

INCLUDE += -I$(LIB_DIR)/SDL3/include
LDFLAGS += -L$(LIB_DIR)/SDL3/build
LDLIBS += -l:libSDL3.so
LIBS += $(LIB_DIR)/SDL3/build/libSDL3.so

$(LIB_DIR)/SDL3/build/libSDL3.so:
	$(RUN_CMD_AR) (cd $(LIB_DIR)/SDL3 && cmake -S . -B build && cmake --build build)

CLEAN += clean_libSDL3.so
PHONY += clean_libSDL3.so
clean_libSDL3.so:
	(cd $(LIB_DIR)/SDL3 && cmake --build build --target clean)


# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

INCLUDE += -I$(LIB_DIR)/glad/include
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
LIBS    += $(LIB_DIR)/cglm/libcglm.a

ifeq ($(UNAME),Windows)
    CGLMEX = -G "MinGW Makefiles"
endif

$(LIB_DIR)/cglm/libcglm.a:
	$(RUN_CMD_AR) (cd $(LIB_DIR)/cglm && cmake . -DCGLM_STATIC=ON $(CGLMEX) && make)

CLEAN += clean_libcglm.a
PHONY += clean_libcglm.a
clean_libcglm.a:
	@(cd $(LIB_DIR)/cglm && make clean)

# =============================



# =============================
# -----------------------------
# UNIT TESTS
# -----------------------------

PHONY += test
test: $(TEST_BIN)
	LD_PRELOAD=lib/SDL3/build/libSDL3.so $(TEST_BIN_DIR)/test_all --enable-mixed-units

$(TEST): %: $(TEST_BIN_DIR)/%
	LD_PRELOAD=lib/SDL3/build/libSDL3.so $(TEST_BIN_DIR)/$@ --enable-mixed-units

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
	LD_PRELOAD=lib/SDL3/build/libSDL3.so $(BIN)

PHONY += build
build: $(BIN) $(SO)

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
