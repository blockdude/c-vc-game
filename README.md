# VCPlatform

A C17 static library wrapping SDL3 and OpenGL for game and app development.

## Dependencies

Vendored in `extern/`:

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
| window | `src/system/window.c` | SDL window + OpenGL context |
| input | `src/system/input.c` | Keyboard, mouse, text input |
| audio | `src/system/audio.c` | SDL audio output |
| time | `src/system/time.c` | High-resolution timing |
| math | `src/math/math.c` | Vec2/3/4, quat, mat4, shapes |
| shader | `src/graphics/shader.c` | GLSL shader compilation/linking, VAO/VBO |
| camera | `src/util/camera.c` | 3D camera (proj/view) |
| timestep | `src/util/timestep.c` | Fixed/variable timestep |
| log | `src/util/log.c` | Logging with callbacks |
