#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_RNZ(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xc0;
    state->memory[1] = 0xc0;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.zero = 1; // block first return operation
    emulate8080(state);
    state->conditions.zero = 0; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;

    return state_compare(state, expected_state);
}

int test_RZ(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xc8;
    state->memory[1] = 0xc8;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.zero = 0; // block first return operation
    emulate8080(state);
    state->conditions.zero = 1; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;
    expected_state->conditions.zero = 1;

    return state_compare(state, expected_state);
}

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

int test_RNC(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xd0;
    state->memory[1] = 0xd0;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.carry = 1; // block first return operation
    emulate8080(state);
    state->conditions.carry = 0; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;

    return state_compare(state, expected_state);
}

int test_RC(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xd8;
    state->memory[1] = 0xd8;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.carry = 0; // block first return operation
    emulate8080(state);
    state->conditions.carry = 1; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;
    expected_state->conditions.carry = 1;

    return state_compare(state, expected_state);
}

int test_RPO(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xe0;
    state->memory[1] = 0xe0;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.parity = 1; // block first return operation
    emulate8080(state);
    state->conditions.parity = 0; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;

    return state_compare(state, expected_state);
}

int test_RPE(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xe8;
    state->memory[1] = 0xe8;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.parity = 0; // block first return operation
    emulate8080(state);
    state->conditions.parity = 1; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;
    expected_state->conditions.parity = 1;

    return state_compare(state, expected_state);
}

int test_RP(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xf0;
    state->memory[1] = 0xf0;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.sign = 1; // block first return operation
    emulate8080(state);
    state->conditions.sign = 0; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;

    return state_compare(state, expected_state);
}

int test_RM(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xf8;
    state->memory[1] = 0xf8;
    state->sp = 0x1384;
    state->memory[state->sp - 2] = 0x02;
    state->memory[state->sp - 1] = 0x01;
    state->sp -= 2;

    state->conditions.sign = 0; // block first return operation
    emulate8080(state);
    state->conditions.sign = 1; // allow second return operation
    emulate8080(state);

    // Set expected state
    expected_state->pc = 0x0102;
    expected_state->sp = 0x1384;
    expected_state->conditions.sign = 1;

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
    case 0xc0: result = test_RNZ(state, expected_state); break;
    case 0xc8: result = test_RZ(state, expected_state); break;
    case 0xc9: result = test_RET(state, expected_state); break;
    case 0xd0: result = test_RNC(state, expected_state); break;
    case 0xd8: result = test_RC(state, expected_state); break;
    case 0xe0: result = test_RPO(state, expected_state); break;
    case 0xe8: result = test_RPE(state, expected_state); break;
    case 0xf0: result = test_RP(state, expected_state); break;
    case 0xf8: result = test_RM(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}