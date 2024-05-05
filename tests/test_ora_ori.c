#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdlib.h>

int test_ORA_B(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->b = 0xF0;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 0;
    state->memory[0] = 0xb0;

    // Set expected state
    expected_state->a = 0xFF;
    expected_state->b = 0xF0;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ORA_C(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->c = 0x0F;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 0;
    state->memory[0] = 0xb1;

    // Set expected state
    expected_state->a = 0xFF;
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

int test_ORA_D(State *state, State *expected_state)
{
    // Set state
    state->a = 0x00;
    state->d = 0xFF;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 0;
    state->memory[0] = 0xb2;

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

int test_ORA_E(State *state, State *expected_state)
{
    // Set state
    state->a = 0xAA;
    state->e = 0x55;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xb3;

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

int test_ORA_H(State *state, State *expected_state)
{
    // Set state
    state->a = 0x36;
    state->h = 0x19;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xb4;

    // Set expected state
    expected_state->a = 0x3F;
    expected_state->h = 0x19;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ORA_L(State *state, State *expected_state)
{
    // Set state
    state->a = 0x00;
    state->l = 0x00;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xb5;

    // Set expected state
    expected_state->a = 0x00;
    expected_state->l = 0x00;
    expected_state->pc = 1;
    expected_state->conditions.zero = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ORA_M(State *state, State *expected_state)
{
    // Set state
    state->a = 0x00;
    state->h = 0x01;
    state->l = 0xFF;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xb6;
    state->memory[0x01FF] = 0x01;

    // Set expected state
    expected_state->a = 0x01;
    expected_state->h = 0x01;
    expected_state->l = 0xFF;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ORA_A(State *state, State *expected_state)
{
    // Set state
    state->a = 0x20;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xb7;

    // Set expected state
    expected_state->a = 0x20;
    expected_state->pc = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ORI(State *state, State *expected_state)
{
    // Set state
    state->a = 0x11;
    state->conditions.carry = 1;
    state->conditions.sign = 1;
    state->memory[0] = 0xf6;
    state->memory[1] = 0xDD;

    // Set expected state
    expected_state->a = 0xDD;
    expected_state->pc = 2;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
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
    case 0xb0: result = test_ORA_B(state, expected_state); break;
    case 0xb1: result = test_ORA_C(state, expected_state); break;
    case 0xb2: result = test_ORA_D(state, expected_state); break;
    case 0xb3: result = test_ORA_E(state, expected_state); break;
    case 0xb4: result = test_ORA_H(state, expected_state); break;
    case 0xb5: result = test_ORA_L(state, expected_state); break;
    case 0xb6: result = test_ORA_M(state, expected_state); break;
    case 0xb7: result = test_ORA_A(state, expected_state); break;
    case 0xf6: result = test_ORI(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}