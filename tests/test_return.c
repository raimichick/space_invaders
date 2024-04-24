#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_RET(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xc9;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;

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
    case 0xc9:
        result = test_RET(state, expected_state);
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