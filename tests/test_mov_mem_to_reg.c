#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>

int test_MOV_A_M(State *state, State *expected_state)
{
    // Modify state for tests
    state->memory[0] = 0x7e;
    state->memory[1] = 1;
    state->memory[2] = 5;
    state->h = 0;
    state->l = 2;

    // Set up the expected register states
    expected_state->a = 5;
    expected_state->h = 0;
    expected_state->l = 2;
    expected_state->pc = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

/* Tests for moving a value from memory to a register
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    // Set up states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case 0x7e: result = test_MOV_A_M(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}
