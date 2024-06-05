cmake_minimum_required(VERSION 3.28)
project(space_invaders_8080 C)
set(CMAKE_C_STANDARD 11)

# SDL2 folder structure and path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# Set CMAKE_PREFIX_PATH to include the Homebrew installation directory
if (APPLE)
    if (EXISTS "/opt/homebrew")
        # Apple Silicon Homebrew location
        set(CMAKE_PREFIX_PATH "/opt/homebrew")
    else ()
        # Intel Homebrew location
        set(CMAKE_PREFIX_PATH "/usr/local")
    endif ()
elseif (WIN32)
    set(SDL2_PATH "SDL2-2.30.3\\x86_64-w64-mingw32")
    set(SDL2_MIXER_PATH "SDL2_mixer-2.8.0\\x86_64-w64-mingw32")
    set(SDL2_IMAGE_PATH "SDL2_image-2.8.2\\x86_64-w64-mingw32")
endif ()

set(SOURCES src/shell.c
        src/state.c
        src/disassemble8080p.c
        src/video.c
        src/sound.c
        src/rom_sections.c
        src/libattopng.c
        src/controls.c
        src/machine.c)

if (WIN32)
    set(SOURCES ${SOURCES} src/timer_win.c)
elseif (APPLE)
    set(SOURCES ${SOURCES} src/timer_apple.c)
else ()
    set(SOURCES ${SOURCES} src/timer_linux.c
            include/settings.h)
endif ()

# Include SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# Create a library with all of the 8080 source code
add_library(8080 ${SOURCES})

# Any executable after this will automatically link the 8080 library
link_libraries(8080 ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

add_compile_definitions(ROOT_DIR="${PROJECT_SOURCE_DIR}")

add_executable(space_invaders_8080 src/main.c)

# Copy the SDL2 dlls to the build folder
add_custom_command(
        TARGET space_invaders_8080 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/SDL2-2.30.3/x86_64-w64-mingw32/bin/SDL2.dll
        ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll)

add_custom_command(
        TARGET space_invaders_8080 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/SDL2_mixer-2.8.0/x86_64-w64-mingw32/bin/SDL2_mixer.dll
        ${CMAKE_CURRENT_BINARY_DIR}/SDL2_mixer.dll)

add_custom_command(
        TARGET space_invaders_8080 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/SDL2_image-2.8.2/x86_64-w64-mingw32/bin/SDL2_image.dll
        ${CMAKE_CURRENT_BINARY_DIR}/SDL2_image.dll)

# Build and add tests only in debug, not release
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    enable_testing()
    add_subdirectory(tests)

    # Copy the SDL2 dlls to the test folder
    add_custom_command(
            TARGET space_invaders_8080 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/SDL2-2.30.3/x86_64-w64-mingw32/bin/SDL2.dll
            ${CMAKE_CURRENT_BINARY_DIR}/tests/SDL2.dll)

    add_custom_command(
            TARGET space_invaders_8080 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/SDL2_mixer-2.8.0/x86_64-w64-mingw32/bin/SDL2_mixer.dll
            ${CMAKE_CURRENT_BINARY_DIR}/tests/SDL2_mixer.dll)

    add_custom_command(
            TARGET space_invaders_8080 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/SDL2_image-2.8.2/x86_64-w64-mingw32/bin/SDL2_image.dll
            ${CMAKE_CURRENT_BINARY_DIR}/SDL2_image.dll)
endif ()