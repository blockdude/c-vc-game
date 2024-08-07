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

BLD_PATH  = bld
LIB_PATH  = lib
SDL3_PATH = $(LIB_PATH)/SDL3
GLAD_PATH = $(LIB_PATH)/glad
CGLM_PATH = $(LIB_PATH)/cglm

# =============================



# =============================
# -----------------------------
# COMPILE TOOLS
# -----------------------------

SHELL = /bin/sh
CXX   = clang++
CC    = clang
LD    = clang
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
INCLUDE += -I$(SDL3_PATH)/include
INCLUDE += -I$(GLAD_PATH)/include
INCLUDE += -I$(CGLM_PATH)/include

LDFLAGS += -L$(BLD_PATH)/bin/sdl3
LDFLAGS += -L$(BLD_PATH)/bin/glad
LDFLAGS += -L$(BLD_PATH)/bin/cglm

LDLIBS  += -l:libSDL3.so
LDLIBS  += -l:glad.o
LDLIBS  += -l:libcglm.a

# =============================



# =============================
# -----------------------------
# OTHER VARIABLES
# -----------------------------

CXX_EXT = cc
C_EXT   = c

# =============================



# =============================
# -----------------------------
# TRACKER VARIABLES
# -----------------------------

PHONY =
CLEAN =
DEPS  =
DIRS  = $(BLD_PATH)

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

SRC_PATH_ENGINE = vce
BIN_PATH_ENGINE = $(BLD_PATH)/bin/$(SRC_PATH_ENGINE)
OBJ_PATH_ENGINE = $(BLD_PATH)/obj/$(SRC_PATH_ENGINE)
DEP_PATH_ENGINE = $(BLD_PATH)/dep/$(SRC_PATH_ENGINE)

TARGET_ENGINE = $(BIN_PATH_ENGINE)/libVCE.so

SRC_ENGINE = $(wildcard $(SRC_PATH_ENGINE)/*.c) \
			 $(wildcard $(SRC_PATH_ENGINE)/**/*.c) \
			 $(wildcard $(SRC_PATH_ENGINE)/**/**/*.c) \
			 $(wildcard $(SRC_PATH_ENGINE)/**/**/**/*.c)

OBJ_ENGINE = $(SRC_ENGINE:$(SRC_PATH_ENGINE)/%.c=$(OBJ_PATH_ENGINE)/%.o)
DEP_ENGINE = $(SRC_ENGINE:$(SRC_PATH_ENGINE)/%.c=$(DEP_PATH_ENGINE)/%.d)

$(TARGET_ENGINE): $(OBJ_ENGINE)
	$(RUN_CMD_LTLINK) $(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJ_ENGINE): $(OBJ_PATH_ENGINE)/%.o: $(SRC_PATH_ENGINE)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) -fpic $(CFLAGS) -MMD -MP -MF $(<:$(SRC_PATH_ENGINE)/%.c=$(DEP_PATH_ENGINE)/%.d) -MT $@ -o $@ -c $<

DEPS += $(DEP_ENGINE)
DIRS += $(BIN_PATH_ENGINE) $(OBJ_PATH_ENGINE) $(DEP_PATH_ENGINE) $(dir $(OBJ_ENGINE)) $(dir $(DEP_ENGINE))

# =============================



# =============================
# -----------------------------
# VC GAME
# -----------------------------

SRC_PATH_GAME = vcg
BIN_PATH_GAME = $(BLD_PATH)/bin/$(SRC_PATH_GAME)
OBJ_PATH_GAME = $(BLD_PATH)/obj/$(SRC_PATH_GAME)
DEP_PATH_GAME = $(BLD_PATH)/dep/$(SRC_PATH_GAME)

TARGET_GAME = $(BIN_PATH_GAME)/main

SRC_GAME = $(wildcard $(SRC_PATH_GAME)/*.$(CXX_EXT)) \
		   $(wildcard $(SRC_PATH_GAME)/**/*.$(CXX_EXT)) \
		   $(wildcard $(SRC_PATH_GAME)/**/**/*.$(CXX_EXT)) \
		   $(wildcard $(SRC_PATH_GAME)/**/**/**/*.$(CXX_EXT)) \

OBJ_GAME = $(SRC_GAME:$(SRC_PATH_GAME)/%.$(CXX_EXT)=$(OBJ_PATH_GAME)/%.o)
DEP_GAME = $(SRC_GAME:$(SRC_PATH_GAME)/%.$(CXX_EXT)=$(DEP_PATH_GAME)/%.d)

$(TARGET_GAME): $(OBJ_GAME)
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ -lstdc++ $(LDFLAGS) -L$(BIN_PATH_ENGINE) $(LDLIBS) -l:libVCE.so

$(OBJ_GAME): $(OBJ_PATH_GAME)/%.o: $(SRC_PATH_GAME)/%.$(CXX_EXT)
	$(RUN_CMD_CXX) $(CXX) $(INCLUDE) -I$(SRC_PATH_GAME) $(CPPFLAGS) -DCGLM_USE_ANONYMOUS_STRUCT=0 $(CXXFLAGS) -MMD -MP -MF $(<:$(SRC_PATH_GAME)/%.$(CXX_EXT)=$(DEP_PATH_GAME)/%.d) -MT $@ -o $@ -c $<

DEPS += $(DEP_GAME)
DIRS += $(BIN_PATH_GAME) $(OBJ_PATH_GAME) $(DEP_PATH_GAME) $(dir $(OBJ_GAME)) $(dir $(DEP_GAME))

# =============================



# =============================
# -----------------------------
# UNIT TEST VCE
# -----------------------------

SRC_PATH_TEST = test
BIN_PATH_TEST = $(BLD_PATH)/bin/$(SRC_PATH_TEST)
OBJ_PATH_TEST = $(BLD_PATH)/obj/$(SRC_PATH_TEST)
DEP_PATH_TEST = $(BLD_PATH)/dep/$(SRC_PATH_TEST)

TARGET_TEST = $(SRC_TEST:$(SRC_PATH_TEST)/%.c=$(BIN_PATH_TEST)/%)

SRC_TEST = $(wildcard $(SRC_PATH_TEST)/*.c)
OBJ_TEST = $(SRC_TEST:$(SRC_PATH_TEST)/%.c=$(OBJ_PATH_TEST)/%.o)
DEP_TEST = $(SRC_TEST:$(SRC_PATH_TEST)/%.c=$(DEP_PATH_TEST)/%.d)

$(TARGET_TEST): $(BIN_PATH_TEST)/%: $(OBJ_PATH_TEST)/%.o
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ $(LDFLAGS) -L$(BIN_PATH_ENGINE) $(LDLIBS) -l:libVCE.so

$(OBJ_TEST): $(OBJ_PATH_TEST)/%.o: $(SRC_PATH_TEST)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) -I$(SRC_PATH_TEST) $(CPPFLAGS) -DINSTANTIATE_MAIN $(CFLAGS) -MMD -MP -MF $(<:$(SRC_PATH_TEST)/%.c=$(DEP_PATH_TEST)/%.d) -MT $@ -o $@ -c $<

DEPS += $(DEP_TEST)
DIRS += $(BIN_PATH_TEST) $(OBJ_PATH_TEST) $(DEP_PATH_TEST)

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
	@./scripts/run.sh "$(BIN_PATH_TEST)/test_all --enable-mixed-units"

TEST = $(SRC_TEST:$(SRC_PATH_TEST)/%.c=%)
$(TEST): %: $(BIN_PATH_TEST)/%
	@./scripts/run.sh "$(BIN_PATH_TEST)/$@ --enable-mixed-units"

PHONY += build run test

# =============================



# =============================
# -----------------------------
# REMOVE BUILD FILES
# -----------------------------

PHONY += clean clean-all

clean:
	@rm -r $(BIN_PATH_ENGINE) $(OBJ_PATH_ENGINE) $(DEP_PATH_ENGINE) 2> /dev/null || true
	@rm -r $(BIN_PATH_GAME) $(OBJ_PATH_GAME) $(DEP_PATH_GAME) 2> /dev/null || true
	@rm -r $(BIN_PATH_TEST) $(OBJ_PATH_TEST) $(DEP_PATH_TEST) 2> /dev/null || true

clean-all:
	@cd lib; $(MAKE) clean
	@rm -r $(BLD_PATH) 2> /dev/null || true

# =============================



# =============================
# -----------------------------
# FINAL STUFF I GUESS
# -----------------------------

$(shell mkdir -p $(DIRS))
-include $(DEPS)
.PHONY: $(PHONY)

# =============================
