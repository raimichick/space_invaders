cmake_minimum_required(VERSION 3.28)
project(space_invaders_8080 C)
set(CMAKE_C_STANDARD 11)

# Create a library with all of the 8080 source code
add_library(8080 src/shell.c src/state.c src/disassemble8080p.c)

# Any executable after this will automatically link the 8080 library
link_libraries(8080)

add_executable(space_invaders_8080 src/main.c)

enable_testing()

# DAMIAN's TESTS
# Add your test file as an executable, first argument is executable name and second is path to file to convert to executable
add_executable(mov_reg_to_reg tests/test_mov_reg_to_reg.c)
add_executable(test_mov_mem_to_reg tests/test_mov_mem_to_reg.c)
add_executable(test_mov_reg_to_mem tests/test_mov_reg_to_mem.c)
add_executable(test_return tests/test_return.c)
add_executable(test_adi tests/test_adi.c)
add_executable(test_jump tests/test_jump.c)
add_executable(test_xra_xri tests/test_xra_xri.c)
add_executable(test_ana_reg tests/test_ana_reg.c)
add_executable(test_ora_ori tests/test_ora_ori.c)

# MOV REG to REG Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_a_d COMMAND mov_reg_to_reg 0x7a)
add_test(NAME mov_a_e COMMAND mov_reg_to_reg 0x7b)
add_test(NAME mov_a_h COMMAND mov_reg_to_reg 0x7c)

# MOV MEM to REG Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_a_m COMMAND test_mov_mem_to_reg 0x7e)

# MOV REG to MEM Tests - create a unique name, use the opcode as the first argument for the executable (COMMAND function_name arg1)
add_test(NAME mov_m_a COMMAND test_mov_reg_to_mem 0x77)

# ANA REG Tests
add_test(NAME ana_b COMMAND test_ana_reg 0xa0)
add_test(NAME ana_c COMMAND test_ana_reg 0xa1)
add_test(NAME ana_d COMMAND test_ana_reg 0xa2)
add_test(NAME ana_e COMMAND test_ana_reg 0xa3)
add_test(NAME ana_h COMMAND test_ana_reg 0xa4)
add_test(NAME ana_l COMMAND test_ana_reg 0xa5)
add_test(NAME ana_m COMMAND test_ana_reg 0xa6)
add_test(NAME ana_a COMMAND test_ana_reg 0xa7)

# XRA and XRI Tests
add_test(NAME xra_b COMMAND test_xra_xri 0xa8)
add_test(NAME xra_c COMMAND test_xra_xri 0xa9)
add_test(NAME xra_d COMMAND test_xra_xri 0xaa)
add_test(NAME xra_e COMMAND test_xra_xri 0xab)
add_test(NAME xra_h COMMAND test_xra_xri 0xac)
add_test(NAME xra_l COMMAND test_xra_xri 0xad)
add_test(NAME xra_m COMMAND test_xra_xri 0xae)
add_test(NAME xra_a COMMAND test_xra_xri 0xaf)
add_test(NAME xri COMMAND test_xra_xri 0xee)

# ORA and ORI Tests
add_test(NAME ora_b COMMAND test_ora_ori 0xb0)
add_test(NAME ora_c COMMAND test_ora_ori 0xb1)
add_test(NAME ora_d COMMAND test_ora_ori 0xb2)
add_test(NAME ora_e COMMAND test_ora_ori 0xb3)
add_test(NAME ora_h COMMAND test_ora_ori 0xb4)
add_test(NAME ora_l COMMAND test_ora_ori 0xb5)
add_test(NAME ora_m COMMAND test_ora_ori 0xb6)
add_test(NAME ora_a COMMAND test_ora_ori 0xb7)
add_test(NAME ori COMMAND test_ora_ori 0xf6)

# Jump Tests
add_test(NAME jnz COMMAND test_jump 0xc2)
add_test(NAME jmp COMMAND test_jump 0xc3)
add_test(NAME jz COMMAND test_jump 0xca)
add_test(NAME jnc COMMAND test_jump 0xd2)
add_test(NAME jc COMMAND test_jump 0xda)
add_test(NAME jpo COMMAND test_jump 0xe2)
add_test(NAME pchl COMMAND test_jump 0xe9)
add_test(NAME jpe COMMAND test_jump 0xea)
add_test(NAME jp COMMAND test_jump 0xf2)
add_test(NAME jm COMMAND test_jump 0xfa)

# Pop Tests
add_test(NAME pop_b COMMAND test_push_pop 0xc1)

# Push Tests
add_test(NAME push_b COMMAND test_push_pop 0xc5)

# ADI D8 Test
# TODO move this to test_immediates?
add_test(NAME adi_d8 COMMAND test_adi 0xc6)

# Return Tests
add_test(NAME rnz COMMAND test_return 0xc0)
add_test(NAME rz COMMAND test_return 0xc8)
add_test(NAME ret COMMAND test_return 0xc9)
add_test(NAME rnc COMMAND test_return 0xd0)
add_test(NAME rc COMMAND test_return 0xd8)
add_test(NAME rpo COMMAND test_return 0xe0)
add_test(NAME rpe COMMAND test_return 0xe8)
add_test(NAME rp COMMAND test_return 0xf0)
add_test(NAME rm COMMAND test_return 0xf8)

# Test Load Instructions
add_executable(test_load tests/test_load.c)
add_test(NAME test_LXI_B COMMAND test_load 0x01)
add_test(NAME test_LXI_D COMMAND test_load 0x11)
add_test(NAME test_LDAX_D COMMAND test_load 0x1a)

# Test Add Instructions
add_executable(test_add tests/test_add.c)
add_test(NAME test_DAD_B COMMAND test_add 0x09)
add_test(NAME test_INX_D COMMAND test_add 0x13)
add_test(NAME test_DAD_D COMMAND test_add 0x19)

# Test Subtract Instructions
add_executable(test_subtract tests/test_subtract.c)
add_test(NAME test_DCR_A COMMAND test_subtract 0x3d)
add_test(NAME test_DCR_B COMMAND test_subtract 0x05)
add_test(NAME test_DCR_C COMMAND test_subtract 0x0d)
add_test(NAME test_DCR_D COMMAND test_subtract 0x15)
add_test(NAME test_DCR_E COMMAND test_subtract 0x1d)
add_test(NAME test_DCR_H COMMAND test_subtract 0x25)
add_test(NAME test_DCR_L COMMAND test_subtract 0x2d)
add_test(NAME test_DCR_M COMMAND test_subtract 0x35)
add_test(NAME test_DCX_B COMMAND test_subtract 0x0b)
add_test(NAME test_DCX_D COMMAND test_subtract 0x1b)
add_test(NAME test_DCX_H COMMAND test_subtract 0x2b)
add_test(NAME test_DCX_SP COMMAND test_subtract 0x3b)
add_test(NAME test_SUB_A COMMAND test_subtract 0x97)
add_test(NAME test_SUB_B COMMAND test_subtract 0x90)
add_test(NAME test_SUB_C COMMAND test_subtract 0x91)
add_test(NAME test_subtract_helper COMMAND test_subtract 0xFFFF)

# Test Move Immediate Instructions
add_executable(test_move_immediate tests/test_move_immediate.c)
add_test(NAME test_MVI_B COMMAND test_move_immediate 0x06)
add_test(NAME test_MVI_C COMMAND test_move_immediate 0x0e)

# Test Rotate Instructions
add_executable(test_rotate tests/test_rotate.c)
add_test(NAME test_RRC COMMAND test_rotate 0x0f)

# CRAIG's TESTS
add_executable(test_push_pop tests/test_push_pop.c)
add_test(NAME test_POP_D, COMMAND test_push_pop 0xd1)
add_test(NAME test_PUSH_D, COMMAND test_push_pop 0xd5)
add_test(NAME test_POP_H, COMMAND test_push_pop 0xe1)
add_test(NAME test_PUSH_H, COMMAND test_push_pop 0xe5)
add_test(NAME test_POP_PSW, COMMAND test_push_pop 0xf1)
add_test(NAME test_PUSH_PSW, COMMAND test_push_pop 0xf5)

add_executable(test_call tests/test_call.c)
add_test(NAME test_CALL, COMMAND test_call 0xcd)
add_test(NAME test_CNZ, COMMAND test_call 0xc4)
add_test(NAME test_CZ, COMMAND test_call 0xcc)
add_test(NAME test_CNC, COMMAND test_call 0xd4)
add_test(NAME test_CC, COMMAND test_call 0xdc)
add_test(NAME test_CPO, COMMAND test_call 0xe4)
add_test(NAME test_CPE COMMAND test_call 0xec)
add_test(NAME test_CP, COMMAND test_call 0xf4)
add_test(NAME test_CM, COMMAND test_call 0xfc)

add_executable(test_immediates tests/test_immediates.c)
add_test(NAME test_ANI_D8, COMMAND test_immediates 0xe6)

add_executable(test_xchg tests/test_xchg.c)
add_test(NAME test_XCHG, COMMAND test_xchg 0xeb)

add_executable(test_compare tests/test_compare.c)
add_test(NAME test_CPI_D8, COMMAND test_compare 0xfe)

add_executable(test_cmc tests/test_cmc.c)
add_test(NAME test_CMC, COMMAND test_cmc 0x3f)
