cmake_minimum_required(VERSION 3.28)
project(space_invaders_8080 C)

set(CMAKE_C_STANDARD 11)

add_executable(space_invaders_8080 src/main.c
        include/foo.h
        src/disassemble8080p.c)

enable_testing()

add_executable(test_test tests/test_test.c)

add_test(NAME test1 COMMAND test_test 1)
