#include "../include/disassemble8080p.h"
#include "../include/structs.h"

#include <stdio.h>
#include <stdlib.h>

void push_to_stack(State *state, u_int16_t from);
void pop_to_program_counter(State *state);
void pop_to_register_pair(State *state, u_int8_t *hi_order_byte_reg,
                          u_int8_t *lo_order_byte_reg);

void unimplementedInstr(uint8_t opcode)
{
    printf("Error: Instruction 0x%02x not implemented.\n", opcode);
    exit(1);
}

State *Init8080(void)
{
    // Reserve memory for the state struct
    State *state = calloc(1, sizeof(State));
    if (state == NULL)
    {
        printf("Error: State allocation failed.\n");
        exit(1);
    }

    // Reserve memory for the 16KB of RAM
    state->memory = malloc(0x10000);
    if (state->memory == NULL)
    {
        printf("Error: State memory allocation failed.\n");
        free(state);
        exit(1);
    }

    // Clear all of the registers and set the initial program counter
    state->a = 0;
    state->b = 0;
    state->c = 0;
    state->e = 0;
    state->h = 0;
    state->l = 0;

    state->conditions.zero = 0;
    state->conditions.sign = 0;
    state->conditions.parity = 0;
    state->conditions.carry = 0;
    state->conditions.aux_carry = 0;
    state->conditions.pad = 0;

    // The program ROM starts at 0x0000 in memory
    state->pc = 0x0000;

    // Stack pointer is initialized by the ROM after start
    state->sp = 0x0000;

    return state;
}

void emulate8080(State *state)
{

    // Retrieve the opcode from memory at the current program counter location
    uint8_t *code = &state->memory[state->pc];
    int opbytes = 1;

    // clang-format off
    switch (*code)
    {
//    case 0x00: printf("NOP");  break;
//    case 0x01: printf("LXI B,D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x02: printf("STAX B"); break;
//    case 0x03: printf("INX B"); break;
//    case 0x04: printf("INR B"); break;
//    case 0x05: printf("DCR B"); break;
//    case 0x06: printf("MVI B, D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x07: printf("RLC"); break;
//    case 0x08: printf("-"); break;
//    case 0x09: printf("DAD B"); break;
//    case 0x0a: printf("LDAX B"); break;
//    case 0x0b: printf("DCX B"); break;
//    case 0x0c: printf("INR C"); break;
//    case 0x0d: printf("DCR C"); break;
//    case 0x0e: printf("MVI C,D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x0f: printf("RRC"); break;
//    case 0x10: printf("-"); break;
//    case 0x11: printf("LXI D,D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x12: printf("STAX D"); break;
//    case 0x13: printf("INX D"); break;
//    case 0x14: printf("INR D"); break;
//    case 0x15: printf("DCR D"); break;
//    case 0x16: printf("MVI D, D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x17: printf("RAL"); break;
//    case 0x18: printf("-"); break;
//    case 0x19: printf("DAD D"); break;
//    case 0x1a: printf("LDAX D"); break;
//    case 0x1b: printf("DCX D"); break;
//    case 0x1c: printf("INR E"); break;
//    case 0x1d: printf("DCR E"); break;
//    case 0x1e: printf("MVI E,D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x1f: printf("RAR"); break;
//    case 0x20: printf("RIM"); break;
//    case 0x21: printf("LXI H,D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x22: printf("SHLD adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x23: printf("INX H"); break;
//    case 0x24: printf("INR H"); break;
//    case 0x25: printf("DCR H"); break;
//    case 0x26: printf("MVI H,D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x27: printf("DAA"); break;
//    case 0x28: printf("-"); break;
//    case 0x29: printf("DAD H"); break;
//    case 0x2a: printf("LHLD adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x2b: printf("DCX H"); break;
//    case 0x2c: printf("INR L"); break;
//    case 0x2d: printf("DCR L"); break;
//    case 0x2e: printf("MVI L, D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x2f: printf("CMA"); break;
//    case 0x30: printf("SIM"); break;
//    case 0x31: printf("LXI SP, D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x32: printf("STA adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x33: printf("INX SP"); break;
//    case 0x34: printf("INR M"); break;
//    case 0x35: printf("DCR M"); break;
//    case 0x36: printf("MVI M,D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x37: printf("STC"); break;
//    case 0x38: printf("-"); break;
//    case 0x39: printf("DAD SP"); break;
//    case 0x3a: printf("LDA adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0x3b: printf("DCX SP"); break;
//    case 0x3c: printf("INR A"); break;
//    case 0x3d: printf("DCR A"); break;
//    case 0x3e: printf("MVI A,D8, $%02x", code[1]); opbytes = 2; break;
//    case 0x3f: printf("CMC"); break;
//    case 0x40: printf("MOV B,B"); break;
//    case 0x41: printf("MOV B,C");  break;
//    case 0x42: printf("MOV B,D");  break;
//    case 0x43: printf("MOV B,E");  break;
//    case 0x44: printf("MOV B,H");  break;
//    case 0x45: printf("MOV B,L");  break;
//    case 0x46: printf("MOV B,M");  break;
//    case 0x47: printf("MOV B,A");  break;
//    case 0x48: printf("MOV C,B");  break;
//    case 0x49: printf("MOV C,C");  break;
//    case 0x4a: printf("MOV C,D");  break;
//    case 0x4b: printf("MOV C,E");  break;
//    case 0x4c: printf("MOV C,H");  break;
//    case 0x4d: printf("MOV C,L");  break;
//    case 0x4e: printf("MOV C,M");  break;
//    case 0x4f: printf("MOV C,A");  break;
//    case 0x50: printf("MOV D,B");  break;
//    case 0x51: printf("MOV D,C");  break;
//    case 0x52: printf("MOV D,D");  break;
//    case 0x53: printf("MOV D,E");  break;
//    case 0x54: printf("MOV D,H");  break;
//    case 0x55: printf("MOV D,L");  break;
//    case 0x56: printf("MOV D,M");  break;
//    case 0x57: printf("MOV D,A");  break;
//    case 0x58: printf("MOV E,B");  break;
//    case 0x59: printf("MOV E,C");  break;
//    case 0x5a: printf("MOV E,D");  break;
//    case 0x5b: printf("MOV E,E");  break;
//    case 0x5c: printf("MOV E,H");  break;
//    case 0x5d: printf("MOV E,L");  break;
//    case 0x5e: printf("MOV E,M");  break;
//    case 0x5f: printf("MOV E,A");  break;
//    case 0x60: printf("MOV H,B");  break;
//    case 0x61: printf("MOV H,C");  break;
//    case 0x62: printf("MOV H,D");  break;
//    case 0x63: printf("MOV H,E");  break;
//    case 0x64: printf("MOV H,H");  break;
//    case 0x65: printf("MOV H,L");  break;
//    case 0x66: printf("MOV H,M");  break;
//    case 0x67: printf("MOV H,A");  break;
//    case 0x68: printf("MOV L,B");  break;
//    case 0x69: printf("MOV L,C");  break;
//    case 0x6a: printf("MOV L,D");  break;
//    case 0x6b: printf("MOV L,E");  break;
//    case 0x6c: printf("MOV L,H");  break;
//    case 0x6d: printf("MOV L,L");  break;
//    case 0x6e: printf("MOV L,M");  break;
//    case 0x6f: printf("MOV L,A");  break;
//    case 0x70: printf("MOV M,B");  break;
//    case 0x71: printf("MOV M,C");  break;
//    case 0x72: printf("MOV M,D");  break;
//    case 0x73: printf("MOV M,E");  break;
//    case 0x74: printf("MOV M,H");  break;
//    case 0x75: printf("MOV M,L");  break;
//    case 0x76: printf("HLT");  break;
//    case 0x77: printf("MOV M,A");  break;
//    case 0x78: printf("MOV A,B");  break;
//    case 0x79: printf("MOV A,C");  break;
//    case 0x7a: printf("MOV A,D");  break;
//    case 0x7b: printf("MOV A,E");  break;
//    case 0x7c: printf("MOV A,H");  break;
//    case 0x7d: printf("MOV A,L");  break;
//    case 0x7e: printf("MOV A,M");  break;
//    case 0x7f: printf("MOV A,A");  break;
//    case 0x80: printf("ADD B");  break;
//    case 0x81: printf("ADD C"); break;
//    case 0x82: printf("ADD D"); break;
//    case 0x83: printf("ADD E"); break;
//    case 0x84: printf("ADD H"); break;
//    case 0x85: printf("ADD L"); break;
//    case 0x86: printf("ADD M"); break;
//    case 0x87: printf("ADD A"); break;
//    case 0x88: printf("ADC B"); break;
//    case 0x89: printf("ADC C"); break;
//    case 0x8a: printf("ADC D"); break;
//    case 0x8b: printf("ADC E"); break;
//    case 0x8c: printf("ADC H"); break;
//    case 0x8d: printf("ADC L"); break;
//    case 0x8e: printf("ADC M"); break;
//    case 0x8f: printf("ADC A"); break;
//    case 0x90: printf("SUB B"); break;
//    case 0x91: printf("SUB C"); break;
//    case 0x92: printf("SUB D"); break;
//    case 0x93: printf("SUB E"); break;
//    case 0x94: printf("SUB H"); break;
//    case 0x95: printf("SUB L"); break;
//    case 0x96: printf("SUB M"); break;
//    case 0x97: printf("SUB A"); break;
//    case 0x98: printf("SBB B"); break;
//    case 0x99: printf("SBB C"); break;
//    case 0x9a: printf("SBB D"); break;
//    case 0x9b: printf("SBB E"); break;
//    case 0x9c: printf("SBB H"); break;
//    case 0x9d: printf("SBB L"); break;
//    case 0x9e: printf("SBB M"); break;
//    case 0x9f: printf("SBB A"); break;
//    case 0xa0: printf("ANA B"); break;
//    case 0xa1: printf("ANA C"); break;
//    case 0xa2: printf("ANA D"); break;
//    case 0xa3: printf("ANA E"); break;
//    case 0xa4: printf("ANA H"); break;
//    case 0xa5: printf("ANA L"); break;
//    case 0xa6: printf("ANA M"); break;
//    case 0xa7: printf("ANA A"); break;
//    case 0xa8: printf("XRA B"); break;
//    case 0xa9: printf("XRA C"); break;
//    case 0xaa: printf("XRA D"); break;
//    case 0xab: printf("XRA E"); break;
//    case 0xac: printf("XRA H"); break;
//    case 0xad: printf("XRA L"); break;
//    case 0xae: printf("XRA M"); break;
//    case 0xaf: printf("XRA A"); break;
//    case 0xb0: printf("ORA B"); break;
//    case 0xb1: printf("ORA C"); break;
//    case 0xb2: printf("ORA D"); break;
//    case 0xb3: printf("ORA E"); break;
//    case 0xb4: printf("ORA H"); break;
//    case 0xb5: printf("ORA L"); break;
//    case 0xb6: printf("ORA M"); break;
//    case 0xb7: printf("ORA A"); break;
//    case 0xb8: printf("CMP B"); break;
//    case 0xb9: printf("CMP C"); break;
//    case 0xba: printf("CMP D"); break;
//    case 0xbb: printf("CMP E"); break;
//    case 0xbc: printf("CMP H"); break;
//    case 0xbd: printf("CMP L"); break;
//    case 0xbe: printf("CMP M"); break;
//    case 0xbf: printf("CMP A"); break;
//    case 0xc0: printf("RNZ"); break;
//    case 0xc1: printf("POP B"); break;
//    case 0xc2: printf("JNZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xc3: printf("JMP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xc4: printf("CNZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xc5: printf("PUSH B"); break;
//    case 0xc6: printf("ADI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xc7: printf("RST 0"); break;
//    case 0xc8: printf("RZ"); break;
//    case 0xc9: printf("RET"); break;
//    case 0xca: printf("JZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xcb: printf("-"); break;
//    case 0xcc: printf("CZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xcd: // CALL code[2], code[1],
    {
        opbytes = 3;
        state->pc += opbytes;
        push_to_stack(state, state->pc);
        state->pc = code[2] << 8 | code[1];
        break;
    }
//    case 0xce: printf("ACI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xcf: printf("RST 1"); break;
//    case 0xd0: printf("RNC"); break;
    case 0xd1: printf("POP D");
    {
        state->pc += opbytes;
        pop_to_register_pair(state, &state->d, &state->e);
        break;
    }
//    case 0xd2: printf("JNC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xd3: printf("OUT D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xd4: printf("CNC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xd5: printf("PUSH D"); break;
//    case 0xd6: printf("SUI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xd7: printf("RST 2"); break;
//    case 0xd8: printf("RC 1"); break;
//    case 0xd9: printf("-"); break;
//    case 0xda: printf("JC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xdb: printf("IN D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xdc: printf("CC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xdd: printf("-"); break;
//    case 0xde: printf("SBI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xdf: printf("RST 3"); break;
//    case 0xe0: printf("RPO"); break;
    case 0xe1: printf("POP H"); break;
//    case 0xe2: printf("JPO, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xe3: printf("XTHL"); break;
//    case 0xe4: printf("CPO, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xe5: printf("PUSH H"); break;
    case 0xe6: printf("ANI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xe7: printf("RST 4"); break;
//    case 0xe8: printf("RPE"); break;
//    case 0xe9: printf("PCHL"); break;
//    case 0xea: printf("JPE, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xeb: printf("XCHG"); break;
//    case 0xec: printf("CPE, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xed: printf("-"); break;
//    case 0xee: printf("XRI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xef: printf("RST 5"); break;
//    case 0xf0: printf("RP"); break;
    case 0xf1: printf("POP PSW"); break;
//    case 0xf2: printf("JP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xf3: printf("DI"); break;
//    case 0xf4: printf("CP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xf5: printf("PUSH PSW"); break;
//    case 0xf6: printf("ORI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xf7: printf("RST 6"); break;
//    case 0xf8: printf("RM"); break;
//    case 0xf9: printf("SPHL"); break;
//    case 0xfa: printf("JM, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xfb: printf("EI"); break;
//    case 0xfc: printf("CM, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xfd: printf("-"); break;
    case 0xfe: printf("CPI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xff: printf("RST 7"); break;
    default: unimplementedInstr(*code); break;
    }
    // clang-format off
}

void push_to_stack(State* state, u_int16_t from){
    /*
    * (1) The most significant 8 bits of data are stored at the memory address
    *       one less than the contents of the stack pointer.
    * (2) The least significant 8 bits of data are stored at the memory address
    *       two less than the contents of the stack pointer.
    * (3) The stack pointer is automatically decremented by two.
    */
    u_int8_t high_order_bits = (from >> 8) & 0xFF;
    u_int8_t low_order_bits = from & 0xFF;
    state->memory[state->sp-1] = high_order_bits;
    state->memory[state->sp-2] = low_order_bits;
    state->sp -= 2;
}

void pop_to_program_counter(State* state)
{
    /*
     * __Pop the stack to the program_counter__
     * 1) The second register of the pair, or the least significant 8 bits
     *      of the program counter, are loaded from the memory address held in
     *      the stack pointer.
     * 2) The first register of the pair, or the most significant 8 bits of
     *      the program counter, are loaded from the memory address one greater
     *      than the address held in the stack pointer.
     * 3) The stack pointer is automatically incremented by two.
    */
    u_int8_t low_order_bits = state->memory[state->sp];
    u_int8_t high_order_bits = state->memory[state->sp+1];
    state->sp += 2;
    state->pc = high_order_bits << 8 | low_order_bits;
}

void pop_to_register_pair(State* state, u_int8_t* hi_order_byte_reg, u_int8_t* lo_order_byte_reg)
{
    /* Pop the stack to a pair of registers
     * 1) The second register of the pair, or the least significant 8 bits
     *      of the program counter, are loaded from the memory address held in
     *      the stack pointer.
     * 2) The first register of the pair, or the most significant 8 bits of
     *      the program counter, are loaded from the memory address one greater
     *      than the address held in the stack pointer.
     * 3) The stack pointer is automatically incremented by two.
    */
    u_int8_t low_order_bits = state->memory[state->sp];
    u_int8_t high_order_bits = state->memory[state->sp+1];
    state->sp += 2;
    *hi_order_byte_reg = high_order_bits;
    *lo_order_byte_reg = low_order_bits;
}