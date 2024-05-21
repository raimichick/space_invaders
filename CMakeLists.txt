cmake_minimum_required(VERSION 3.28)
project(space_invaders_8080 C)
set(CMAKE_C_STANDARD 11)

# SDL2 folder structure and path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2-2.30.3\\x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "SDL2_mixer-2.8.0\\x86_64-w64-mingw32")

# Include SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

# Create a library with all of the 8080 source code
add_library(8080
        src/shell.c
        src/state.c
        src/disassemble8080p.c
        src/video.c
        src/sound.c
        src/rom_sections.c
        src/libattopng.c
        src/machine.c)

# Any executable after this will automatically link the 8080 library
link_libraries(8080 ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY})

add_compile_definitions(ROOT_DIR="${PROJECT_SOURCE_DIR}")

add_executable(space_invaders_8080 src/main.c)

# Build and add tests only in debug, not release
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    enable_testing()
    add_subdirectory(tests)
endif ()