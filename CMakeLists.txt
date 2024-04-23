cmake_minimum_required(VERSION 3.28)
project(space_invaders_8080 C)

set(CMAKE_C_STANDARD 11)

add_executable(space_invaders_8080 src/main.c
        include/foo.h
        src/disassemble8080p.c
        src/shell.c
        src/state.c
        include/state.h)

enable_testing()

# DAMIAN's TESTS
# Add your test file as an executable, first argument is executable name and second is path to file to convert to executable
add_executable(mov_reg_to_reg tests/test_mov_reg_to_reg.c src/state.c src/shell.c)
add_executable(test_mov_mem_to_reg tests/test_mov_mem_to_reg.c src/state.c src/shell.c)
add_executable(test_mov_reg_to_mem tests/test_mov_reg_to_mem.c src/state.c src/shell.c)
add_executable(test_return tests/test_return.c src/state.c src/shell.c)
add_executable(test_adi tests/test_adi.c src/state.c src/shell.c)
add_executable(test_jump tests/test_jump.c src/state.c src/shell.c)
add_executable(test_xra_reg tests/test_xra_reg.c src/state.c src/shell.c)
add_executable(test_ana_reg tests/test_ana_reg.c src/state.c src/shell.c)

# MOV REG to REG Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_a_d COMMAND mov_reg_to_reg 0x7a)
add_test(NAME mov_a_e COMMAND mov_reg_to_reg 0x7b)
add_test(NAME mov_a_h COMMAND mov_reg_to_reg 0x7c)

# MOV MEM to REG Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_a_m COMMAND test_mov_mem_to_reg 0x7e)

# MOV REG to MEM Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_m_a COMMAND test_mov_reg_to_mem 0x77)

# ANA REG Tests
add_test(NAME ana_a COMMAND test_ana_reg 0xa7)

# NICK's TESTS
add_executable(test_load tests/test_load.c src/state.c src/shell.c)

# add_test(NAME test1 COMMAND test_test 1)
add_test(NAME test_LXI_B COMMAND test_load 0x01)
add_test(NAME test_LXI_D COMMAND test_load 0x11)
add_test(NAME test_LDAX_D COMMAND test_load 0x1a)

