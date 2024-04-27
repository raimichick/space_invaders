#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_XCHG(State *state, State *expected_state)
{
    // Example from 8080 Programmers Manual page 25
    state->memory[0] = 0xeb;
    state->d = 0x33;
    state->e = 0x55;
    state->h = 0x00;
    state->l = 0xff;

    expected_state->pc = 1;
    expected_state->d = 0x00;
    expected_state->e = 0xff;
    expected_state->h = 0x33;
    expected_state->l = 0x55;

    emulate8080(state);
    return state_compare(state, expected_state) == 1;
}

int main(int argc, char *argv[])
{
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;
    // clang-format off
    switch (strtol(argv[1], NULL, 16))
    {
        case 0xeb: result = test_XCHG(state, expected_state); break;
        default: return 1; // Test failed due to incorrect test parameter
    }
    // clang-format on

    Free8080(state);
    Free8080(expected_state);

    return result;
}