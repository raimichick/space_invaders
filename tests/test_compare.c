#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_CPI_D8(State *state, State *expected_state)
{
    state->memory[0] = CPI;
    state->memory[1] = 0x40;
    state->a = 0x4a;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.zero = 1;
    state->conditions.parity = 1;
    state->conditions.sign = 1;

    expected_state->pc = 2;
    expected_state->a = 0x4a;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;

    emulate8080(state);
    return state_compare(state, expected_state);
}

int test_CMP_BCDEHL(State *state, State *expected_state, uint8_t opcode)
{
    uint8_t *state_reg = 0;
    uint8_t *exp_state_reg = 0;

    // clang-format off
    switch (opcode)
    {
        case CMP_B: state_reg = &state->b; exp_state_reg = &expected_state->b; break;
        case CMP_C: state_reg = &state->c; exp_state_reg = &expected_state->c; break;
        case CMP_D: state_reg = &state->d; exp_state_reg = &expected_state->d; break;
        case CMP_E: state_reg = &state->e; exp_state_reg = &expected_state->e; break;
        case CMP_H: state_reg = &state->h; exp_state_reg = &expected_state->h; break;
        case CMP_L: state_reg = &state->l; exp_state_reg = &expected_state->l; break;
        default: return FAIL;
    }
    // clang-format on

    // Ex 1 from 8080 manual
    state->memory[0] = opcode;
    state->a = 0x0a;
    *state_reg = 0x05;

    expected_state->pc = 1;
    expected_state->a = 0x0a;
    *exp_state_reg = 0x05;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Ex 2 from 8080 manual
    state->pc = 0;
    state->a = 0x02;
    *state_reg = 0x05;

    expected_state->pc = 1;
    expected_state->a = 0x02;
    *exp_state_reg = 0x05;
    expected_state->conditions.carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Ex 3 from 8080 manual
    state->pc = 0;
    state->a = -0x1b;
    *state_reg = 0x05;

    expected_state->pc = 1;
    expected_state->a = -0x1b;
    *exp_state_reg = 0x05;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return 0;
}

int test_CMP_M(State *state, State *expected_state)
{
    // Ex 1 from 8080 manual
    state->memory[0] = CMP_M;
    state->a = 0x0a;
    state->h = 0x11;
    state->l = 0x55;
    state->memory[0x1155] = 0x05;

    expected_state->pc = 1;
    expected_state->a = 0x0a;
    expected_state->h = 0x11;
    expected_state->l = 0x55;
    expected_state->memory[0x1155] = 0x05;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x1155] != expected_state->memory[0x1155]) return FAIL;

    // Ex 2 from 8080 manual
    state->pc = 0;
    state->a = 0x02;
    state->h = 0x11;
    state->l = 0x55;
    state->memory[0x1155] = 0x05;

    expected_state->pc = 1;
    expected_state->a = 0x02;
    state->h = 0x11;
    state->l = 0x55;
    state->memory[0x1155] = 0x05;
    expected_state->conditions.carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x1155] != expected_state->memory[0x1155]) return FAIL;

    // Ex 3 from 8080 manual
    state->pc = 0;
    state->a = -0x1b;
    state->h = 0x11;
    state->l = 0x55;
    state->memory[0x1155] = 0x05;

    expected_state->pc = 1;
    expected_state->a = -0x1b;
    state->h = 0x11;
    state->l = 0x55;
    state->memory[0x1155] = 0x05;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x1155] != expected_state->memory[0x1155]) return FAIL;

    return 0;
}

int test_CMP_A(State *state, State *expected_state)
{
    // state->a is positive
    state->memory[0] = CMP_A;
    state->a = 0x55;

    expected_state->pc = 1;
    expected_state->a = 0x55;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // state->a is 0
    state->pc = 0;
    state->a = 0x0;

    expected_state->pc = 1;
    expected_state->a = 0x0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // state->a is negative
    state->pc = 0;
    state->a = -0x55;

    expected_state->pc = 1;
    expected_state->a = -0x55;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    return PASS;
}

int main(int argc, char *argv[])
{
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;
    // clang-format off
    switch (strtol(argv[1], NULL, 16))
    {
        case CPI: result = test_CPI_D8(state, expected_state); break;
        case CMP_B: result = test_CMP_BCDEHL(state, expected_state, CMP_B); break;
        case CMP_C: result = test_CMP_BCDEHL(state, expected_state, CMP_C); break;
        case CMP_D: result = test_CMP_BCDEHL(state, expected_state, CMP_D); break;
        case CMP_E: result = test_CMP_BCDEHL(state, expected_state, CMP_E); break;
        case CMP_H: result = test_CMP_BCDEHL(state, expected_state, CMP_H); break;
        case CMP_L: result = test_CMP_BCDEHL(state, expected_state, CMP_L); break;
        case CMP_M: result = test_CMP_M(state, expected_state); break;
        case CMP_A: result = test_CMP_A(state, expected_state); break;
        default: result = FAIL; // Test failed due to incorrect test parameter
    }
    // clang-format on

    Free8080(state);
    Free8080(expected_state);

    return result;
}