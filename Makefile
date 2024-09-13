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
RUN_CMD_TOUCH  = @echo "  TOUCH " $@;
RUN_CMD_RM     = @echo "  RM    " $@;
RUN_CMD_CP     = @echo "  CP    " $@;
RUN_CMD_MV     = @echo "  MV    " $@;

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
LIB_PATH  = src/extern

BIN_PATH  = $(BLD_PATH)/bin
OBJ_PATH  = $(BLD_PATH)/obj
DEP_PATH  = $(BLD_PATH)/dep

GLAD_PATH = $(LIB_PATH)/glad
SDL3_PATH = $(LIB_PATH)/sdl
STB_PATH  = $(LIB_PATH)/stb
TOL_PATH  = $(LIB_PATH)/tol

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
CFLAGS	 = -std=c11
CXXFLAGS = -std=c++17
LDFLAGS	 =
LDLIBS	 = -lSDL3 -lglad -lm -ldl

INCLUDE += -I$(SDL3_PATH)/include
INCLUDE += -I$(GLAD_PATH)/include
INCLUDE += -I$(STB_PATH)
INCLUDE += -I$(TOL_PATH)

LDFLAGS += -L$(BIN_PATH)/sdl
LDFLAGS += -L$(BIN_PATH)/glad

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

define BLD_SDL

echo
echo =====================
echo ----BUILDING SDL3----
echo =====================
echo

cd $(SDL3_PATH) && cmake -S . -DSDL_STATIC=ON -B build && cmake --build build

cp $(SDL3_PATH)/build/libSDL3.so $(BIN_PATH)/sdl
cd $(BIN_PATH)/sdl && ln -s libSDL3.so libSDL3.so.0

echo
echo =====================
echo ----SDL3 FINISHED----
echo =====================
echo

endef

DIRS       += $(BIN_PATH)/sdl
LIBS       += $(BIN_PATH)/sdl/libSDL3.so
CLEAN_LIBS += (rm -r $(SDL3_PATH)/build 2> /dev/null || true);

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

echo "  CC    " $(OBJ_PATH)/glad/gl.o 		&& $(CC) -I$(GLAD_PATH)/include -o $(OBJ_PATH)/glad/gl.o     -c $(GLAD_PATH)/src/gl.c
echo "  CC    " $(OBJ_PATH)/glad/gles.o 	&& $(CC) -I$(GLAD_PATH)/include -o $(OBJ_PATH)/glad/gles2.o  -c $(GLAD_PATH)/src/gles2.c
echo "  CC    " $(OBJ_PATH)/glad/vulkan.o 	&& $(CC) -I$(GLAD_PATH)/include -o $(OBJ_PATH)/glad/vulkan.o -c $(GLAD_PATH)/src/vulkan.c
echo "  AR    " $(BIN_PATH)/glad/libglad.a 	&& $(AR) rcs $(BIN_PATH)/glad/libglad.a $(OBJ_PATH)/glad/gl.o $(OBJ_PATH)/glad/gles2.o $(OBJ_PATH)/glad/vulkan.o

echo
echo =====================
echo ----GLAD FINISHED----
echo =====================
echo

endef

DIRS	   += $(BIN_PATH)/glad $(OBJ_PATH)/glad
LIBS       += $(BIN_PATH)/glad/libglad.a
CLEAN_LIBS += (rm -r $(GLAD_PATH)/obj 2> /dev/null || true);

# =============================



# =============================
# -----------------------------
# BUILD LIBS
# -----------------------------

$(LIBS) &:
	@$(BLD_SDL)
	@$(BLD_GLAD)

# =============================



# =============================
# -----------------------------
# CANS
# -----------------------------

#(namespace, directory, file extension, output)
define DEFVARS

$1_SRC_PATH = $2
$1_SRC_EXT  = $3
$1_TARGET   = $$(addprefix $$($1_BIN_PATH)/,$4)

$1_BIN_PATH = $(BIN_PATH)/$$(shell basename $$($1_SRC_PATH))
$1_OBJ_PATH = $(OBJ_PATH)/$$(shell basename $$($1_SRC_PATH))
$1_DEP_PATH = $(DEP_PATH)/$$(shell basename $$($1_SRC_PATH))

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

$(eval $(call DEFVARS,ENGINE,src/common,c,libVC.a))

$(ENGINE_TARGET): $(ENGINE_OBJ) $(LIBS)
	$(RUN_CMD_AR) $(AR) rcs $@ $(ENGINE_OBJ)

$(ENGINE_OBJ): private INCLUDE  += -I$(ENGINE_SRC_PATH)
$(ENGINE_OBJ): $(ENGINE_OBJ_PATH)/%.o: $(ENGINE_SRC_PATH)/%.$(ENGINE_SRC_EXT)
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(ENGINE_SRC_PATH)/%.$(ENGINE_SRC_EXT)=$(ENGINE_DEP_PATH)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# VC GAME
# -----------------------------

$(eval $(call DEFVARS,GAME,src/game,cc,main))

$(GAME_TARGET): private LDFLAGS += -L$(ENGINE_BIN_PATH)
$(GAME_TARGET): private LDLIBS  += -lstdc++ -lVC
$(GAME_TARGET): $(GAME_OBJ) $(ENGINE_TARGET)
	$(RUN_CMD_LTLINK) $(LD) -o $@ $(GAME_OBJ) $(LDFLAGS) $(LDLIBS)

$(GAME_TARGET).so: private LDFLAGS += -L$(ENGINE_BIN_PATH)
$(GAME_TARGET).so: private LDLIBS  += -lstdc++ -lVC
$(GAME_TARGET).so: $(GAME_OBJ) $(ENGINE_TARGET)
	$(RUN_CMD_LTLINK) $(LD) -shared -o $@ $(GAME_OBJ) $(LDFLAGS) $(LDLIBS)

$(GAME_OBJ): private INCLUDE  += -I$(GAME_SRC_PATH) -I$(ENGINE_SRC_PATH)
$(GAME_OBJ): private CPPFLAGS += -DCGLM_USE_ANONYMOUS_STRUCT=0
$(GAME_OBJ): $(GAME_OBJ_PATH)/%.o: $(GAME_SRC_PATH)/%.$(GAME_SRC_EXT)
	$(RUN_CMD_CXX) $(CXX) $(INCLUDE) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -MF $(<:$(GAME_SRC_PATH)/%.$(GAME_SRC_EXT)=$(GAME_DEP_PATH)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# UNIT TESTS
# -----------------------------

$(eval $(call DEFVARS,TEST,src/test,c,$$(TEST_SRC:$$(TEST_SRC_PATH)/%.c=%)))

$(TEST_TARGET): private LDFLAGS += -L$(ENGINE_BIN_PATH) -L$(GAME_BIN_PATH)
$(TEST_TARGET): private LDLIBS  += -lVC -l:main.so
$(TEST_TARGET): $(TEST_BIN_PATH)/%: $(TEST_OBJ_PATH)/%.o $(ENGINE_TARGET) | $(GAME_TARGET).so
	$(RUN_CMD_LTLINK) $(LD) -o $@ $< $(LDFLAGS) $(LDLIBS)

$(TEST_OBJ): private INCLUDE  += -I$(TEST_SRC_PATH) -I$(GAME_SRC_PATH) -I$(ENGINE_SRC_PATH)
$(TEST_OBJ): private CPPFLAGS += -DINSTANTIATE_MAIN
$(TEST_OBJ): $(TEST_OBJ_PATH)/%.o: $(TEST_SRC_PATH)/%.$(TEST_SRC_EXT)
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(TEST_SRC_PATH)/%.$(TEST_SRC_EXT)=$(TEST_DEP_PATH)/%.d) -MT $@ -o $@ -c $<

# =============================



# =============================
# -----------------------------
# BUILD & RUN & TEST
# -----------------------------

run: build
	@./scripts/run.sh $(GAME_TARGET)

rto: build
	@timeout 5s ./scripts/run.sh $(GAME_TARGET)

build: debug

debug: CPPFLAGS += -DDEBUG
debug: CFLAGS   += -g -Wall -Wextra -Wshadow -ggdb3 -pedantic -fpic -Wno-missing-field-initializers
debug: CXXFLAGS += -g -Wall -Wextra -Wshadow -ggdb3 -pedantic -fpic -Wno-missing-field-initializers
debug: $(GAME_TARGET)

release: CPPFLAGS += -DRELEASE
release: CFLAGS   += -O3 -Wall
release: CXXFLAGS += -O3 -Wall
release: $(GAME_TARGET)

test: CPPFLAGS += -DDEBUG
test: CFLAGS   += -g -Wall -Wextra -Wshadow -ggdb3 -pedantic -fpic -Wno-missing-field-initializers
test: CXXFLAGS += -g -Wall -Wextra -Wshadow -ggdb3 -pedantic -fpic -Wno-missing-field-initializers
test: $(TEST_TARGET)
	@./scripts/run.sh "$(TEST_BIN_PATH)/test-all --enable-mixed-units"

TEST = $(TEST_SRC:$(TEST_SRC_PATH)/%.c=%)
$(TEST): debug
	@./scripts/run.sh "$(TEST_BIN_PATH)/$@ --enable-mixed-units"

PHONY += debug release build run test $(TEST)

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
