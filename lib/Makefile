# =============================
# -----------------------------
# SDL LIB
# -----------------------------

BLDLIBS += (echo ----BUILDING SDL3----);
BLDLIBS += (cd SDL3 && cmake -S . -B build && cmake --build build);
BLDLIBS += (mkdir -p ../bld/sdl3/bin);
BLDLIBS += (cp SDL3/build/libSDL3.so ../bld/sdl3/bin);
CLEAN   += (cd SDL3 && cmake --build build --target clean);

# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

BLDLIBS += (echo ----BUILDING GLAD----);
BLDLIBS += (cd glad && mkdir -p obj && $(CC) -Iinclude -o obj/glad.o -c -fpic src/glad.c);
BLDLIBS += (echo [100%] built target glad);
BLDLIBS += (mkdir -p ../bld/glad/bin);
BLDLIBS += (cp glad/obj/glad.o ../bld/glad/bin);
CLEAN   += (rm -r glad/obj 2> /dev/null || true);

# =============================



# =============================
# -----------------------------
# CGLM LIB
# -----------------------------

ifeq ($(UNAME),Windows)
    CGLMEX = -G "MinGW Makefiles"
endif

BLDLIBS += (echo ----BUILDING CGLM----);
BLDLIBS += (cd cglm && cmake . -DCGLM_STATIC=ON $(CGLMEX) && make);
BLDLIBS += (mkdir -p ../bld/cglm/bin);
BLDLIBS += (cp cglm/libcglm.a ../bld/cglm/bin);
CLEAN   += (cd cglm && make clean);

# =============================



# =============================
# -----------------------------
# ENTRY POINT
# -----------------------------

build:
	@$(BLDLIBS)
	@echo > build

# =============================



# =============================
# -----------------------------
# REMOVE BUILD FILES
# -----------------------------

clean:
	@$(CLEAN)
	@rm build

# =============================

.PHONY: clean all
