# =============================
# -----------------------------
# SDL LIB
# -----------------------------

define BLD_SDL3

@echo ----BUILDING SDL3----

# BUILD SDL
@cd SDL3 && cmake -S . -B build && cmake --build build

# COPY SDL TO BUILD LOCATION
@mkdir -p ../bld/bin/sdl3
@cp SDL3/build/libSDL3.so ../bld/bin/sdl3
@cd ../bld/bin/sdl3 && ln -s libSDL3.so libSDL3.so.0

endef

TARGETS += ../bld/bin/sdl3/libSDL3.so
CLEAN   += (cd SDL3 && cmake --build build --target clean);

# =============================



# =============================
# -----------------------------
# GLAD LIB
# -----------------------------

define BLD_GLAD

@echo ----BUILDING GLAD----

@cd glad && mkdir -p obj && $(CC) -Iinclude -o obj/glad.o -c -fpic src/glad.c
@echo [100%] built target glad

@mkdir -p ../bld/bin/glad
@cp glad/obj/glad.o ../bld/bin/glad

endef

TARGETS += ../bld/bin/glad/glad.o
BLDLIBS += (CLEAN   += (rm -r glad/obj 2> /dev/null || true);

# =============================



# =============================
# -----------------------------
# CGLM LIB
# -----------------------------

ifeq ($(UNAME),Windows)
    CGLMEX = -G "MinGW Makefiles"
endif

define BLD_CGLM

@echo ----BUILDING CGLM----
@cd cglm && cmake . -DCGLM_STATIC=ON $(CGLMEX) && make
@mkdir -p ../bld/bin/cglm
@cp cglm/libcglm.a ../bld/bin/cglm

endef

TARGETS += ../bld/bin/cglm/libcglm.a
CLEAN   += (cd cglm && make clean);

# =============================



# =============================
# -----------------------------
# ENTRY POINT
# -----------------------------

all: $(TARGETS)

$(TARGETS) &:
	$(BLD_SDL3)
	$(BLD_GLAD)
	$(BLD_CGLM)

# =============================



# =============================
# -----------------------------
# REMOVE BUILD FILES
# -----------------------------

clean:
	@$(CLEAN)

# =============================

.PHONY: clean all
