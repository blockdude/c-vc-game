cmake_minimum_required(VERSION 3.25)
project(platform LANGUAGES C)

# --- Dependencies ---

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_TEST_LIBRARY OFF)
set(SDL_TEST OFF)
add_subdirectory(extern/sdl EXCLUDE_FROM_ALL)

# --- Library ---

set(stb_include "extern/stb")
set(sdl_include "extern/sdl/include")
set(glad_include "extern/glad/include")
set(glad_sources "extern/glad/src/gl.c")

set(stb_sources "${CMAKE_CURRENT_BINARY_DIR}/generated/stb.generated.c")
file(WRITE ${stb_sources}
	"#define STB_IMAGE_IMPLEMENTATION\n"     "#include \"stb_image.h\"\n"
	"#define STB_PERLIN_IMPLEMENTATION\n"    "#include \"stb_perlin.h\"\n"
	"#define STB_RECT_PACK_IMPLEMENTATION\n" "#include \"stb_rect_pack.h\"\n"
)

set(platform_include "include")
set(platform_headers
	"include/vcp/vcp.h")

set(platform_sources
	"src/math.c"
	"src/audio.c"
	"src/input.c"
	"src/time.c"
	"src/window.c"
	"src/clock.c"
	"src/log.c"
	"src/platform.c")

add_library(platform STATIC ${platform_sources} ${glad_sources} ${stb_sources})
target_include_directories(platform PUBLIC ${platform_include} ${glad_include} ${stb_include})
target_link_libraries(platform PUBLIC SDL3::SDL3)

target_compile_definitions(platform PRIVATE
    VCP_BUILD_TYPE="$<CONFIG>"
    VCP_BUILD_DEBUG=$<IF:$<CONFIG:Debug>,1,0>
    VCP_BUILD_RELEASE=$<IF:$<CONFIG:Release>,1,0>
    VCP_BUILD_PROFILE=$<IF:$<CONFIG:Profile>,1,0>
)

set_target_properties(platform PROPERTIES
    LANGUAGE C
    C_STANDARD 17
)

# --- Version generation ---

set(version_script "${CMAKE_CURRENT_BINARY_DIR}/generated/embed_version.cmake")
set(version_c     "${CMAKE_CURRENT_BINARY_DIR}/generated/version.generated.c")

file(WRITE ${version_script} [=[
execute_process(
    COMMAND git rev-list --count HEAD
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE BN OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE CM OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE CM_FULL OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE BR OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git describe --tags --always --dirty
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE TG OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git describe --tags --long --always
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE TG_LONG OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git log -1 --format=%ct
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE EP OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(ENV{SOURCE_DATE_EPOCH} ${EP})
string(TIMESTAMP TS "%Y-%m-%dT%H:%M:%SZ" UTC)

if(TG_LONG MATCHES "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+)-([0-9]+)-g")
    set(VERSION_MAJOR   ${CMAKE_MATCH_1})
    set(VERSION_MINOR   ${CMAKE_MATCH_2})
    set(VERSION_PATCH   ${CMAKE_MATCH_3})
    set(VERSION_RELATIVE ${CMAKE_MATCH_4})
else()
    set(VERSION_MAJOR   0)
    set(VERSION_MINOR   0)
    set(VERSION_PATCH   0)
    set(VERSION_RELATIVE 0)
endif()

if(TG MATCHES "-dirty$")
    set(VERSION_DIRTY 1)
else()
    set(VERSION_DIRTY 0)
endif()

set(CONTENT
"#include <stdbool.h>
extern const int VCP_VERSION_MAJOR = ${VERSION_MAJOR};
extern const int VCP_VERSION_MINOR = ${VERSION_MINOR};
extern const int VCP_VERSION_PATCH = ${VERSION_PATCH};
extern const int VCP_VERSION_BUILD = ${VERSION_RELATIVE};
extern const int VCP_VERSION_BUILD_ABSOLUTE = ${BN};
extern const bool VCP_VERSION_DIRTY = ${VERSION_DIRTY};
extern const char* const VCP_VERSION_COMMIT = \"${CM}\";
extern const char* const VCP_VERSION_COMMIT_FULL = \"${CM_FULL}\";
extern const char* const VCP_VERSION_BRANCH = \"${BR}\";
extern const char* const VCP_VERSION_TAG = \"${TG}\";
extern const char* const VCP_VERSION_TIMESTAMP = \"${TS}\";
extern const char* const VCP_VERSION_STRING = \"v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} (Build ${BN})\";
extern const long long VCP_VERSION_EPOCH = ${EP};")

if(EXISTS "${out}")
    file(READ "${out}" OLD)
    if(OLD STREQUAL CONTENT)
        return()
    endif()
endif()
file(WRITE "${out}" "${CONTENT}")
]=])

add_custom_target(generate_vcp_version ALL
    COMMAND ${CMAKE_COMMAND} "-Dout=${version_c}" "-DSRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}" -P ${version_script}
    BYPRODUCTS ${version_c}
    COMMENT "Generating version info..."
)
add_dependencies(platform generate_vcp_version)
set_source_files_properties(${version_c} PROPERTIES GENERATED TRUE)
target_sources(platform PRIVATE ${version_c})
target_include_directories(platform PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)

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
