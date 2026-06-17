cmake_minimum_required(VERSION 3.25)

set(stb_include "extern/stb")
set(sdl_include "extern/sdl/include")
set(glad_include "extern/glad/include")
set(glad_headers "extern/glad/include/glad/gl.h")
set(glad_sources "extern/glad/src/gl.c")

set(platform_include "include")
set(platform_headers
	"include/vcp/vcp.h")

set(stb_source "${CMAKE_CURRENT_BINARY_DIR}/generated/stb.generated.c")
file(WRITE ${stb_source}
	"#define STB_IMAGE_IMPLEMENTATION\n"     "#include \"stb_image.h\"\n"
	"#define STB_PERLIN_IMPLEMENTATION\n"    "#include \"stb_perlin.h\"\n"
	"#define STB_RECT_PACK_IMPLEMENTATION\n" "#include \"stb_rect_pack.h\"\n"
)

set(platform_sources
	"src/math/math.c"
	"src/graphics/shader.c"
	"src/graphics/vao.c"
	"src/graphics/vbo.c"
	"src/system/audio.c"
	"src/system/input.c"
	"src/system/time.c"
	"src/system/window.c"
	"src/util/timestep.c"
	"src/util/camera.c"
	"src/util/log.c"
	"src/platform.c")

set_source_files_properties(${platform_sources} ${platform_headers} PROPERTIES LANGUAGE C)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_TEST_LIBRARY OFF)
set(SDL_TEST OFF)
add_subdirectory(extern/sdl EXCLUDE_FROM_ALL)

project(platform LANGUAGES C VERSION "0.0.0.0")
add_library(platform STATIC ${platform_sources} ${glad_sources} ${stb_source})
target_include_directories(platform PUBLIC ${platform_include} ${glad_include} ${stb_include})
target_link_libraries(platform PUBLIC SDL3::SDL3)
set_property(TARGET platform PROPERTY C_STANDARD 17)

# --- Tests ---
include(CTest)

add_executable(test-platform
	"tests/test-all.c"
)
target_include_directories(test-platform PRIVATE
	${platform_include}
	"tests"
)
target_link_libraries(test-platform PRIVATE
	platform
	SDL3::SDL3
)
set_property(TARGET test-platform PROPERTY C_STANDARD 17)
add_test(NAME test-platform COMMAND test-platform)
