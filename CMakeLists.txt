cmake_minimum_required(VERSION 3.28)
project(space_invaders_8080 C)

set(CMAKE_C_STANDARD 11)

add_executable(space_invaders_8080 src/main.c
        include/foo.h
        src/disassemble8080p.c
        src/shell.c
        include/structs.h)

enable_testing()

# Add your test file as an executable, first argument is executable name and second is path to file to convert to executable
add_executable(mov_reg_to_reg tests/test_mov_reg_to_reg.c)
add_executable(test_mov_mem_to_reg tests/test_mov_mem_to_reg.c)
add_executable(test_mov_reg_to_mem tests/test_mov_reg_to_mem.c)

# MOV REG to REG Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_a_d COMMAND mov_reg_to_reg 0x7a)
add_test(NAME mov_a_e COMMAND mov_reg_to_reg 0x7b)
add_test(NAME mov_a_h COMMAND mov_reg_to_reg 0x7c)

# MOV MEM to REG Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_a_m COMMAND test_mov_mem_to_reg 0x7e)

# MOV REG to MEM Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_m_a COMMAND test_mov_reg_to_mem 0x77)