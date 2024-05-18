#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/state.h"

#define RED_TXT_COLOR "\033[0;31m"
#define DEFAULT_TXT_COLOR "\033[0m"

float cycles_elapsed = 0;

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
    state->memory = calloc(MEM_SIZE, sizeof(uint8_t));
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

    state->conditions.sign = 0;
    state->conditions.zero = 0;
    state->conditions.pad5 = 0; // always 0, per manual
    state->conditions.aux_carry = 0;
    state->conditions.pad3 = 0; // always 0, per manual
    state->conditions.parity = 0;
    state->conditions.pad1 = 0; // PUSH PSW will set this to 1.
    // Manual says always 1, set to zero to pass test. This
    // indicates that the pad values are
    // only given on PUSH PSW operation
    // https://retrocomputing.stackexchange.com/questions/12300/bit-one-of-the-intel-8080s-flags-register
    state->conditions.carry = 0;

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
    if (s_cond.pad5      != es_cond.pad5)      { printf("Err: Pad0\n");      return FAIL; }
    if (s_cond.aux_carry != es_cond.aux_carry) { printf("Err: Aux_Carry\n"); return FAIL; }
    if (s_cond.pad3      != es_cond.pad3)      { printf("Err: Pad1\n");      return FAIL; }
    if (s_cond.parity    != es_cond.parity)    { printf("Err: Parity\n");    return FAIL; }
    if (s_cond.pad1      != es_cond.pad1)      { printf("Err: Pad2\n");      return FAIL; }
    if (s_cond.carry     != es_cond.carry)     { printf("Err: Carry\n");     return FAIL; }

    for (int i = 0; i < sizeof s->ports; i++)
    {
        if (s->ports[i] != es->ports[i]) { printf("Err: Port %d\n", i); return FAIL; }
    }

    // clang-format on
    printf(DEFAULT_TXT_COLOR); // prints after this will be in default color

    return PASS;
}

int state_compare_to_js_site(State *state, State *expected_state)
{
    // same as state_compare but ignores items that the JS site doesn't give us. Or where there is a
    // know error in the js site (parity, for example)
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

    if (s_cond.sign      != es_cond.sign)      { printf("Err: Sign\n");      return FAIL; }
    if (s_cond.zero      != es_cond.zero)      { printf("Err: Zero\n");      return FAIL; }
    if (s_cond.pad5      != es_cond.pad5)      { printf("Err: Pad0\n");      return FAIL; }
    if (s_cond.aux_carry != es_cond.aux_carry) { printf("Err: Aux_Carry\n"); return FAIL; }
    if (s_cond.pad3      != es_cond.pad3)      { printf("Err: Pad1\n");      return FAIL; }
//    if (s_cond.parity    != es_cond.parity)    { printf("Err: Parity\n");    return FAIL; }
    if (s_cond.pad1      != es_cond.pad1)      { printf("Err: Pad2\n");      return FAIL; }
    if (s_cond.carry     != es_cond.carry)     { printf("Err: Carry\n");     return FAIL; }

    // clang-format on
    printf(DEFAULT_TXT_COLOR); // prints after this will be in default color

    return PASS;
}

void set_conditions(State *state, uint8_t byte_val)
{
    state->conditions.sign = byte_val >> 7;
    state->conditions.zero = byte_val >> 6;
    state->conditions.pad5 = byte_val >> 5;
    state->conditions.aux_carry = byte_val >> 4;
    state->conditions.pad3 = byte_val >> 3;
    state->conditions.parity = byte_val >> 2;
    state->conditions.pad1 = byte_val >> 1;
    state->conditions.carry = byte_val >> 0;
}

uint8_t get_conditions_byte(const State *state)
{
    uint8_t S = state->conditions.sign << 7;
    uint8_t Z = state->conditions.zero << 6;
    uint8_t PAD5 = state->conditions.pad5 << 5;
    uint8_t AC = state->conditions.aux_carry << 4;
    uint8_t PAD3 = state->conditions.pad3 << 3;
    uint8_t P = state->conditions.parity << 2;
    uint8_t PAD1 = state->conditions.pad1 << 1;
    uint8_t C = state->conditions.carry << 0;
    return S | Z | PAD5 | AC | PAD3 | P | PAD1 | C;
}

// clang-format off
void set_reg_pair(State *state, const char *reg_pair, uint16_t bit16_val)
{
    // find correct register pairs
    if (strcmp(reg_pair, "af") == 0) { state->a = bit16_val >> 8; set_conditions(state, bit16_val); }
    if (strcmp(reg_pair, "bc") == 0) { state->b = bit16_val >> 8; state->c = bit16_val; }
    if (strcmp(reg_pair, "de") == 0) { state->d = bit16_val >> 8; state->e = bit16_val; }
    if (strcmp(reg_pair, "hl") == 0) { state->h = bit16_val >> 8; state->l = bit16_val; }
}
// clang-format on

void print_next_x_operations(const State *state, int num_ops, int cur_op_num)
{
    for (int i = 0; i < 5; i++) printf("\n");
    printf("OPERATION #: %d: \n", cur_op_num);
    for (int i = 0; i < num_ops; i++) disassemble8080p(state->memory, state->pc + i);
}
