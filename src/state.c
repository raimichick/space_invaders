#include <stdio.h>
#include <stdlib.h>

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
    state->conditions.pad = 0;

    // The program ROM starts at 0x0000 in memory
    state->pc = 0x0000;

    // Stack pointer is initialized by the ROM after start
    state->sp = 0x0000;

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

    // clang-format off
    printf(RED_TXT_COLOR); // anything printed after this will be in red;
    if (state->a != expected_state->a)      { printf("Err: A\n");   return 1; }
    if (state->b != expected_state->b)      { printf("Err: B\n");   return 1; }
    if (state->c != expected_state->c)      { printf("Err: C\n");   return 1; }
    if (state->d != expected_state->d)      { printf("Err: D\n");   return 1; }
    if (state->e != expected_state->e)      { printf("Err: E\n");   return 1; }
    if (state->h != expected_state->h)      { printf("Err: H\n");   return 1; }
    if (state->l != expected_state->l)      { printf("Err: L\n");   return 1; }
    if (state->sp != expected_state->sp)    { printf("Err: SP\n");  return 1; }
    if (state->pc != expected_state->pc)    { printf("Err: PC\n");  return 1; }

    if (state->int_enable != expected_state->int_enable) { printf("Err: int_enable\n"); return 1; }

    if (state->conditions.zero != expected_state->conditions.zero)          { printf("Err: Zero\n");     return 1; }
    if (state->conditions.sign != expected_state->conditions.sign)          { printf("Err: Sign\n");     return 1; }
    if (state->conditions.parity != expected_state->conditions.parity)      { printf("Err: Parity\n");   return 1; }
    if (state->conditions.carry != expected_state->conditions.carry)        { printf("Err: Carry\n");    return 1; }
    if (state->conditions.aux_carry != expected_state->conditions.aux_carry){ printf("Err: Aux_Carry\n");return 1; }
    if (state->conditions.pad != expected_state->conditions.pad)            { printf("Err: Pad\n");      return 1; }
    printf(DEFAULT_TXT_COLOR); // anything printed after this will be in default color
    // clang-format on

    return 0;
}
