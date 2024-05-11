#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_NOP(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = NOP;

    // Set up the expected register states
    expected_state->pc = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_RIM(State *state, State *expected_state)
{
    state->memory[0] = RIM;
    expected_state->pc = 1;
    emulate8080(state);
    return state_compare(state, expected_state);
}

int test_SIM(State *state, State *expected_state)
{
    state->memory[0] = SIM;
    expected_state->pc = 1;
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
    case NOP: result = test_NOP(state, expected_state); break;
    case RIM: result = test_RIM(state, expected_state); break;
    case SIM: result = test_SIM(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}