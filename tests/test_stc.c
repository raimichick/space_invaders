#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_STC(State *state, State *expected_state)
{
    state->memory[0] = STC;
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->conditions.carry = 1;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    state->pc = 0;
    state->conditions.carry = 1;

    expected_state->pc = 1;
    expected_state->conditions.carry = 1;

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
    case STC: result = test_STC(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}