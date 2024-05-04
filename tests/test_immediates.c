#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_ANI_D8(State *state, State *expected_state)
{
    // Example from 8080 Programmers Manual page 28
    state->memory[0] = 0xe6;
    state->memory[1] = 0x0f;
    state->a = 0x3a;
    state->conditions.carry = 1;
    state->conditions.zero = 1;
    state->conditions.sign = 1;
    state->conditions.parity = 0;

    expected_state->pc = 2;
    expected_state->a = 0x0a;
    expected_state->conditions.carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);
    return state_compare(state, expected_state);
}

/* Tests for loading values into registers
 * Select a test by passing the opcode value as the first argument
 */
int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;
    // clang-format off
    switch (strtol(argv[1], NULL, 16))
    {
        case 0xe6: result = test_ANI_D8(state, expected_state); break;
        default: result = FAIL; // Test failed due to incorrect test parameter
    }
    // clang-format on

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}