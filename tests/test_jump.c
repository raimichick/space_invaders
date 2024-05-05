#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdlib.h>

int test_JNZ(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xc2;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xc2;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.zero = 1; // block first jump operation
    emulate8080(state);
    state->conditions.zero = 0; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;

    return state_compare(state, expected_state);
}

int test_JMP(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xc3;
    state->memory[1] = 0x05;
    state->memory[2] = 0x00;

    // Set expected state
    expected_state->pc = 5;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_JZ(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xca;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xca;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.zero = 0; // block first jump operation
    emulate8080(state);
    state->conditions.zero = 1; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;
    expected_state->conditions.zero = 1;

    return state_compare(state, expected_state);
}

int test_JNC(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xd2;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xd2;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.carry = 1; // block first jump operation
    emulate8080(state);
    state->conditions.carry = 0; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;

    return state_compare(state, expected_state);
}

int test_JC(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xda;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xda;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.carry = 0; // block first jump operation
    emulate8080(state);
    state->conditions.carry = 1; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;
    expected_state->conditions.carry = 1;

    return state_compare(state, expected_state);
}

int test_JPO(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xe2;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xe2;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.parity = 1; // block first jump operation
    emulate8080(state);
    state->conditions.parity = 0; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;

    return state_compare(state, expected_state);
}

int test_PCHL(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xe9;
    state->l = 0xff;
    state->h = 0x11;

    // Expected state
    expected_state->pc = 0x11ff;
    expected_state->l = 0xff;
    expected_state->h = 0x11;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_JPE(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xea;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xea;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.parity = 0; // block first jump operation
    emulate8080(state);
    state->conditions.parity = 1; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;
    expected_state->conditions.parity = 1;

    return state_compare(state, expected_state);
}

int test_JP(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xf2;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xf2;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.sign = 1; // block first jump operation
    emulate8080(state);
    state->conditions.sign = 0; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;

    return state_compare(state, expected_state);
}

int test_JM(State *state, State *expected_state)
{
    // Set state
    state->memory[0] = 0xfa;
    state->memory[1] = 0x06;
    state->memory[2] = 0x00;
    state->memory[3] = 0xfa;
    state->memory[4] = 0xff;
    state->memory[5] = 0x11;

    state->conditions.sign = 0; // block first jump operation
    emulate8080(state);
    state->conditions.sign = 1; // allow second jump operation
    emulate8080(state);

    // Set expected state - after one jump blocked, one jump executed
    expected_state->pc = 0x11ff;
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
    case 0xc2: result = test_JNZ(state, expected_state); break;
    case 0xc3: result = test_JMP(state, expected_state); break;
    case 0xca: result = test_JZ(state, expected_state); break;
    case 0xd2: result = test_JNC(state, expected_state); break;
    case 0xda: result = test_JC(state, expected_state); break;
    case 0xe2: result = test_JPO(state, expected_state); break;
    case 0xe9: result = test_PCHL(state, expected_state); break;
    case 0xea: result = test_JPE(state, expected_state); break;
    case 0xf2: result = test_JP(state, expected_state); break;
    case 0xfa: result = test_JM(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}