# =============================
# -----------------------------
# SDL LIB
# -----------------------------

#TODO: make sure this can compile in windows aswell
INCLUDE += -I$(LIB_DIR)/SDL3/include
LDFLAGS += -L$(LIB_DIR)/SDL3/build
LDLIBS += -l:libSDL3.so
LIBS += $(LIB_DIR)/SDL3/build/libSDL3.so

SDL3/build/libSDL3.so:
	$(RUN_CMD_AR) (cd SDL3 && cmake -S . -B build && cmake --build build)

CLEAN += (cd $(LIB_DIR)/SDL3 && cmake --build build --target clean);

# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

INCLUDE += -I$(LIB_DIR)/glad/include
LIBS    += $(LIB_DIR)/glad/obj/glad.o

glad/obj/glad.o:
	$(RUN_CMD_CC) (cd glad && mkdir -p obj && $(CC) -Iinclude -o obj/glad.o -c -fpic src/glad.c)

CLEAN += (rm -r $(LIB_DIR)/glad/obj 2> /dev/null || true);

# =============================



# =============================
# -----------------------------
# CGLM LIB
# -----------------------------

INCLUDE += -Icglm/include
LIBS    += $(LIB_DIR)/cglm/libcglm.a

ifeq ($(UNAME),Windows)
    CGLMEX = -G "MinGW Makefiles"
endif

cglm/libcglm.a:
	$(RUN_CMD_AR) (cd cglm && cmake . -DCGLM_STATIC=ON $(CGLMEX) && make)

CLEAN += (cd $(LIB_DIR)/cglm && make clean);

# =============================
