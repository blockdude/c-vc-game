# VCPlatform

A C17 static library wrapping SDL3 and OpenGL for game and app development.

## Dependencies

External modules in `extern/`:

| Library | Purpose |
|---------|---------|
| [SDL3](https://github.com/libsdl-org/SDL) | Windowing, input, audio, timing |
| [glad](https://glad.sh/) | OpenGL 4.6 core loader |
| [stb](https://github.com/nothings/stb) | Image loading |
| [tol](https://github.com/syoyo/tinyobjloader-c) | Tiny OBJ loader |
| [utest](https://github.com/sheredom/utest.h) | Unit test framework (in `test/`) |

## Build

### CMake (primary, Windows)

```sh
cmake -S . -B build
cmake --build build
```

## Modules

| Module | Path | Description |
|--------|------|-------------|
| platform | `src/platform.c` | Init/deinit lifecycle |
| window | `src/window.c` | SDL window + OpenGL context |
| input | `src/input.c` | Keyboard, mouse, text input |
| audio | `src/audio.c` | SDL audio output |
| time | `src/time.c` | High-resolution timing |
| math | `src/math.c` | Vec2/3/4, quat, mat4, shapes |
| timestep | `src/timestep.c` | Fixed/variable timestep |
| log | `src/log.c` | Logging with callbacks |
