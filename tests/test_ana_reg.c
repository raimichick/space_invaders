#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdlib.h>

int test_ANA_B(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->b = 0x00;
    state->conditions.carry = 1;
    state->memory[0] = 0xa0;

    // Set expected state
    expected_state->a = 0x00;
    expected_state->b = 0x00;
    expected_state->pc = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ANA_C(State *state, State *expected_state)
{
    // Set state
    state->a = 0xF0;
    state->c = 0x0F;
    state->conditions.carry = 1;
    state->memory[0] = 0xa1;

    // Set expected state
    expected_state->a = 0x00;
    expected_state->c = 0x0F;
    expected_state->pc = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ANA_D(State *state, State *expected_state)
{
    // Set state
    state->a = 0xFF;
    state->d = 0xFF;
    state->conditions.carry = 1;
    state->conditions.zero = 1;
    state->memory[0] = 0xa2;

    // Set expected state
    expected_state->a = 0xFF;
    expected_state->d = 0xFF;
    expected_state->pc = 1;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ANA_E(State *state, State *expected_state)
{
    // Set state
    state->a = 0xCD;
    state->e = 0xCD;
    state->conditions.carry = 1;
    state->memory[0] = 0xa3;

    // Set expected state
    expected_state->a = 0xCD;
    expected_state->e = 0xCD;
    expected_state->pc = 1;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ANA_H(State *state, State *expected_state)
{
    // Set state
    state->a = 0xDE;
    state->h = 0xCC;
    state->conditions.carry = 1;
    state->memory[0] = 0xa4;

    // Set expected state
    expected_state->a = 0xCC;
    expected_state->h = 0xCC;
    expected_state->pc = 1;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ANA_L(State *state, State *expected_state)
{
    // Set state
    state->a = 0x82;
    state->l = 0x42;
    state->conditions.carry = 1;
    state->memory[0] = 0xa5;

    // Set expected state
    expected_state->a = 0x02;
    expected_state->l = 0x42;
    expected_state->pc = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ANA_M(State *state, State *expected_state)
{
    // Set state
    state->a = 0x33;
    state->h = 0x01;
    state->l = 0xFF;
    state->conditions.carry = 1;
    state->memory[0] = 0xa6;
    state->memory[0x01FF] = 0x22;

    // Set expected state
    expected_state->a = 0x22;
    expected_state->memory[0x01FF] = 0x22;
    expected_state->h = 0x01;
    expected_state->l = 0xFF;
    expected_state->pc = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ANA_A(State *state, State *expected_state)
{
    // Set state
    state->a = 0xCC;
    state->conditions.carry = 1;
    state->memory[0] = 0xa7;

    // Set expected state
    expected_state->a = 0xCC;
    expected_state->pc = 1;
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
    case 0xa0: result = test_ANA_B(state, expected_state); break;
    case 0xa1: result = test_ANA_C(state, expected_state); break;
    case 0xa2: result = test_ANA_D(state, expected_state); break;
    case 0xa3: result = test_ANA_E(state, expected_state); break;
    case 0xa4: result = test_ANA_H(state, expected_state); break;
    case 0xa5: result = test_ANA_L(state, expected_state); break;
    case 0xa6: result = test_ANA_M(state, expected_state); break;
    case 0xa7: result = test_ANA_A(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}