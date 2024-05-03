#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdlib.h>

int test_XRA_B(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->b = 0xF0;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xa8;

    // Set expected state
    expected_state->a = 0x0F;
    expected_state->b = 0xF0;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRA_C(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->c = 0x0F;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xa9;

    // Set expected state
    expected_state->a = 0xF0;
    expected_state->c = 0x0F;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRA_D(State *state, State *expected_state)
{
    // Set state
    state->a = 0x00;
    state->d = 0xFF;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xaa;

    // Set expected state
    expected_state->a = 0xFF;
    expected_state->d = 0xFF;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRA_E(State *state, State *expected_state)
{
    // Set state
    state->a = 0xAA;
    state->e = 0x55;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xab;

    // Set expected state
    expected_state->a = 0xFF;
    expected_state->e = 0x55;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRA_H(State *state, State *expected_state)
{
    // Set state
    state->a = 0x36;
    state->h = 0x19;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xac;

    // Set expected state
    expected_state->a = 0x2F;
    expected_state->h = 0x19;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRA_L(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->l = 0xFF;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xad;

    // Set expected state
    expected_state->a = 0x00;
    expected_state->l = 0xFF;
    expected_state->pc = 1;
    expected_state->conditions.zero = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRA_M(State *state, State *expected_state)
{
    // Set state
    state->a = 0xDD;
    state->h = 0x01;
    state->l = 0xFF;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xae;
    state->memory[0x01FF] = 0x22;

    // Set expected state
    expected_state->a = 0xFF;
    expected_state->h = 0x01;
    expected_state->l = 0xFF;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRA_A(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xaf;

    // Set expected state
    expected_state->a = 0x00;
    expected_state->pc = 1;
    expected_state->conditions.zero = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_XRI(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->conditions.carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xee;
    state->memory[1] = 0xDD;

    // Set expected state
    expected_state->a = 0x22;
    expected_state->pc = 2;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case 0xa8: result = test_XRA_B(state, expected_state); break;
    case 0xa9: result = test_XRA_C(state, expected_state); break;
    case 0xaa: result = test_XRA_D(state, expected_state); break;
    case 0xab: result = test_XRA_E(state, expected_state); break;
    case 0xac: result = test_XRA_H(state, expected_state); break;
    case 0xad: result = test_XRA_L(state, expected_state); break;
    case 0xae: result = test_XRA_M(state, expected_state); break;
    case 0xaf: result = test_XRA_A(state, expected_state); break;
    case 0xee: result = test_XRI(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}