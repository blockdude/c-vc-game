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

find = $(wildcard $1/$2) \
	   $(wildcard $1/**/$2) \
	   $(wildcard $1/**/**/$2) \
	   $(wildcard $1/**/**/**/$2)

#rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $2,$d))

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

BIN_PATH  = $(BLD_PATH)/bin
OBJ_PATH  = $(BLD_PATH)/obj
DEP_PATH  = $(BLD_PATH)/dep

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
LIBS  = 

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
# SDL LIB
# -----------------------------

define BLD_SDL3

echo
echo =====================
echo ----BUILDING SDL3----
echo =====================
echo

# BUILD SDL
cd $(SDL3_PATH) && cmake -S . -B build && cmake --build build

# COPY SDL TO BUILD LOCATION
cp $(SDL3_PATH)/build/libSDL3.so $(BLD_PATH)/bin/sdl3
cd $(BLD_PATH)/bin/sdl3 && ln -s libSDL3.so libSDL3.so.0

endef

DIRS       += $(BLD_PATH)/bin/sdl3
LIBS       += $(BLD_PATH)/bin/sdl3/libSDL3.so
CLEAN_LIBS += (cd $(SDL3_PATH) && cmake --build build --target clean);

# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

define BLD_GLAD

echo
echo =====================
echo ----BUILDING GLAD----
echo =====================
echo

cd $(GLAD_PATH) && mkdir -p obj && $(CC) -Iinclude -o obj/glad.o -c -fpic src/glad.c
echo [100%] built target glad

cp $(GLAD_PATH)/obj/glad.o $(BLD_PATH)/bin/glad

endef

DIRS	   += $(BLD_PATH)/bin/glad
LIBS       += $(BLD_PATH)/bin/glad/glad.o
CLEAN_LIBS += (rm -r $(GLAD_PATH)/obj 2> /dev/null || true);

# =============================



# =============================
# -----------------------------
# CGLM LIB
# -----------------------------

ifeq ($(UNAME),Windows)
    CGLMEX = -G "MinGW Makefiles"
endif

define BLD_CGLM

echo
echo =====================
echo ----BUILDING CGLM----
echo =====================
echo

cd $(CGLM_PATH) && cmake . -DCGLM_STATIC=ON $(CGLMEX) && make
mkdir -p $(BLD_PATH)/bin/cglm
cp $(CGLM_PATH)/libcglm.a $(BLD_PATH)/bin/cglm

endef

DIRS       += $(BLD_PATH)/bin/cglm
LIBS       += $(BLD_PATH)/bin/cglm/libcglm.a
CLEAN_LIBS += (cd $(CGLM_PATH) && make clean);

# =============================



# =============================
# -----------------------------
# BUILD LIBS
# -----------------------------

$(LIBS) &:
	@$(BLD_SDL3)
	@$(BLD_GLAD)
	@$(BLD_CGLM)

# =============================



# =============================
# -----------------------------
# CANS
# -----------------------------

define DEFVARS

$1_SRC_PATH = $2
$1_SRC_EXT  = $3
$1_TARGET   = $$(addprefix $$($1_BIN_PATH)/,$4)

$1_BIN_PATH = $(BIN_PATH)/$$($1_SRC_PATH)
$1_OBJ_PATH = $(OBJ_PATH)/$$($1_SRC_PATH)
$1_DEP_PATH = $(DEP_PATH)/$$($1_SRC_PATH)

$1_SRC = $$(call find,$$($1_SRC_PATH),*.$$($1_SRC_EXT))
$1_OBJ = $$($1_SRC:$$($1_SRC_PATH)/%.$$($1_SRC_EXT)=$$($1_OBJ_PATH)/%.o)
$1_DEP = $$($1_SRC:$$($1_SRC_PATH)/%.$$($1_SRC_EXT)=$$($1_DEP_PATH)/%.d)

DEPS  += $$($1_DEP)
DIRS  += $$($1_BIN_PATH) $$($1_OBJ_PATH) $$($1_DEP_PATH) $$(dir $$($1_OBJ)) $$(dir $$($1_DEP))
CLEAN += $$($1_BIN_PATH) $$($1_OBJ_PATH) $$($1_DEP_PATH)

endef

# =============================



# =============================
# -----------------------------
# VC ENGINE
# -----------------------------

$(eval $(call DEFVARS,ENGINE,vce,c,libVCE.so))

$(ENGINE_TARGET): LDFLAGS += -shared
$(ENGINE_TARGET): $(ENGINE_OBJ)
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(ENGINE_OBJ): CFLAGS += -fpic
$(ENGINE_OBJ): $(ENGINE_OBJ_PATH)/%.o: $(ENGINE_SRC_PATH)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(ENGINE_SRC_PATH)/%.c=$(ENGINE_DEP_PATH)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# VC GAME
# -----------------------------

$(eval $(call DEFVARS,GAME,vcg,cc,main))

$(GAME_TARGET): LDFLAGS += -L$(ENGINE_BIN_PATH)
$(GAME_TARGET): LDLIBS  += -lstdc++
$(GAME_TARGET): LDLIBS  += -l:libVCE.so
$(GAME_TARGET): $(GAME_OBJ)
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(GAME_OBJ): INCLUDE  += -I$(GAME_SRC_PATH)
$(GAME_OBJ): CPPFLAGS += -DCGLM_USE_ANONYMOUS_STRUCT=0
$(GAME_OBJ): $(GAME_OBJ_PATH)/%.o: $(GAME_SRC_PATH)/%.$(CXX_EXT)
	$(RUN_CMD_CXX) $(CXX) $(INCLUDE) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -MF $(<:$(GAME_SRC_PATH)/%.$(CXX_EXT)=$(GAME_DEP_PATH)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# UNIT TESTS
# -----------------------------
$(eval $(call DEFVARS,TEST,test,c,$$(TEST_SRC:$$(TEST_SRC_PATH)/%.c=%)))

$(TEST_TARGET): LDFLAGS += -L$(ENGINE_BIN_PATH)
$(TEST_TARGET): LDLIBS  += -l:libVCE.so
$(TEST_TARGET): $(TEST_BIN_PATH)/%: $(TEST_OBJ_PATH)/%.o
	$(RUN_CMD_LTLINK) $(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TEST_OBJ): CPPFLAGS += -DINSTANTIATE_MAIN
$(TEST_OBJ): INCLUDE  += -I$(TEST_SRC_PATH)
$(TEST_OBJ): $(TEST_OBJ_PATH)/%.o: $(TEST_SRC_PATH)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(TEST_SRC_PATH)/%.c=$(TEST_DEP_PATH)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# BUILD & RUN & TEST
# -----------------------------

run: build
	@./scripts/run.sh bld/bin/vcg/main

build:
	@$(MAKE) -s $(LIBS)
	@$(MAKE) -s $(ENGINE_TARGET)
	@$(MAKE) -s $(GAME_TARGET)
	@$(MAKE) -s $(TEST_TARGET)

test: build
	@./scripts/run.sh "$(TEST_BIN_PATH)/test_all --enable-mixed-units"

TEST = $(TEST_SRC:$(TEST_SRC_PATH)/%.c=%)
$(TEST): %: $(TEST_BIN_PATH)/%
	@./scripts/run.sh "$(TEST_BIN_PATH)/$@ --enable-mixed-units"

PHONY += build run test game engine libs

# =============================



# =============================
# -----------------------------
# REMOVE BUILD FILES
# -----------------------------

PHONY += clean clean-all

clean:
	@rm -r $(CLEAN) 2> /dev/null || true

clean-all:
	@rm -r $(BLD_PATH) 2> /dev/null || true
	@$(CLEAN_LIBS)

# =============================



# =============================
# -----------------------------
# FINAL STUFF I GUESS
# -----------------------------

$(shell mkdir -p $(DIRS))
-include $(DEPS)
.PHONY: $(PHONY)

# =============================
