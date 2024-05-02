// #include "../include/disassemble8080p.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdio.h>
#include <stdlib.h>

void emulate8080(State *state)
{

    // Retrieve the opcode from memory at the current program counter location
    uint8_t *code = &state->memory[state->pc];
    int opbytes = 1;

    // clang-format off
    switch (*code)
    {
    case 0x00: // NOP
    {
        state->pc += opbytes;
        wait_cycles(4);
        break;
    }
    case 0x01: // LXI B,D16     B <- Code[2], C <- Code[1]
    {
        opbytes = 3;
        state->pc += opbytes;
        state->b = code[2];
        state->c = code[1];
        wait_cycles(10);
        break;
    }
    case 0x02: // STAX B (BC) <- A
    {
        state->pc += opbytes;
        uint16_t bc = (state->b << 8) | (state->c);
        state->memory[bc] = state->a;
        wait_cycles(7);
        break;
    }
    case 0x03: // INX B BC <- BC + 1
    {
        state->pc += opbytes;
        uint16_t temp_BC = combine_bytes_to_word(state->b, state->c);
        temp_BC += 1;
        state->b = temp_BC >> 8;
        state->c = temp_BC;
        wait_cycles(5);
        break;
    }
//    case 0x04: printf("INR B"); break;
    case 0x05: // DCR B     B <- B-1
    {
        state->pc += opbytes;
        state->conditions.aux_carry = !get_aux_carry_flag_from_sum(state->b, 0xFF);
        state->b -= 1;
        state->conditions.zero = get_zero_flag(state->b);
        state->conditions.sign = get_sign_flag(state->b);
        state->conditions.parity = get_parity_flag(state->b);
        wait_cycles(5);
        break;
    }
    case 0x06: // MVI B,D8     B <- code[1]
    {
        opbytes = 2;
        state->pc += opbytes;
        state->b = code[1];
        wait_cycles(7);
        break;
    }
//    case 0x07: printf("RLC"); break;
//    case 0x08: printf("-"); break;
    case 0x09: // DAD B       HL = HL + BC
    {
        state->pc += opbytes;
        uint16_t temp_HL = combine_bytes_to_word(state->h, state->l);
        uint16_t temp_BC = combine_bytes_to_word(state->b, state->c);
        state->conditions.carry = get_carry_flag_from_sum_16b(temp_HL, temp_BC);
        temp_HL += temp_BC;
        state->h = temp_HL >> 8;
        state->l = temp_HL;
        wait_cycles(10);
        break;
    }
//    case 0x0a: printf("LDAX B"); break;
//    case 0x0b: printf("DCX B"); break;
//    case 0x0c: printf("INR C"); break;
    case 0x0d: // DCR C     C <- C-1
    {
        state->pc += opbytes;
        state->conditions.aux_carry = !get_aux_carry_flag_from_sum(state->c, 0xFF);
        state->c -= 1;
        state->conditions.zero = get_zero_flag(state->c);
        state->conditions.sign = get_sign_flag(state->c);
        state->conditions.parity = get_parity_flag(state->c);
        wait_cycles(5);
        break;
    }
    case 0x0e: // MVI C,D8      C <- code[1]
    {
        opbytes = 2;
        state->pc += opbytes;
        state->c = code[1];
        wait_cycles(7);
        break;
    }
    case 0x0f: // RRC       Set Carry = A0, then rotate A right
    {
        state->pc += opbytes;
        state->conditions.carry = state->a & 0b00000001;
        state->a = (state->a >> 1) + (state->conditions.carry << 7);
        wait_cycles(4);
        break;
    }
//    case 0x10: printf("-"); break;
    case 0x11: // LXI D,D16     D <- code[2], E <- code[1]
    {
        opbytes = 3;
        state->pc += opbytes;
        state->d = code[2];
        state->e = code[1];
        wait_cycles(10);
        break;
    }
    case 0x12: // STAX D (DE) <- A
    {	state->pc += opbytes;
	uint16_t de = (state->d << 8) | (state->e);
	state->memory[de] = state->a;
     	wait_cycles(7);
	break;
    }
   case 0x13: // INX D      DE <- DE + 1
    {
    	state->pc += opbytes;
    	uint16_t de = (state->d << 8) | state->e;
    	de += 1;
    	state->d = de >> 8;
    	state->e = de & 0xFF;
    	wait_cycles(5);
    	break;
    }
//    case 0x14: printf("INR D"); break;
//    case 0x15: printf("DCR D"); break;
    case 0x16: // MVI D, D8 D <- code[1]
    {
	opbytes = 2;
        state->pc += opbytes;
        state->d = code[1];
        wait_cycles(7);
        break;
    }
//    case 0x17: printf("RAL"); break;
//    case 0x18: printf("-"); break;
    case 0x19: // DAD D     HL = HL + DE
    {
        state->pc += opbytes;
        uint16_t temp_HL = combine_bytes_to_word(state->h, state->l);
        uint16_t temp_DE = combine_bytes_to_word(state->d, state->e);
        state->conditions.carry = get_carry_flag_from_sum_16b(temp_HL, temp_DE);
        temp_HL += temp_DE;
        state->h = temp_HL >> 8;
        state->l = temp_HL;
        wait_cycles(10);
        break;
    }
    case 0x1a: // LDAX D      A <- value at memory[DE]
    {
        state->pc += opbytes;
        uint16_t temp_DE = combine_bytes_to_word(state->d, state->e);
        state->a = state->memory[temp_DE];
        wait_cycles(7);
        break;
    }
//    case 0x1b: printf("DCX D"); break;
//    case 0x1c: printf("INR E"); break;
//    case 0x1d: printf("DCR E"); break;
//    case 0x1e: printf("MVI E,D8, $%02x", code[1]); opbytes = 2; break;
    case 0x1e: // MVI E, D8 E <- code[1]
    {		    
	opbytes = 2;
        state->pc += opbytes;
        state->e = code[1];
        wait_cycles(7);
        break;
    }
//    case 0x1f: printf("RAR"); break;
    case 0x20: // RIM, unimplemented instruction treated as NOP
    {
	state->pc += opbytes;
        wait_cycles(4);
        break;
    }		    
//    case 0x21: printf("LXI H,D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0x21: // LXI H, D16   H <- code[2], L <- code[1]
    {
        opbytes = 3;
        state->pc += opbytes;
        state->h = code[2];
        state->l = code[1];
        wait_cycles(10);
        break;
    }     
    case 0x22: // SHLD  code[2] <-L; code[1]<-H
    {
    	opbytes = 3;
    	state->pc += opbytes;
    	state->memory[combine_bytes_to_word(code[1], code[2])] = state->l;
    	state->memory[combine_bytes_to_word(code[1] + 1, code[2])] = state->h;
    	wait_cycles(16);
    	break;
    }
    case 0x23: // INX H  LH <- LH + 1
    {
        state->pc += opbytes;
        uint16_t temp_LH = combine_bytes_to_word(state->h, state->l);
        temp_LH += 1;
        state->l = temp_LH >> 8;
        state->h = temp_LH;
        wait_cycles(5);
        break;
    }      
//    case 0x24: printf("INR H"); break;
//    case 0x25: printf("DCR H"); break;
    case 0x26: // MVI H, D8
    {
        opbytes = 2;
        state->pc += opbytes;
        state->h = code[1];
        wait_cycles(7);
        break;
    }    
    case 0x27: // DAA   Z, S, P, CY, AC
    {
    	state->pc += opbytes;
    	uint8_t lower_nib = state->a & 0x0F;
    	uint8_t higher_nib = (state->a >> 4) & 0x0F;
    	if (lower_nib > 9 || state->conditions.aux_carry == 1) {
        	state->a += 6;
        	state->conditions.aux_carry = 1;
    	}
    	if (higher_nib > 9 || state->conditions.carry == 1) {
        	state->a += 0x60;
        	state->conditions.carry = 1;
    	}
    	state->conditions.zero = (state->a == 0);
    	state->conditions.sign = (state->a & 0x80) != 0;
    	state->conditions.parity = 1; // Start with odd parity
    	for (int i = 0; i < 8; i++) {
        	if (state->a & (1 << i)) {
            	state->conditions.parity = !state->conditions.parity; // Flip parity if bit is set
        	}
    	}
    	wait_cycles(4);
    	break;
    }
//    case 0x28: printf("-"); break;
    case 0x29: // DAD H     HL = HL + HL
    {
        state->pc += opbytes;
        uint16_t temp_HL = combine_bytes_to_word(state->h, state->l);
        state->conditions.carry = get_carry_flag_from_sum_16b(temp_HL, temp_HL);
        temp_HL += temp_HL;
        state->h = temp_HL >> 8;
        state->l = temp_HL;
        wait_cycles(10);
        break;
    }
    case 0x2a: // LHLD  code[2] <-L; code[1]<-H
    {
        opbytes = 3;
        state->pc += opbytes;
        uint16_t address = combine_bytes_to_word(code[2], code[1]); // Combine bytes to form 16-bit address
        state->l = state->memory[address]; // Load the value at address into L
        state->h = state->memory[address + 1]; // Load the value at address + 1 into H
        wait_cycles(16);
        break;
    }  
//    case 0x2b: printf("DCX H"); break;
//    case 0x2c: printf("INR L"); break;
//    case 0x2d: printf("DCR L"); break;
    case 0x2e: // MVI L, D8 L <- code[1]
    {
    	opbytes = 2;
    	state->pc += opbytes;
    	state->l = code[1];
    	break;
    }
    case 0x2f: // CMA A <- !A
    {
    	state->pc += opbytes;
    	state->a = ~(state->a);
    	wait_cycles(4);
    	break;
    }
    case 0x30: // SIM, unimplemented instruction treated as NOP
    {
	state->pc += opbytes;
        wait_cycles(4);
        break;
    }	
    case 0x31: // LXI SP, D16 code[2], code[1]
    {
        opbytes = 3;
        state->pc += opbytes;
        state->sp = combine_bytes_to_word(code[2], code[1]); 
        wait_cycles(10);
        break;
    }   
    case 0x32: // STA adr code[2], code[1]
    {
        opbytes = 3;
        state->pc += opbytes;
        uint16_t temp_adr = combine_bytes_to_word(code[2], code[1]);
	state->a = state->memory[temp_adr];
        wait_cycles(13);
        break;            
    }  
    case 0x33: // INX SP      SP = SP + 1
    {
        state->pc += opbytes;
        state->sp++;
        wait_cycles(5);
        break;
    }
//    case 0x34: printf("INR M"); break;
//    case 0x35: printf("DCR M"); break;
    case 0x36: // MVI M, D8  H <- code[1]
    {
        opbytes = 2;
        state->pc += opbytes;
        state->memory[combine_bytes_to_word(state->h, state->l)] = code[1];
        wait_cycles(7);
        break;
    }  
    case 0x37: // STC  CY = 1
    {
	state->pc += opbytes;
	state->conditions.carry = 1;
	wait_cycles(4);
	break;
    }

//    case 0x38: printf("-"); break;
//    case 0x39: printf("DAD SP"); break;
    case 0x3a: // LDA adr A <- code[1] adr <- code[2]
    {
        opbytes = 3;
        state->pc += opbytes;
        state->a = state->memory[combine_bytes_to_word(code[2], code[1])];
        wait_cycles(17);
        break;
    } 
//    case 0x3b: printf("DCX SP"); break;
//    case 0x3c: printf("INR A"); break;
//    case 0x3d: printf("DCR A"); break;
    case 0x3e: // MVI A, D8  A <- code[1]
    {
        opbytes = 2;
        state->pc += opbytes;
        state->a = code[1];
        wait_cycles(7);
        break;
    }    
    case 0x3f: // CMC   CY != CY
    {
	state->pc += opbytes;
	state->conditions.carry = ~state->conditions.carry;
	wait_cycles(4);
	break;
    }
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
   case 0x56: // MOV D, M
    {
        mov_mem_to_reg(state, &state->d);
	wait_cycles(5);
        break;
    } 
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
   case 0x66: // MOV H, M
   {
        mov_mem_to_reg(state, &state->h);
	wait_cycles(5);
        break;
   }     
//    case 0x67: printf("MOV H,A");  break;
//    case 0x68: printf("MOV L,B");  break;
//    case 0x69: printf("MOV L,C");  break;
//    case 0x6a: printf("MOV L,D");  break;
//    case 0x6b: printf("MOV L,E");  break;
//    case 0x6c: printf("MOV L,H");  break;
//    case 0x6d: printf("MOV L,L");  break;
//    case 0x6e: printf("MOV L,M");  break;
   case 0x6f: // MOV L, A 
   {
       mov_reg_to_reg(state, &state->l, &state->a);
       wait_cycles(5);
       break;
   } 
//    case 0x70: printf("MOV M,B");  break;
//    case 0x71: printf("MOV M,C");  break;
//    case 0x72: printf("MOV M,D");  break;
//    case 0x73: printf("MOV M,E");  break;
//    case 0x74: printf("MOV M,H");  break;
//    case 0x75: printf("MOV M,L");  break;
//    case 0x76: printf("HLT");  break;
    case 0x77:  // MOV M,A
    {
        mov_reg_to_mem(state, &state->a);
        break;
    }
//    case 0x78: printf("MOV A,B");  break;
//    case 0x79: printf("MOV A,C");  break;
    case 0x7a: // MOV A,D
    {
        mov_reg_to_reg(state, &state->a, &state->d);
        break;
    }
    case 0x7b:  // MOV A,E
    {
        mov_reg_to_reg(state, &state->a, &state->e);
        break;
    }
    case 0x7c:  //MOV A,H
    {
        mov_reg_to_reg(state, &state->a, &state->h);
        break;
    }
//    case 0x7d: printf("MOV A,L");  break;
    case 0x7e:  // MOV A,M
    {
        mov_mem_to_reg(state, &state->a);
        break;
    }
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
    case 0x90: // SUB B   Z, S, P, CY, AC    A <- A - B
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->b);
        wait_cycles(4);
        break;
    }
    case 0x91: // SUB C   Z, S, P, CY, AC	A <- A - C
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->c);
        wait_cycles(4);
        break;
    }
    case 0x92: // SUB D   Z, S, P, CY, AC	A <- A - D
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->d);
        wait_cycles(4);
        break;
    }
    case 0x93: // SUB E   Z, S, P, CY, AC	A <- A - E
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->e);
        wait_cycles(4);
        break;
    }
    case 0x94: // SUB H   Z, S, P, CY, AC	A <- A - H
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->h);
        wait_cycles(4);
        break;
    }
    case 0x95: // SUB L   Z, S, P, CY, AC	A <- A - L
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->l);
        wait_cycles(4);
        break;
    }
    case 0x96: // SUB M   Z, S, P, CY, AC    A <- A - (HL)
    {
        uint16_t address = (state->h << 8) | state->l;
        uint8_t value = state->memory[address];
        state->pc += opbytes;
        subtract_8b(state, state->a, value);
        wait_cycles(7);
        break;
    }
    case 0x97: // SUB A   Z, S, P, CY, AC    A <- A - A
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->a);
        wait_cycles(4);
        break;
    }
    case 0x98: // SBB B   Z, S, P, CY, AC    A <- A - B - CY
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->b + (state->conditions.carry ? 1 : 0));
        wait_cycles(4);
        break;
    }
    case 0x99: // SBB C   Z, S, P, CY, AC    A <- A - C - CY
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->c + (state->conditions.carry ? 1 : 0));
        wait_cycles(4);
        break;
    }
    case 0x9a: // SBB D   Z, S, P, CY, AC    A <- A - D - CY
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->d + (state->conditions.carry ? 1 : 0));
        wait_cycles(4);
        break;
    }
    case 0x9b: // SBB E   Z, S, P, CY, AC    A <- A - E - CY
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->e + (state->conditions.carry ? 1 : 0));
        wait_cycles(4);
        break;
    }
    case 0x9c: // SBB H   Z, S, P, CY, AC    A <- A - H - CY
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->h + (state->conditions.carry ? 1 : 0));
        wait_cycles(4);
        break;
    }
    case 0x9d: // SBB L   Z, S, P, CY, AC    A <- A - L - CY
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->l + (state->conditions.carry ? 1 : 0));
        wait_cycles(4);
        break;
    }
    case 0x9e: // SBB M   Z, S, P, CY, AC    A <- A - (HL) - CY
    {
        uint16_t address = (state->h << 8) | state->l;
        uint8_t value = state->memory[address];
        state->pc += opbytes;
        subtract_8b(state, state->a, value + (state->conditions.carry ? 1 : 0));
        wait_cycles(7);
        break;
    }
    case 0x9f: // SBB A   Z, S, P, CY, AC    A <- A - A - CY
    {
        state->pc += opbytes;
        subtract_8b(state, state->a, state->a + (state->conditions.carry ? 1 : 0));
        wait_cycles(4);
        break;
    }
//    case 0xa0: printf("ANA B"); break;
//    case 0xa1: printf("ANA C"); break;
//    case 0xa2: printf("ANA D"); break;
//    case 0xa3: printf("ANA E"); break;
//    case 0xa4: printf("ANA H"); break;
//    case 0xa5: printf("ANA L"); break;
//    case 0xa6: printf("ANA M"); break;
    case 0xa7:  // ANA A
    {
        ana_helper(state, state->a);
        break;
    }
//    case 0xa8: printf("XRA B"); break;
//    case 0xa9: printf("XRA C"); break;
//    case 0xaa: printf("XRA D"); break;
//    case 0xab: printf("XRA E"); break;
//    case 0xac: printf("XRA H"); break;
//    case 0xad: printf("XRA L"); break;
//    case 0xae: printf("XRA M"); break;
    case 0xaf:  // XRA A
    {
        xra_helper(state, state->a);
        break;
    }
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
    case 0xc1:  // POP B; Pops stack into BC register pair
    {
        state->pc += opbytes;
        pop_stack_to_register_pair(state, &state->b, &state->c);
        break;
    }
    case 0xc2:  //JNZ, $%02x%02x, code[2], code[1]
    {
        opbytes = 3;
        if (state->conditions.zero == 0) jump_to_addr(state, code);
        else state->pc += opbytes;
        break;
    }
    case 0xc3:  // JMP, $%02x%02x", code[2], code[1])
    {
        jump_to_addr(state, code);
        break;
    }
//    case 0xc4: printf("CNZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xc5:  // PUSH B
    {
        state->pc += opbytes;
        push_register_pair_to_stack(state, state->b, state->c);
        break;
    }
    case 0xc6:  // ADI D8 (code[1]) : opbytes = 2
    {
        opbytes = 2;
        state->pc += opbytes;
        uint8_t temp_accum = state->a + code[1];
        state->conditions.zero = get_zero_flag(temp_accum);
        state->conditions.parity = get_parity_flag(temp_accum);
        state->conditions.sign = get_sign_flag(temp_accum);
        state->conditions.carry = get_carry_flag_from_sum_8b(state->a, code[1]);
        state->conditions.aux_carry = get_aux_carry_flag_from_sum(state->a, code[1]);
        state->a = temp_accum;
        break;
    }
//    case 0xc7: printf("RST 0"); break;
//    case 0xc8: printf("RZ"); break;
    case 0xc9:  // RET
    {
        return_helper(state);
        break;
    }
//    case 0xca: printf("JZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xcb: printf("-"); break;
//    case 0xcc: printf("CZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xcd: // CALL code[2], code[1]; Push next seq. instr. to stack. Set pc to given args.
    {
        opbytes = 3;
        state->pc += opbytes;
        call_helper(state);
        state->pc = combine_bytes_to_word(code[2], code[1]);
        wait_cycles(17); // per Intel 8080 Programmers Manual
        break;
    }
//    case 0xce: printf("ACI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xcf: printf("RST 1"); break;
//    case 0xd0: printf("RNC"); break;
    case 0xd1: // POP D; Pops stack into DE register pair.
    {
        state->pc += opbytes;
        pop_stack_to_register_pair(state, &state->d, &state->e);
        wait_cycles(10); // per Intel 8080 Programmers Manual
        break;
    }
//    case 0xd2: printf("JNC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xd3: // OUT D8, code[1]; Send the data from A onto the 8bit data bus for transmission to spec'd port
    {
        opbytes = 2;
        state->pc += opbytes;
        // TODO emulator 101 recommended skipping over this for now.
        // TODO IO[code[1]] = state->a;
        wait_cycles(10); // per Intel 8080 Programmers Manual
        break;
    }
//    case 0xd4: printf("CNC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xd5: // PUSH D; Pushes register pair DE to the stack.
    {
        state->pc += opbytes;
        push_register_pair_to_stack(state, state->d, state->e);
        wait_cycles(11); // per Intel 8080 Programmers Manual
        break;
    }
    case 0xd6: // SUI D8   Z, S, P, CY, AC A <- A - byte
    {
        uint8_t immediate = state->memory[state->pc + 1];
        state->pc += 2;
        subtract_8b(state, state->a, immediate);
        wait_cycles(7);
        break;
    }
//    case 0xd7: printf("RST 2"); break;
//    case 0xd8: printf("RC 1"); break;
//    case 0xd9: printf("-"); break;
//    case 0xda: printf("JC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xdb: printf("IN D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xdc: printf("CC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xdd: printf("-"); break;
    case 0xde: // SBI D8   Z, S, P, CY, AC    A <- A - byte - CY
    {
        uint8_t immediate = state->memory[state->pc + 1];
        state->pc += 2;
        subtract_8b(state, state->a, immediate + (state->conditions.carry ? 1 : 0));
        wait_cycles(7);
        break;
    }
//    case 0xdf: printf("RST 3"); break;
//    case 0xe0: printf("RPO"); break;
    case 0xe1: // POP H; Pops stack into HL register pair.
    {
        state->pc += opbytes;
        pop_stack_to_register_pair(state, &state->h, &state->l);
        wait_cycles(10); // per Intel 8080 Programmers Manual
        break;
    }
//    case 0xe2: printf("JPO, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xe3: printf("XTHL"); break;
//    case 0xe4: printf("CPO, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xe5: // PUSH H; Pushes register pair HL to the stack.
    {
        state->pc += opbytes;
        push_register_pair_to_stack(state, state->h, state->l);
        wait_cycles(11); // per Intel 8080 Programmers Manual
        break;
    }
    case 0xe6: //ANI D8, code[1]; A = A & D8, clear carry, clear aux_carry (update Z, S, P)
    {
        opbytes = 2;
        state->pc += opbytes;
        state->a = state->a & code[1];
        state->conditions.carry = 0;
        state->conditions.aux_carry = 0;
        state->conditions.zero = get_zero_flag(state->a);
        state->conditions.sign = get_sign_flag(state->a);
        state->conditions.parity = get_parity_flag(state->a);
        wait_cycles(7);
        break;
    }
//    case 0xe7: printf("RST 4"); break;
//    case 0xe8: printf("RPE"); break;
//    case 0xe9: printf("PCHL"); break;
//    case 0xea: printf("JPE, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xeb: // XCHG; H <-> D, L <-> E; The contents of H and D, L and E are swapped.
    {
        state->pc += opbytes;
        uint8_t temp_h = state->h;
        uint8_t temp_l = state->l;
        uint8_t temp_d = state->d;
        uint8_t temp_e = state->e;
        state->h = temp_d;
        state->l = temp_e;
        state->d = temp_h;
        state->e = temp_l;
        wait_cycles(5); // TODO this is from the chart but both manual disagree (and disagree with one another).
        break;
    }
//    case 0xec: printf("CPE, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xed: printf("-"); break;
//    case 0xee: printf("XRI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xef: printf("RST 5"); break;
//    case 0xf0: printf("RP"); break;
    case 0xf1: // POP PSW; Pop Processor Status Word.
    {
        state->pc += opbytes;
        uint8_t sp_val8 = state->memory[state->sp];
        state->conditions.carry     = (sp_val8 >> 0) & 0x01;
        state->conditions.parity    = (sp_val8 >> 2) & 0x01;
        state->conditions.aux_carry = (sp_val8 >> 4) & 0x01;
        state->conditions.zero      = (sp_val8 >> 6) & 0x01;
        state->conditions.sign      = (sp_val8 >> 7) & 0x01;
        state->a = state->memory[state->sp + 1];
        state->sp += 2;
        wait_cycles(10); // per Intel 8080 Programmers Manual.
        break;
    }
//    case 0xf2: printf("JP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xf3: printf("DI"); break;
//    case 0xf4: printf("CP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xf5: // PUSH PSW; Push Processor Status Word.
    {
        // TODO update state->conditions struct to be in same order as manual?
        state->pc += opbytes;
        state->memory[state->sp - 1] = state->a;
        uint8_t c = (state->conditions.carry << 0);
        uint8_t p = (state->conditions.parity << 2);
        uint8_t ac = (state->conditions.aux_carry << 4);
        uint8_t z = (state->conditions.zero << 6);
        uint8_t s = (state->conditions.sign << 7);
        uint8_t flags = s | z | ac | p | c;
        state->memory[state->sp - 2] = flags;
        state->sp -= 2;
        wait_cycles(11); // per Intel 8080 Programmers Manual.
        break;
    }
//    case 0xf6: printf("ORI D8, $%02x", code[1]); opbytes = 2; break;
//    case 0xf7: printf("RST 6"); break;
//    case 0xf8: printf("RM"); break;
    case 0xf9: // SPHL
    {
    	state->sp = (state->h << 8) | state->l;
    	state->pc += opbytes;
    	wait_cycles(5);
    	break;
    }
//    case 0xfa: printf("JM, $%02x%02x", code[2], code[1]); opbytes = 3; break;
    case 0xfb: // EI; "The interrupt system is enabled following the execution of the next instruction"...
    {
        state->pc += opbytes;
        // TODO emulator 101 recommended skipping over this for now.
        wait_cycles(4); // per Intel 8080 Programmers Manual.
    }
//    case 0xfc: printf("CM, $%02x%02x", code[2], code[1]); opbytes = 3; break;
//    case 0xfd: printf("-"); break;
    case 0xfe: // CPI D8, code[1]; Compare immediate with accumulator. AKA reg.a - immediate.
    {
        opbytes = 2;
        state->pc += opbytes;
        subtract_8b(state, state->a, code[1]);
        uint8_t result = state->a - code[1];
        state->conditions.zero = (result == 0);
        state->conditions.sign = ((result & 0x80) != 0); // Set if bit 7 of the result is set
        int count = 0;
        for (int i = 0; i < 8; i++) {
            if (result & (1 << i)) {
                count++;
            }
        }
        state->conditions.parity = (count % 2 == 0);
        state->conditions.carry = (state->a < code[1]);
        wait_cycles(7); 
        break;
    }
//    case 0xff: printf("RST 7"); break;
    default: unimplementedInstr(*code); break;
    }
    // clang-format off
}

void push_register_pair_to_stack(State* state, uint8_t rh, uint8_t rl){
    /*
    * (1) The most significant 8 bits of data are stored at the memory address
    *       one less than the contents of the stack pointer.
    * (2) The least significant 8 bits of data are stored at the memory address
    *       two less than the contents of the stack pointer.
    * (3) The stack pointer is automatically decremented by two.
    */
    state->memory[state->sp-1] = rh;
    state->memory[state->sp-2] = rl;
    state->sp -= 2;
}

void pop_stack_to_register_pair(State* state, uint8_t* rh, uint8_t* rl)
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
    uint8_t low_order_bits = state->memory[state->sp];
    uint8_t high_order_bits = state->memory[state->sp+1];
    state->sp += 2;
    *rh = high_order_bits;
    *rl = low_order_bits;
}

void mov_reg_to_reg(State *state, uint8_t *to, uint8_t *from)
{
    /* Copies the value stored in the from register address to the to register address
     * Increments the program counter by 1
    */
    state->pc += 1; // increment program counter by 1
    *to = *from;
}

void mov_reg_to_mem(State *state, uint8_t *from)
{
    /* Copies the value stored in the from register address into memory
     * The memory address is determined by registers H (most significant bits
     * and L (least significant bits)
     * Increments the program counter by 1
    */
    state->pc += 1; // increment program counter by 1
    uint16_t mem_offset = (state->h << 8) | state->l;
    state->memory[mem_offset] = *from;
}

void mov_mem_to_reg(State *state, uint8_t *to)
{
    /* Copies the value stored in memory into the to register address.
     * The memory address is determined by registers H (most significant bits
     * and L (least significant bits)
     * Increments the program counter by 1
    */
    state->pc += 1; // increment program counter by 1
    uint16_t mem_offset = (state->h << 8) | state->l;
    *to = state->memory[mem_offset];
}

void ana_helper(State *state, uint8_t andwith_val)
{
    /* Helper function for ANA opcodes - performs logical AND on the
     * accumulator and provided value andwith_val
     * Sets carry to 0
     * Updates zero, sign, and parity (aux_carry not mentioned in 8080
     * manual)
     * Increments the program counter by 1
    */
    state->pc += 1; // increment program counter by 1
    state->a = state->a & andwith_val;
    state->conditions.carry = 0;
    state->conditions.zero = get_zero_flag(state->a);
    state->conditions.sign = get_sign_flag(state->a);
    state->conditions.parity = get_parity_flag(state->a);
}

void xra_helper(State *state, uint8_t xorwith_val)
{
    /* Helper function for XRA opcodes - performs logical XOR on the
     * accumulator and provided value xorwith_val
     * Sets carry and aux_carry to 0 - manual says carry should be 0, unclear
     * about aux_carry
     * Updates zero, sign, and parity
     * Increments the program counter by 1
    */
    state->pc += 1;
    state->a = state->a ^ xorwith_val;
    state->conditions.carry = 0;
    state->conditions.aux_carry = 0;
    state->conditions.zero = get_zero_flag(state->a);
    state->conditions.sign = get_sign_flag(state->a);
    state->conditions.parity = get_parity_flag(state->a);
}

void jump_to_addr(State *state, uint8_t *code)
{
    /* Helper function for JUMP opcodes
     * Sets program counter to the address stored in the next two memory indexes
     * - higher-order bits in code[2] and lower-order bits in code[1]
    */
    state->pc = (code[2] << 8) | code[1];
}

void call_helper(State* state){
    /*
    * (1) The most significant 8 bits of data are stored at the memory address
    *       one less than the contents of the stack pointer.
    * (2) The least significant 8 bits of data are stored at the memory address
    *       two less than the contents of the stack pointer.
    * (3) The stack pointer is automatically decremented by two.
    */
    // uint8_t high_order_bits = (state->pc >> 8) & 0xFF;
    // uint8_t low_order_bits = state->pc & 0xFF;
    // uint8_t *hb_p = &state->memory[state->sp-1];
    // uint8_t *lb_p = &state->memory[state->sp-2];
    split_word_to_bytes(state->pc,
                        &state->memory[state->sp-1],
                        &state->memory[state->sp-2]
                        );
    state->sp -= 2;
}

void return_helper(State *state)
{
    /* Helper function for RETURN opcodes
     * Pops the top two bytes from the stack pointer and increments sp by 2
     * Sets pc to the memory address retrieved
    */
    state->pc = combine_bytes_to_word(state->memory[state->sp+1],
                                      state->memory[state->sp]
                                      );
    state->sp += 2;
}

void wait_cycles(int clockCycles)
{
    // TODO: Implememnt the CPU clock delay
}

uint8_t get_sign_flag(uint8_t register_value)
{
    // Sign bit is set to the value of the most significant bit of the affected
    // register
    return register_value >> 7;
}

uint8_t get_zero_flag(uint8_t register_value) { return register_value == 0; }

uint8_t get_parity_flag(uint8_t register_value)
{
//    The parity bit is set to 1 if the # of set bits is EVEN.
//    The parity bit is cleared to 0 if the # of set bits is ODD.
//    // probably not worth the loss of readability but just did a lc on this :]
//    // https://leetcode.com/problems/number-of-1-bits/description/
//    uint8_t val = register_value;
//    while (val > 0)
//    {
//        val = val & (val-1)
//    }
//    return val % 2 == 0;

    int num_one_bits = 0;
    for (int i = 0; i < 8; i++)
    {
        uint8_t bit = register_value >> i;
        bit = bit & 0b00000001;
        num_one_bits += bit;
    }
    return num_one_bits % 2 == 0;
}

uint8_t get_carry_flag_from_sum_8b(uint8_t val0, uint8_t val1){
    // if sum is greater than max byte. ChatGPT helped me with this one.
    uint16_t v16_0 = val0;
    uint16_t v16_1 = val1;
    return ((v16_0 & 0x00FF) + (v16_1 & 0x00FF)) > 0x00FF;
}

uint8_t get_carry_flag_from_sum_16b(uint16_t val0, uint16_t val1){
    // Overload for register pair addition
    // if sum is greater than 2 bytes
    uint32_t v32_0 = val0;
    uint32_t v32_1 = val1;
    return v32_0 + v32_1 > 0xFFFF;
}

uint8_t get_aux_carry_flag_from_sum(uint8_t val0, uint8_t val1){
    // if sum is greater than max nibble. ChatGPT helped me with this one.
    return ((val0 & 0x0F) + (val1 & 0x0F)) > 0x0F;
}

uint8_t subtract_8b(struct State *state, uint8_t minuend, uint8_t subtrahend)
{
    // NOTE: The carry flag is cleared if there's a carry, and set if there's no carry.
        // This is opposite of the addition instructions.
    // val = minuend - subtrahend
    uint16_t twos_complement = ~(subtrahend) + 0x01;
    uint8_t res_8b = twos_complement + minuend;
    state->conditions.zero = minuend == subtrahend;
    state->conditions.carry = minuend < subtrahend;
    //state->conditions.aux_carry = !get_aux_carry_flag_from_sum(twos_complement, minuend);
    state->conditions.aux_carry = get_aux_carry_flag_from_sum(minuend, twos_complement);
    // TODO consider changer param name from "register_value".
    state->conditions.sign = get_sign_flag(res_8b);
    state->conditions.parity = get_parity_flag(res_8b);
    return res_8b;
}

uint16_t combine_bytes_to_word(uint8_t hi_byte, uint8_t lo_byte)
{
    uint16_t hi_byte_16 = hi_byte;
    uint16_t lo_byte_16 = lo_byte;
    return (hi_byte_16 << 8) + lo_byte_16;
}

void split_word_to_bytes(uint16_t word, uint8_t *hi_byte, uint8_t *lo_byte)
{
    *hi_byte = word >> 8;
    *lo_byte = word;
}

void unimplementedInstr(uint8_t opcode)
{
    printf("Error: Instruction 0x%02x not implemented.\n", opcode);
    exit(1);
}

