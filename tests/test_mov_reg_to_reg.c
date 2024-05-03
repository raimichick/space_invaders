#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>

int test_MOV_A_D(State *state, State *expected_state)
{
    // Modify state for tests
    state->d = 5;
    state->memory[0] = 0x7a;
    state->memory[1] = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 5;
    expected_state->d = 5;

    // Run command to test
    emulate8080(state);

    // Validate output - Reg A = 5, pc advanced by 1
    return state_compare(state, expected_state);
}

int test_MOV_A_E(State *state, State *expected_state)
{
    // Modify state for tests
    state->e = 5;
    state->memory[0] = 0x7b;
    state->memory[1] = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 5;
    expected_state->e = 5;

    // Run command to test
    emulate8080(state);

    // Validate output - Reg A = 5, pc advanced by 1
    return state_compare(state, expected_state);
}

int test_MOV_A_H(State *state, State *expected_state)
{
    // Modify state for tests
    state->h = 5;
    state->memory[0] = 0x7c;
    state->memory[1] = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 5;
    expected_state->h = 5;

    // Run command to test
    emulate8080(state);

    // Validate output - Reg A = 5, pc advanced by 1
    return state_compare(state, expected_state);
}

/* Tests for moving a value from one register to another
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
    case 0x7a: result = test_MOV_A_D(state, expected_state); break;
    case 0x7b: result = test_MOV_A_E(state, expected_state); break;
    case 0x7c: result = test_MOV_A_H(state, expected_state); break;
    default:
        return result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}