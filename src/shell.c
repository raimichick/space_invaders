#include "../include/disassemble8080p.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Conditions
{
    uint8_t zero : 1;
    uint8_t sign : 1;
    uint8_t parity : 1;
    uint8_t carry : 1;
    uint8_t aux_carry : 1;
    uint8_t pad : 3;
} Conditions;

typedef struct State
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t stack_pointer;
    uint16_t program_counter;
    uint8_t *memory;
    Conditions conditions;
    uint8_t int_enable;
} State;

void unimplementedInstr(uint8_t opcode)
{
    printf("Error: Instruction 0x%02x not implemented.\n", opcode);
    exit(1);
}

State *Init8080(void)
{
    // Reserve memory for the state struct
    State *state = calloc(1, sizeof(State));

    // Reserve memory for the 16KB of RAM
    state->memory = malloc(0x10000);

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
    default:
        unimplementedInstr(*opcode);
        break;
    }
}