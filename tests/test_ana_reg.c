#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

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
    case 0xa7:
        result = test_ANA_A(state, expected_state);
        break;
    default:
        return 1; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}