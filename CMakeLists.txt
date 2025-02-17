cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(sdl_include src/extern/sdl/include)
set(glad_include src/extern/glad/include)
set(glad_headers src/extern/glad/include/glad/gl.h)
set(glad_sources src/extern/glad/src/gl.c)

set(platform_include src)
set(platform_headers
	src/graphics/shader.h
	src/graphics/vao.h
	src/graphics/vbo.h
	src/math/color.h
	src/math/math.h
	src/math/matrix.h
	src/math/quat.h
	src/math/vector.h
	src/system/audio.h
	src/system/global.h
	src/system/input.h
	src/system/system.h
	src/system/time.h
	src/system/window.h
	src/util/timestep.h
	src/util/camera.h
	src/util/kdtree.h
	src/util/list.h
	src/util/log.h
	src/util/types.h
	src/util/util.h
	src/platform.h)

set(platform_sources
	src/graphics/shader.c
	src/graphics/vao.c
	src/graphics/vbo.c
	src/system/audio.c
	src/system/input.c
	src/system/system.c
	src/system/time.c
	src/system/window.c
	src/util/camera.c
	src/util/kdtree.c
	src/util/log.c)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_TEST_LIBRARY OFF)
set(SDL_TEST OFF)
add_subdirectory(src/extern/sdl EXCLUDE_FROM_ALL)

project(platform)
add_library(platform STATIC ${platform_sources} ${platform_headers} ${glad_sources} ${glad_headers})
target_include_directories(platform PUBLIC ${platform_include} ${glad_include})
target_link_libraries(platform SDL3::SDL3)
