#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_EI(State *state, State *expected_state)
{
    state->memory[0] = EI;
    state->interrupt_enabled = 0;

    expected_state->pc = 1;
    expected_state->interrupt_enabled = 1;

    emulate8080(state);
    return state_compare(state, expected_state);
}

int test_DI(State *state, State *expected_state)
{
    state->memory[0] = DI;
    state->interrupt_enabled = 1;

    expected_state->pc = 1;
    expected_state->interrupt_enabled = 0;

    emulate8080(state);
    return state_compare(state, expected_state);
}

int test_HLT(State *state, State *expected_state)
{
    state->memory[0x40] = HLT;
    state->pc = 0x40;
    expected_state->pc = 0x40;

    if (emulate8080(state) != QUIT_CODE) return FAIL;

    return state_compare(state, expected_state);
}

int main(int argc, char *argv[])
{
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;
    switch (strtol(argv[1], NULL, 16))
    {
    case EI: result = test_EI(state, expected_state); break;
    case DI: result = test_DI(state, expected_state); break;
    case HLT: result = test_HLT(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    Free8080(state);
    Free8080(expected_state);

    return result;
}