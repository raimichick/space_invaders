#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdlib.h>

int test_CMC(State *state, State *expected_state)
{
    // test carry switches 1->0
    state->memory[0] = CMC;
    state->conditions.carry = 1;

    expected_state->pc = 1;
    expected_state->conditions.carry = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // test carry switches 0->1
    state->pc = 0;
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->conditions.carry = 1;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_CMA(State *state, State *expected_state)
{
    // all zeros to all ones.
    state->memory[0] = CMA;
    state->a = 0b00000000;

    expected_state->pc = 1;
    expected_state->a = 0b11111111;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // all ones to all zeros.
    state->pc = 0;
    state->a = 0b11111111;

    expected_state->pc = 1;
    expected_state->a = 0b00000000;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // alternative zeros and ones
    state->pc = 0;
    state->a = 0b10101010;

    expected_state->pc = 1;
    expected_state->a = 0b01010101;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case CMC: result = test_CMC(state, expected_state); break;
    case CMA: result = test_CMA(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}