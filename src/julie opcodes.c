//
// Created by J Web on 4/20/2024.
//
#include "../include/disassemble8080p.h"
#include "../include/structs.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    state->program_counter = 0x0000;

    // Stack pointer is initialized by the ROM after start
    state->stack_pointer = 0x0000;

    return state;
}

void emulate8080(State *state)
{

    // Retrieve the opcode from memory at the current program counter location
    uint8_t *opcode = &state->memory[state->program_counter];

    switch (*opcode)
    {

    case 0x21:
        state->l = opcode[1];
        state->h = opcode[2];
        state->pc += 2;
        break;
    case 0x23:
        state->l++;
        if (state->l == 0)
            state->h++;
        break;
    case 0x26:
        state->h = opcode[1];
        state->pc++;
        break;
    case 0x29:
        {
            uint32_t hl = (state->h << 8) | state->l;
            uint32_t res = hl + hl;
            state->h = (res & 0xff00) >> 8;
            state->l = res & 0xff;
            state->cc.cy = ((res & 0xffff0000) != 0);
        }
            break;
    case 0x31:
        state->sp = (opcode[2]<<8) | opcode[1];
        state->pc += 2;
        break;
    case 0x32:
        {
            uint16_t offset = (opcode[2] << 8 | opcode[1]);
            state->memory[offset] = state->a;
            state->pc += 2;
        }
        break;
    case 0x36:
        {
            uint16_t offset = (state->h<<8) | state->l;
            state->memory[offset] = opcode[1];
            state->pc++;
        }
        break;
    case 0x3a:
        {
            uint16_t offset = (opcode[2]<<8) | (opcode[1]);
            state->a = state->memory[offset];
            state->pc+=2;
        }
        break;
    case 0x3e:
        state->a = opcode[1];
        state->pc++;
        break;
    case 0x56:
    {
        uint16_t offset = (state->h<<8) | (state->l);
        state->d = state->memory[offset];
    }
    break;
    case 0x66:
    {
        uint16_t offset = (state->h<<8) | (state->l);
        state->h = state->memory[offset];
    }
    break;
    case 0x6f: state->l = state->a; break;
    default:
        unimplementedInstr(*opcode);
        break;
    }
}