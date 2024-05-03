#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_ADI_D8(State *state, State *expected_state)
{
    // Set state
    // Example from page 27 of the 8080 Programmers Manual
    state->memory[0] = 0xc6;
    state->memory[1] = 66;
    state->a = 20;
    state->conditions.zero = 1;
    state->conditions.sign = 1;
    state->conditions.aux_carry = 1;
    state->conditions.carry = 1;

    // Set expected state
    expected_state->a = 86;
    expected_state->pc = 2;
    expected_state->conditions.parity = 1;

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
    case 0xc6: result = test_ADI_D8(state, expected_state); break;
    default: return 1; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}