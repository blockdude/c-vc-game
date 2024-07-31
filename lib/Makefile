# =============================
# -----------------------------
# SDL LIB
# -----------------------------

BLDLIBS += (echo ----BUILDING SDL3----);
BLDLIBS += (cd SDL3 && cmake -S . -B build && cmake --build build);
BLDLIBS += (mkdir -p ../bld/bin/sdl3);
BLDLIBS += (cp SDL3/build/libSDL3.so.*.*.* ../bld/bin/sdl3);
BLDLIBS += (cd ../bld/bin/sdl3 && ln -s libSDL3.so.*.*.* libSDL3.so.0 && ln -s libSDL3.so.*.*.* libSDL3.so);
CLEAN   += (cd SDL3 && cmake --build build --target clean);

# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

BLDLIBS += (echo ----BUILDING GLAD----);
BLDLIBS += (cd glad && mkdir -p obj && $(CC) -Iinclude -o obj/glad.o -c -fpic src/glad.c);
BLDLIBS += (echo [100%] built target glad);
BLDLIBS += (mkdir -p ../bld/bin/glad);
BLDLIBS += (cp glad/obj/glad.o ../bld/bin/glad);
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
BLDLIBS += (mkdir -p ../bld/bin/cglm);
BLDLIBS += (cp cglm/libcglm.a ../bld/bin/cglm);
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
	@rm build 2> /dev/null || true

# =============================

.PHONY: clean all
