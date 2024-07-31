# =============================
# -----------------------------
# COMMON
# -----------------------------

NPROC := 1

ifeq ($(OS),Windows_NT)
UNAME := Windows
else
UNAME := $(shell uname -s)
NPROC := $(shell nproc)
endif

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



# =============================
# -----------------------------
# MAKEFILE FLAGS
# -----------------------------

MAKEFLAGS = -j$(NPROC) --no-print-directory

# =============================



# =============================
# -----------------------------
# BUILD & SUBMODULE DIRECTORIES
# -----------------------------

BLD_DIR  = bld
LIB_DIR  = lib
SDL3_DIR = $(LIB_DIR)/SDL3
GLAD_DIR = $(LIB_DIR)/glad
CGLM_DIR = $(LIB_DIR)/cglm

# =============================



# =============================
# -----------------------------
# COMPILE TOOLS
# -----------------------------

SHELL = /bin/sh
CXX   = g++
CC    = gcc
LD    = gcc
AR    = ar
NM    = nm

# =============================



# =============================
# -----------------------------
# COMPILE FLAGS
# -----------------------------

INCLUDE	 =
CPPFLAGS = -DLOG_USE_COLOR
CFLAGS	 = -g -Wall -Wextra -std=c11 -ggdb3 -pedantic
CXXFLAGS = -g -Wall -Wextra -std=c++17 -ggdb3 -pedantic
LDFLAGS	 = 
LDLIBS	 = -lm

INCLUDE += -Ivce
INCLUDE += -I$(SDL3_DIR)/include
INCLUDE += -I$(GLAD_DIR)/include
INCLUDE += -I$(CGLM_DIR)/include

LDFLAGS += -L$(BLD_DIR)/sdl3/bin
LDFLAGS += -L$(BLD_DIR)/glad/bin
LDFLAGS += -L$(BLD_DIR)/cglm/bin

LDLIBS  += -l:libSDL3.so
LDLIBS  += -l:glad.o
LDLIBS  += -l:libcglm.a

# =============================



# =============================
# -----------------------------
# TRACKER VARIABLES
# -----------------------------

PHONY =
CLEAN =
DEPS  =
DIRS  = $(BLD_DIR)

# =============================



TEST_BLD_DIR = $(BLD_DIR)/test
TEST_SRC_DIR = test
TEST_BIN_DIR = $(TEST_BLD_DIR)/bin
TEST_OBJ_DIR = $(TEST_BLD_DIR)/obj
TEST_DEP_DIR = $(TEST_BLD_DIR)/dep

TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)
TEST_DEP = $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_DEP_DIR)/%.d)
TEST_BIN = $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_BIN_DIR)/%)
TEST     = $(TEST_SRC:$(TEST_SRC_DIR)/%.c=%)



# =============================
# -----------------------------
# ENTRY POINT
# -----------------------------

all: build
PHONY += all

# =============================



# =============================
# -----------------------------
# VC ENGINE
# -----------------------------

SRC_DIR_ENGINE = vce
BIN_DIR_ENGINE = $(BLD_DIR)/$(SRC_DIR_ENGINE)/bin
OBJ_DIR_ENGINE = $(BLD_DIR)/$(SRC_DIR_ENGINE)/obj
DEP_DIR_ENGINE = $(BLD_DIR)/$(SRC_DIR_ENGINE)/dep

TARGET_ENGINE = $(BIN_DIR_ENGINE)/libVCE.so

SRC_ENGINE = $(wildcard $(SRC_DIR_ENGINE)/*.c) \
			 $(wildcard $(SRC_DIR_ENGINE)/**/*.c) \
			 $(wildcard $(SRC_DIR_ENGINE)/**/**/*.c) \
			 $(wildcard $(SRC_DIR_ENGINE)/**/**/**/*.c)

OBJ_ENGINE = $(SRC_ENGINE:$(SRC_DIR_ENGINE)/%.c=$(OBJ_DIR_ENGINE)/%.o)
DEP_ENGINE = $(SRC_ENGINE:$(SRC_DIR_ENGINE)/%.c=$(DEP_DIR_ENGINE)/%.d)

$(TARGET_ENGINE): $(OBJ_ENGINE)
	$(RUN_CMD_LTLINK) $(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJ_ENGINE): $(OBJ_DIR_ENGINE)/%.o: $(SRC_DIR_ENGINE)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) -fpic $(CFLAGS) -MMD -MP -MF $(<:$(SRC_DIR_ENGINE)/%.c=$(DEP_DIR_ENGINE)/%.d) -MT $@ -o $@ -c $<

DEPS += $(DEP_ENGINE)
DIRS += $(BIN_DIR_ENGINE) $(OBJ_DIR_ENGINE) $(DEP_DIR_ENGINE) $(dir $(OBJ_ENGINE)) $(dir $(DEP_ENGINE))

# =============================



# =============================
# -----------------------------
# VC GAME
# -----------------------------

SRC_DIR_GAME = vcg
BIN_DIR_GAME = $(BLD_DIR)/$(SRC_DIR_GAME)/bin
OBJ_DIR_GAME = $(BLD_DIR)/$(SRC_DIR_GAME)/obj
DEP_DIR_GAME = $(BLD_DIR)/$(SRC_DIR_GAME)/dep

TARGET_GAME = $(BIN_DIR_GAME)/main

SRC_GAME = $(wildcard $(SRC_DIR_GAME)/*.c) \
		   $(wildcard $(SRC_DIR_GAME)/**/*.c) \
		   $(wildcard $(SRC_DIR_GAME)/**/**/*.c) \
		   $(wildcard $(SRC_DIR_GAME)/**/**/**/*.c)

OBJ_GAME = $(SRC_GAME:$(SRC_DIR_GAME)/%.c=$(OBJ_DIR_GAME)/%.o)
DEP_GAME = $(SRC_GAME:$(SRC_DIR_GAME)/%.c=$(DEP_DIR_GAME)/%.d)

$(TARGET_GAME): $(OBJ_GAME)
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ $(LDFLAGS) -L$(BIN_DIR_ENGINE) $(LDLIBS) -l:libVCE.so

$(OBJ_GAME): $(OBJ_DIR_GAME)/%.o: $(SRC_DIR_GAME)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(SRC_DIR_GAME)/%.c=$(DEP_DIR_GAME)/%.d) -MT $@ -o $@ -c $<

DEPS += $(DEP_GAME)
DIRS += $(BIN_DIR_GAME) $(OBJ_DIR_GAME) $(DEP_DIR_GAME) $(dir $(OBJ_GAME)) $(dir $(DEP_GAME))

# =============================



# =============================
# -----------------------------
# UNIT TESTS
# -----------------------------

#PHONY += test
#test: $(TEST_BIN)
#	@LD_PRELOAD=lib/SDL3/build/libSDL3.so $(TEST_BIN_DIR)/test_all --enable-mixed-units
#
#$(TEST): %: $(TEST_BIN_DIR)/%
#	@LD_PRELOAD=lib/SDL3/build/libSDL3.so $(TEST_BIN_DIR)/$@ --enable-mixed-units
#
#$(TEST_BIN): $(TEST_BIN_DIR)/%: $(TEST_OBJ_DIR)/%.o $(OBJ:$(OBJ_DIR)/main.o=) $(LIBS)
#	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
#
#$(TEST_OBJ): $(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
#	$(RUN_CMD_CC) $(CC) $(INCLUDE) -I$(TEST_SRC_DIR) $(CPPFLAGS) -DINSTANTIATE_MAIN $(CFLAGS) -MMD -MP -MF $(<:$(TEST_SRC_DIR)/%.c=$(TEST_DEP_DIR)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# BUILD & RUN
# -----------------------------

run: build
	@exec ./scripts/run.sh

build:
	@cd lib; $(MAKE) -s
	@$(MAKE) -s $(TARGET_ENGINE)
	@$(MAKE) -s $(TARGET_GAME)

PHONY += build run

# =============================



# =============================
# -----------------------------
# REMOVE BUILD FILES
# -----------------------------

PHONY += clean clean-all

clean:
	@rm -r $(BIN_DIR_ENGINE) $(OBJ_DIR_ENGINE) $(DEP_DIR_ENGINE) 2> /dev/null || true
	@rm -r $(BIN_DIR_GAME) $(OBJ_DIR_GAME) $(DEP_DIR_GAME) 2> /dev/null || true

clean-all: clean
	@cd lib; $(MAKE) clean

# =============================



# =============================
# -----------------------------
# FINAL STUFF I GUESS
# -----------------------------

$(shell mkdir -p $(DIRS))
-include $(TEST_DEP) $(DEPS)
.PHONY: $(PHONY)

# =============================
