cmake_minimum_required(VERSION 3.28)
project(space_invaders_8080 C)
set(CMAKE_C_STANDARD 11)

# SDL2 folder structure and path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2-2.30.3\\x86_64-w64-mingw32")
set(SOURCES src/shell.c
        src/state.c
        src/disassemble8080p.c
        src/video.c
        src/rom_sections.c
        src/libattopng.c
        src/controls.c)

if (WIN32)
    set(SOURCES ${SOURCES} src/timer_win.c)
elseif (APPLE)
    set(SOURCES ${SOURCES} src/timer_apple.c)
else ()
    set(SOURCES ${SOURCES} src/timer_linux.c)
endif ()

# Include SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Create a library with all of the 8080 source code
add_library(8080 ${SOURCES})


link_libraries(8080 ${SDL2_LIBRARY})

# Any executable after this will automatically link the 8080 library

add_executable(space_invaders_8080 src/main.c)


enable_testing()

add_executable(test_sound tests/test_sound.c)
add_test(NAME test_sound1, COMMAND test_sound)