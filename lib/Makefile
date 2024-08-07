# =============================
# -----------------------------
# SDL LIB
# -----------------------------

define BLD_SDL

@echo ----BUILDING SDL3----

# BUILD SDL
@cd SDL3 && cmake -S . -B build && cmake --build build

# COPY SDL TO BUILD LOCATION
@mkdir -p ../bld/bin/sdl3
@cp SDL3/build/libSDL3.so ../bld/bin/sdl3
@ln -s ../bld/bin/sdl3/libSDL3.so ../bld/bin/sdl3/libSDL3.so.0

endef

TARGETS += ../bld/bin/sdl3/libSDL3.so
CLEAN   += (cd SDL3 && cmake --build build --target clean);

# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

TARGETS += ../bld/bin/glad/glad.o
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

TARGETS += ../bld/bin/cglm/libcglm.a
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

all: $(TARGETS)

$(TARGETS) &:
	$(BLD_SDL)
	@$(BLDLIBS)

# =============================



# =============================
# -----------------------------
# REMOVE BUILD FILES
# -----------------------------

clean:
	@$(CLEAN)

# =============================

.PHONY: clean all
