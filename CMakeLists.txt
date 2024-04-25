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

# XRA REG Tests
add_test(NAME xra_a COMMAND test_xra_reg 0xaf)

# Jump Tests
add_test(NAME jnz COMMAND test_jump 0xc2)
add_test(NAME jmp COMMAND test_jump 0xc3)

# Pop Tests
add_test(NAME pop_b COMMAND test_push_pop 0xc1)

# Push Tests
add_test(NAME push_b COMMAND test_push_pop 0xc5)

# ADI D8 Test
# TODO move this to test_immediates?
add_test(NAME adi_d8 COMMAND test_adi 0xc6)

# Return Tests
add_test(NAME ret COMMAND test_return 0xc9)

# NICK's TESTS
add_executable(test_load tests/test_load.c src/state.c src/shell.c)
add_executable(test_add tests/test_add.c src/state.c src/shell.c)
add_executable(test_subtract tests/test_subtract.c src/state.c src/shell.c)
add_executable(test_move_immediate tests/test_move_immediate.c src/state.c src/shell.c)
add_executable(test_rotate tests/test_rotate.c src/state.c src/shell.c)

# Test Load Instructions
add_test(NAME test_LXI_B COMMAND test_load 0x01)
add_test(NAME test_LXI_D COMMAND test_load 0x11)
add_test(NAME test_LDAX_D COMMAND test_load 0x1a)

# Test Add Instructions
add_test(NAME test_DAD_B COMMAND test_add 0x09)
add_test(NAME test_INX_D COMMAND test_add 0x13)
add_test(NAME test_DAD_D COMMAND test_add 0x19)

# Test Subtract Instructions
add_test(NAME test_DCR_B COMMAND test_subtract 0x05)
add_test(NAME test_DCR_C COMMAND test_subtract 0x0d)

# Test Move Immediate Instructions
add_test(NAME test_MVI_B COMMAND test_move_immediate 0x06)
add_test(NAME test_MVI_C COMMAND test_move_immediate 0x0e)

# Test Rotate Instructions
add_test(NAME test_RRC COMMAND test_rotate 0x0f)

# CRAIG's TESTS
add_executable(test_push_pop tests/test_push_pop.c src/state.c src/shell.c)
add_test(NAME test_POP_D, COMMAND test_push_pop 0xd1)
add_test(NAME test_PUSH_D, COMMAND test_push_pop 0xd5)
add_test(NAME test_POP_H, COMMAND test_push_pop 0xe1)
add_test(NAME test_PUSH_H, COMMAND test_push_pop 0xe5)
add_test(NAME test_POP_PSW, COMMAND test_push_pop 0xf1)
add_test(NAME test_PUSH_PSW, COMMAND test_push_pop 0xf5)

add_executable(test_call tests/test_call.c src/state.c src/shell.c)
add_test(NAME test_CALL, COMMAND test_call 0xcd)

add_executable(test_immediates tests/test_immediates.c src/state.c src/shell.c)
add_test(NAME test_ANI_D8, COMMAND test_immediates 0xe6)
