#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_DCR_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x05;
    state->memory[1] = 0x05;
    state->b = 0x01;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->b = 0x00;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) != 0) return 1;

    // Set up the expected register states
    expected_state->pc = 2;
    expected_state->b = 0xff;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x0d;
    state->c = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->c = 0xfe;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

/* Tests for various subtract instructions
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
    case 0x05:
        result = test_DCR_B(state, expected_state);
        break;
    case 0x0d:
        result = test_DCR_C(state, expected_state);
        break;
    default:
        return 1; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}