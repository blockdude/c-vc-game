cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(sdl_include src/extern/sdl/include)
set(glad_include src/extern/glad/include)
set(glad_headers
	src/extern/glad/include/glad/gl.h
	src/extern/glad/include/glad/gles2.h
	src/extern/glad/include/glad/vulkan.h
	src/extern/glad/include/KHR/khrplatform.h
	src/extern/glad/include/vk_video/vulkan_video_codec_av1std.h
	src/extern/glad/include/vk_video/vulkan_video_codec_av1std_decode.h
	src/extern/glad/include/vk_video/vulkan_video_codec_h264std.h
	src/extern/glad/include/vk_video/vulkan_video_codec_h264std_decode.h
	src/extern/glad/include/vk_video/vulkan_video_codec_h264std_encode.h
	src/extern/glad/include/vk_video/vulkan_video_codec_h265std.h
	src/extern/glad/include/vk_video/vulkan_video_codec_h265std_decode.h
	src/extern/glad/include/vk_video/vulkan_video_codec_h265std_encode.h
	src/extern/glad/include/vk_video/vulkan_video_codecs_common.h
	src/extern/glad/include/vk_platform.h)

set(glad_sources 
	src/extern/glad/src/gl.c
	src/extern/glad/src/gles2.c
	src/extern/glad/src/vulkan.c)

set(platform_include src/common)
set(platform_headers
	src/common/graphics/mesh.h
	src/common/graphics/shader.h
	src/common/graphics/vao.h
	src/common/graphics/vbo.h
	src/common/math/color.h
	src/common/math/math.h
	src/common/math/matrix.h
	src/common/math/quat.h
	src/common/math/vector.h
	src/common/system/audio.h
	src/common/system/global.h
	src/common/system/input.h
	src/common/system/system.h
	src/common/system/time.h
	src/common/system/timestep.h
	src/common/system/window.h
	src/common/util/camera.h
	src/common/util/ecs.h
	src/common/util/hashmap.h
	src/common/util/hashset.h
	src/common/util/kdtree.h
	src/common/util/linkedlist.h
	src/common/util/list.h
	src/common/util/log.h
	src/common/util/state.h
	src/common/util/types.h
	src/common/util/util.h
	src/common/common.h)

set(platform_sources
	src/common/graphics/mesh.c
	src/common/graphics/shader.c
	src/common/graphics/vao.c
	src/common/graphics/vbo.c
	src/common/system/audio.c
	src/common/system/input.c
	src/common/system/system.c
	src/common/system/time.c
	src/common/system/window.c
	src/common/util/camera.c
	src/common/util/ecs.c
	src/common/util/kdtree.c
	src/common/util/linkedlist.c
	src/common/util/log.c
	src/common/util/state.c)

set(game_include src/game)
set(game_headers
	src/game/Game.h
	src/game/Renderer.h)

set(game_sources
	src/game/Game.cc
	src/game/main.cc
	src/game/Renderer.cc)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_TEST_LIBRARY OFF)
set(SDL_TEST OFF)
add_subdirectory(src/extern/sdl EXCLUDE_FROM_ALL)

project(glad)
add_library(glad STATIC ${glad_sources} ${glad_headers})
target_include_directories(glad PUBLIC ${glad_include})

project(platform)
add_library(platform STATIC ${platform_sources} ${platform_headers})
target_include_directories(platform PUBLIC ${platform_include})
target_link_libraries(platform glad m dl SDL3::SDL3)

project(game)
add_compile_definitions(LOG_USE_COLOR)
add_executable(game ${game_sources} ${game_headers})
target_include_directories(game PUBLIC ${game_include})
target_link_libraries(game platform)
