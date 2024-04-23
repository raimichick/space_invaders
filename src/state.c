#include <stdio.h>
#include <stdlib.h>

#include "../include/state.h"

#define MEM_SIZE 0x10000

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
    state->memory = malloc(MEM_SIZE);
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

int state_compare(State *state, State *expected_state)
{
    // Compares each of the registers and conditions between the two states
    // If both states are the same, returns 0, else 1
    // Does not check memory

    if (state->a != expected_state->a) return 1;
    if (state->b != expected_state->b) return 1;
    if (state->c != expected_state->c) return 1;
    if (state->d != expected_state->d) return 1;
    if (state->e != expected_state->e) return 1;
    if (state->h != expected_state->h) return 1;
    if (state->l != expected_state->l) return 1;
    if (state->sp != expected_state->sp) return 1;
    if (state->pc != expected_state->pc) return 1;
    if (state->int_enable != expected_state->int_enable) return 1;

    if (state->conditions.zero != expected_state->conditions.zero) return 1;
    if (state->conditions.sign != expected_state->conditions.sign) return 1;
    if (state->conditions.parity != expected_state->conditions.parity) return 1;
    if (state->conditions.carry != expected_state->conditions.carry) return 1;
    if (state->conditions.aux_carry != expected_state->conditions.aux_carry)
        return 1;
    if (state->conditions.pad != expected_state->conditions.pad) return 1;

    return 0;
}

int state_mem_compare(State *state, State *expected_state)
{
    /** return 1 if NOT equal */
    for (size_t i = 0; i < MEM_SIZE; i++)
    {
        if (state->memory[i] != expected_state->memory[i]) return 1;
    }
    return 0;
}
