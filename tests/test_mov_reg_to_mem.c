#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>

int test_MOV_M_A(State *state, State *expected_state)
{
    // Modify state for tests
    state->a = 5;
    state->memory[0] = 0x77;
    state->memory[1] = 1;
    state->h = 0;
    state->l = 2;

    // Set up the expected register states
    expected_state->a = 5;
    expected_state->h = 0;
    expected_state->l = 2;
    expected_state->pc = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) != PASS) return FAIL;
    if (state->memory[2] != 5) return FAIL;

    return PASS;
}

/* Tests for moving a value from a register to memory
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
    case 0x77:
        result = test_MOV_M_A(state, expected_state);
        break;
    default:
        return result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}
