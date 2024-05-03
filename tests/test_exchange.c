#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_XCHG(State *state, State *expected_state)
{
    // Example from 8080 Programmers Manual page 25
    state->memory[0] = XCHG;
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
    return state_compare(state, expected_state);
}

int test_XTHL(State *state, State *expected_state)
{
    // Example from 8080 Programmers Manual page 25
    state->memory[0] = XTHL;
    state->sp = 0x10ad;
    state->memory[0x10ac] = 0xff;
    state->memory[0x10ad] = 0xf0;
    state->memory[0x10ae] = 0x0d;
    state->memory[0x10af] = 0xff;
    state->h = 0x0b;
    state->l = 0x3c;

    expected_state->pc = 1;
    expected_state->sp = 0x10ad;
    expected_state->memory[0x10ac] = 0xff;
    expected_state->memory[0x10ad] = 0x3c;
    expected_state->memory[0x10ae] = 0x0b;
    expected_state->memory[0x10af] = 0xff;
    expected_state->h = 0x0d;
    expected_state->l = 0xf0;

    emulate8080(state);
    if (state->memory[0x10ac] != expected_state->memory[0x10ac]) return FAIL;
    if (state->memory[0x10ad] != expected_state->memory[0x10ad]) return FAIL;
    if (state->memory[0x10ae] != expected_state->memory[0x10ae]) return FAIL;
    if (state->memory[0x10af] != expected_state->memory[0x10af]) return FAIL;
    return state_compare(state, expected_state);
}

int main(int argc, char *argv[])
{
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;
    // clang-format off
    switch (strtol(argv[1], NULL, 16))
    {
        case XCHG: result = test_XCHG(state, expected_state); break;
        case XTHL: result = test_XTHL(state, expected_state); break;
        default: result = FAIL; // Test failed due to incorrect test parameter
    }
    // clang-format on

    Free8080(state);
    Free8080(expected_state);

    return result;
}