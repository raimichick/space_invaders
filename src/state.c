#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/state.h"

#define MEM_SIZE 0x10000

#define RED_TXT_COLOR "\033[0;31m"
#define DEFAULT_TXT_COLOR "\033[0m"

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
    state->conditions.pad0 = 0;
    state->conditions.pad1 = 0;
    state->conditions.pad2 = 0;

    state->interrupt_enabled = 0;

    // The program ROM starts at 0x0000 in memory
    state->pc = 0x0000;

    // Stack pointer is initialized by the ROM after start
    state->sp = 0x0000;

    for (int i = 0; i < sizeof state->ports; i++)
    {
        state->ports[i] = 0;
    }

    return state;
}

void Free8080(State *state)
{
    free(state->memory);
    free(state);
}

int state_compare(State *state, State *expected_state)
{
    // Compares each of the registers and conditions between the two states
    // If both states are the same, returns 0, else 1
    // Does not check memory

    const State *s = state;
    const State *es = expected_state;
    const Conditions s_cond = state->conditions;
    const Conditions es_cond = expected_state->conditions;

    printf(RED_TXT_COLOR); // prints after this will be in red;
    // clang-format off
    if (s->a  != es->a)     { printf("Err: A\n");   return FAIL; }
    if (s->b  != es->b)     { printf("Err: B\n");   return FAIL; }
    if (s->c  != es->c)     { printf("Err: C\n");   return FAIL; }
    if (s->d  != es->d)     { printf("Err: D\n");   return FAIL; }
    if (s->e  != es->e)     { printf("Err: E\n");   return FAIL; }
    if (s->h  != es->h)     { printf("Err: H\n");   return FAIL; }
    if (s->l  != es->l)     { printf("Err: L\n");   return FAIL; }
    if (s->sp != es->sp)    { printf("Err: SP\n");  return FAIL; }
    if (s->pc != es->pc)    { printf("Err: PC\n");  return FAIL; }

    if (s->interrupt_enabled != es->interrupt_enabled) { printf("Err: int_enable\n"); return FAIL; }
    if (s->halt != es->halt) { printf("Err: halt\n"); return FAIL; }

    if (s_cond.sign      != es_cond.sign)      { printf("Err: Sign\n");      return FAIL; }
    if (s_cond.zero      != es_cond.zero)      { printf("Err: Zero\n");      return FAIL; }
    if (s_cond.pad0      != es_cond.pad0)      { printf("Err: Pad0\n");      return FAIL; }
    if (s_cond.aux_carry != es_cond.aux_carry) { printf("Err: Aux_Carry\n"); return FAIL; }
    if (s_cond.pad1      != es_cond.pad1)      { printf("Err: Pad1\n");      return FAIL; }
    if (s_cond.parity    != es_cond.parity)    { printf("Err: Parity\n");    return FAIL; }
    if (s_cond.pad2      != es_cond.pad2)      { printf("Err: Pad2\n");      return FAIL; }
    if (s_cond.carry     != es_cond.carry)     { printf("Err: Carry\n");     return FAIL; }

    for (int i = 0; i < sizeof s->ports; i++)
    {
        if (s->ports[i] != es->ports[i]) { printf("Err: Port %d\n", i); return FAIL; }
    }

    // clang-format on
    printf(DEFAULT_TXT_COLOR); // prints after this will be in default color

    return PASS;
}

void set_conditions(State *state, uint8_t hex_val)
{
    state->conditions.sign = hex_val >> 7;
    state->conditions.zero = hex_val >> 6;
    state->conditions.pad0 = hex_val >> 5;
    state->conditions.aux_carry = hex_val >> 4;
    state->conditions.pad1 = hex_val >> 3;
    state->conditions.parity = hex_val >> 2;
    state->conditions.pad2 = hex_val >> 1;
    state->conditions.carry = hex_val >> 0;
}
