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
    return state_compare(state, expected_state) == 1;
}

int test_CMP_B(State *state, State *expected_state)
{
    // Ex 1 from 8080 manual
    state->memory[0] = CMP_B;
    state->a = 0x0a;
    state->b = 0x05;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.zero = 1;
    state->conditions.parity = 1;
    state->conditions.sign = 1;

    expected_state->pc = 1;
    expected_state->a = 0x0a;
    expected_state->b = 0x05;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // Ex 2 from 8080 manual
    state->pc = 0;
    state->a = 0x02;
    state->b = 0x05;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.zero = 1;
    state->conditions.parity = 1;
    state->conditions.sign = 1;

    expected_state->pc = 1;
    expected_state->a = 0x02;
    expected_state->b = 0x05;
    expected_state->conditions.carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // Ex 3 from 8080 manual
    state->pc = 0;
    state->a = -0x1b;
    state->b = 0x05;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.zero = 1;
    state->conditions.parity = 1;
    state->conditions.sign = 1;

    expected_state->pc = 1;
    expected_state->a = -0x1b;
    expected_state->b = 0x05;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;
    return 0;
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
        case CMP_B: result = test_CMP_B(state, expected_state); break;
        default: result = 1; // Test failed due to incorrect test parameter
        return result;
    }
    // clang-format on

    Free8080(state);
    Free8080(expected_state);

    return result;
}