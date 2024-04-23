#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdlib.h>

int test_JMP(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xc3;
    state->memory[1] = 0x05;
    state->memory[2] = 0x00;

    // Set expected state
    state->pc = 5;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_JNZ(State *state, State *expected_state)
{
    // Set state

    // Set expected state

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
    case 0xc2:
        result = test_JNZ(state, expected_state);
        break;
    case 0xc3:
        result = test_JMP(state, expected_state);
        break;
    default:
        return 1; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    free(state->memory);
    free(expected_state->memory);
    free(state);
    free(expected_state);

    return result;
}