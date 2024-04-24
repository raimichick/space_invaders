#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_MVI_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x06;
    state->memory[1] = 0xd5;

    // Set up the expected register states
    expected_state->pc = 2;
    expected_state->b = 0xd5;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_MVI_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x0e;
    state->memory[1] = 0x23;

    // Set up the expected register states
    expected_state->pc = 2;
    expected_state->c = 0x23;

    emulate8080(state);

    return state_compare(state, expected_state);
}


/* Tests for various add instructions
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case 0x06:
        result = test_MVI_B(state, expected_state);
        break;
    case 0x0e:
        result = test_MVI_C(state, expected_state);
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