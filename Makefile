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
CXXFLAGS = -g -Wall -Wextra -std=c++20 -ggdb3 -pedantic
LDFLAGS	 = 
LDLIBS	 = -lm

INCLUDE += -Ivce
INCLUDE += -I$(SDL3_DIR)/include
INCLUDE += -I$(GLAD_DIR)/include
INCLUDE += -I$(CGLM_DIR)/include

LDFLAGS += -L$(BLD_DIR)/bin/sdl3
LDFLAGS += -L$(BLD_DIR)/bin/glad
LDFLAGS += -L$(BLD_DIR)/bin/cglm

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
BIN_DIR_ENGINE = $(BLD_DIR)/bin/$(SRC_DIR_ENGINE)
OBJ_DIR_ENGINE = $(BLD_DIR)/obj/$(SRC_DIR_ENGINE)
DEP_DIR_ENGINE = $(BLD_DIR)/dep/$(SRC_DIR_ENGINE)

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
BIN_DIR_GAME = $(BLD_DIR)/bin/$(SRC_DIR_GAME)
OBJ_DIR_GAME = $(BLD_DIR)/obj/$(SRC_DIR_GAME)
DEP_DIR_GAME = $(BLD_DIR)/dep/$(SRC_DIR_GAME)

TARGET_GAME = $(BIN_DIR_GAME)/main

SRC_GAME = $(wildcard $(SRC_DIR_GAME)/*.c) \
		   $(wildcard $(SRC_DIR_GAME)/**/*.c) \
		   $(wildcard $(SRC_DIR_GAME)/**/**/*.c) \
		   $(wildcard $(SRC_DIR_GAME)/**/**/**/*.c)

OBJ_GAME = $(SRC_GAME:$(SRC_DIR_GAME)/%.c=$(OBJ_DIR_GAME)/%.o)
DEP_GAME = $(SRC_GAME:$(SRC_DIR_GAME)/%.c=$(DEP_DIR_GAME)/%.d)

$(TARGET_GAME): $(OBJ_GAME)
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ -lstdc++ $(LDFLAGS) -L$(BIN_DIR_ENGINE) $(LDLIBS) -l:libVCE.so

$(OBJ_GAME): $(OBJ_DIR_GAME)/%.o: $(SRC_DIR_GAME)/%.c
	$(RUN_CMD_CXX) $(CXX) $(INCLUDE) -I$(SRC_DIR_GAME) $(CPPFLAGS) -DCGLM_USE_ANONYMOUS_STRUCT=0 $(CXXFLAGS) -MMD -MP -MF $(<:$(SRC_DIR_GAME)/%.c=$(DEP_DIR_GAME)/%.d) -MT $@ -o $@ -c $<

DEPS += $(DEP_GAME)
DIRS += $(BIN_DIR_GAME) $(OBJ_DIR_GAME) $(DEP_DIR_GAME) $(dir $(OBJ_GAME)) $(dir $(DEP_GAME))

# =============================



# =============================
# -----------------------------
# UNIT TEST VCE
# -----------------------------

SRC_DIR_TEST = test
BIN_DIR_TEST = $(BLD_DIR)/bin/$(SRC_DIR_TEST)
OBJ_DIR_TEST = $(BLD_DIR)/obj/$(SRC_DIR_TEST)
DEP_DIR_TEST = $(BLD_DIR)/dep/$(SRC_DIR_TEST)

TARGET_TEST = $(SRC_TEST:$(SRC_DIR_TEST)/%.c=$(BIN_DIR_TEST)/%)

SRC_TEST = $(wildcard $(SRC_DIR_TEST)/*.c)
OBJ_TEST = $(SRC_TEST:$(SRC_DIR_TEST)/%.c=$(OBJ_DIR_TEST)/%.o)
DEP_TEST = $(SRC_TEST:$(SRC_DIR_TEST)/%.c=$(DEP_DIR_TEST)/%.d)

$(TARGET_TEST): $(BIN_DIR_TEST)/%: $(OBJ_DIR_TEST)/%.o
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ $(LDFLAGS) -L$(BIN_DIR_ENGINE) $(LDLIBS) -l:libVCE.so

$(OBJ_TEST): $(OBJ_DIR_TEST)/%.o: $(SRC_DIR_TEST)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) -I$(SRC_DIR_TEST) $(CPPFLAGS) -DINSTANTIATE_MAIN $(CFLAGS) -MMD -MP -MF $(<:$(SRC_DIR_TEST)/%.c=$(DEP_DIR_TEST)/%.d) -MT $@ -o $@ -c $<

DEPS += $(DEP_TEST)
DIRS += $(BIN_DIR_TEST) $(OBJ_DIR_TEST) $(DEP_DIR_TEST)

# =============================



# =============================
# -----------------------------
# BUILD & RUN & TEST
# -----------------------------

run: build
	@./scripts/run.sh bld/bin/vcg/main

build:
	@cd lib; $(MAKE) -s
	@$(MAKE) -s $(TARGET_ENGINE)
	@$(MAKE) -s $(TARGET_GAME)
	@$(MAKE) -s $(TARGET_TEST)

test: build
	@./scripts/run.sh "$(BIN_DIR_TEST)/test_all --enable-mixed-units"

TEST = $(SRC_TEST:$(SRC_DIR_TEST)/%.c=%)
$(TEST): %: $(BIN_DIR_TEST)/%
	@./scripts/run.sh "$(BIN_DIR_TEST)/$@ --enable-mixed-units"

PHONY += build run test

# =============================



# =============================
# -----------------------------
# REMOVE BUILD FILES
# -----------------------------

PHONY += clean clean-all

clean:
	@rm -r $(BIN_DIR_ENGINE) $(OBJ_DIR_ENGINE) $(DEP_DIR_ENGINE) 2> /dev/null || true
	@rm -r $(BIN_DIR_GAME) $(OBJ_DIR_GAME) $(DEP_DIR_GAME) 2> /dev/null || true
	@rm -r $(BIN_DIR_TEST) $(OBJ_DIR_TEST) $(DEP_DIR_TEST) 2> /dev/null || true

clean-all:
	@cd lib; $(MAKE) clean
	@rm -r $(BLD_DIR) 2> /dev/null || true

# =============================



# =============================
# -----------------------------
# FINAL STUFF I GUESS
# -----------------------------

$(shell mkdir -p $(DIRS))
-include $(DEPS)
.PHONY: $(PHONY)

# =============================
