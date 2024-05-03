#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_DAD_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x09;
    state->h = 0x89;
    state->l = 0xab;
    state->b = 0xcd;
    state->c = 0xef;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x57;
    expected_state->l = 0x9a;
    expected_state->b = 0xcd;
    expected_state->c = 0xef;
    expected_state->conditions.carry = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DAD_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x19;
    state->h = 0x12;
    state->l = 0x34;
    state->d = 0x56;
    state->e = 0x78;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x68;
    expected_state->l = 0xac;
    expected_state->d = 0x56;
    expected_state->e = 0x78;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INX_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x13;
    state->d = 0x12;
    state->e = 0x34;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0x12;
    expected_state->e = 0x35;

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
    case 0x09:
        result = test_DAD_B(state, expected_state);
        break;
    case 0x13:
        result = test_INX_D(state, expected_state);
        break;
    case 0x19:
        result = test_DAD_D(state, expected_state);
        break;
    default:
        return 1; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}