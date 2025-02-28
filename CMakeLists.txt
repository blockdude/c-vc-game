cmake_minimum_required(VERSION 3.25)

set(sdl_include "extern/sdl/include")
set(glad_include "extern/glad/include")
set(glad_headers "extern/glad/include/glad/gl.h")
set(glad_sources "extern/glad/src/gl.c")

set(platform_include "src")
set(platform_headers
	"src/graphics/shader.h"
	"src/graphics/vao.h"
	"src/graphics/vbo.h"
	"src/math/color.h"
	"src/math/math.h"
	"src/math/mat4.h"
	"src/math/quat.h"
	"src/math/vec2.h"
	"src/math/vec3.h"
	"src/math/vec4.h"
	"src/system/audio.h"
	"src/system/global.h"
	"src/system/input.h"
	"src/system/time.h"
	"src/system/window.h"
	"src/system/allocator.h"
	"src/util/timestep.h"
	"src/util/camera.h"
	"src/util/kdtree.h"
	"src/util/list.h"
	"src/util/log.h"
	"src/util/types.h"
	"src/util/util.h"
	"src/common.h"
	"src/version.h"
	"src/platform.h")

set(platform_sources
	"src/platform.c"
	"src/math/math.c"
	"src/graphics/shader.c"
	"src/graphics/vao.c"
	"src/graphics/vbo.c"
	"src/system/audio.c"
	"src/system/input.c"
	"src/system/time.c"
	"src/system/window.c"
	"src/system/allocator.c"
	"src/util/kdtree.c"
	"src/util/log.c")

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_TEST_LIBRARY OFF)
set(SDL_TEST OFF)
add_subdirectory(extern/sdl EXCLUDE_FROM_ALL)

project(platform C)
add_library(platform STATIC ${platform_sources} ${glad_sources})
target_include_directories(platform PUBLIC ${platform_include} ${glad_include})
target_link_libraries(platform PUBLIC SDL3::SDL3)
