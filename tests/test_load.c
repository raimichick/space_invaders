#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_LXI_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x01;
    state->memory[1] = 0xaa;
    state->memory[2] = 0x35;

    // Set up the expected register states
    expected_state->pc = 3;
    expected_state->b = 0x35;
    expected_state->c = 0xaa;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_LXI_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x11;
    state->memory[1] = 0x27;
    state->memory[2] = 0x89;

    // Set up the expected register states
    expected_state->pc = 3;
    expected_state->d = 0x89;
    expected_state->e = 0x27;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_LDAX_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x1a;
    state->memory[0x1234] = 0xf6;
    state->d = 0x12;
    state->e = 0x34;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0x12;
    expected_state->e = 0x34;
    expected_state->a = 0xf6;

    emulate8080(state);

    return state_compare(state, expected_state);
}

/* Tests for loading values into registers
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
    case 0x01:
        result = test_LXI_B(state, expected_state);
        break;
    case 0x11:
        result = test_LXI_D(state, expected_state);
        break;
    case 0x1a:
        result = test_LDAX_D(state, expected_state);
        break;
    default:
        return 1; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}