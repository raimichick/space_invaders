#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_RAL(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = RAL;
    state->a = 0b10110101;
    state->conditions.carry = 0;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0b01101010;
    expected_state->conditions.carry = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_RAR(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = RAR;
    state->a = 0b01101010;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0b10110101;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_RLC(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = RLC;
    state->a = 0b10100101;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0b01001011;
    expected_state->conditions.carry = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_RRC(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = RRC;
    state->a = 0b01001011;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0b10100101;
    expected_state->conditions.carry = 1;

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
    case RAL: result = test_RAL(state, expected_state); break;
    case RAR: result = test_RAR(state, expected_state); break;
    case RLC: result = test_RLC(state, expected_state); break;
    case RRC: result = test_RRC(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);
    return result;
}