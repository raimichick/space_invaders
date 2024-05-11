#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_SHLD(State *state, State *expected_state)
{
    state->memory[0] = SHLD;
    state->l = 0x33;
    state->h = 0x22;
    state->memory[1] = 0x5b;
    state->memory[2] = 0x02;
    state->memory[0x025b] = 0x00;
    state->memory[0x025c] = 0x00;

    expected_state->pc = 3;
    expected_state->l = 0x33;
    expected_state->h = 0x22;
    expected_state->memory[0x025b] = 0x33;
    expected_state->memory[0x025c] = 0x22;

    emulate8080(state);

    if (state->memory[0x025b] != expected_state->memory[0x025b]) return FAIL;
    if (state->memory[0x025c] != expected_state->memory[0x025c]) return FAIL;
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SPHL(State *state, State *expected_state)
{
    state->memory[0] = SPHL;
    state->h = 0x50;
    state->l = 0x6c;
    state->sp = 0xAAAA;

    expected_state->pc = 1;
    expected_state->h = 0x50;
    expected_state->l = 0x6c;
    expected_state->sp = 0x506c;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_STA(State *state, State *expected_state)
{
    state->memory[0] = STA; // STA 0x05B3
    state->memory[1] = 0xB3;
    state->memory[2] = 0x05;
    state->a = 0x11;
    state->memory[0x05B3] = 0xf6;

    expected_state->pc = 3;
    expected_state->a = 0x11;
    expected_state->memory[0x05B3] = 0x11;

    emulate8080(state);

    if (state->memory[0x05B3] != expected_state->memory[0x05B3]) return FAIL;
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_STAX_B(State *state, State *expected_state)
{
    state->memory[0] = STAX_B;
    state->a = 0x11;
    state->b = 0x3f;
    state->c = 0x16;
    state->memory[0x3f16] = 0xf6;

    expected_state->pc = 1;
    expected_state->a = 0x11;
    expected_state->b = 0x3f;
    expected_state->c = 0x16;
    expected_state->memory[0x3f16] = 0x11;

    emulate8080(state);

    if (state->memory[0x3f16] != expected_state->memory[0x3f16]) return FAIL;
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_STAX_D(State *state, State *expected_state)
{
    state->memory[0] = STAX_D;
    state->a = 0x11;
    state->d = 0x3f;
    state->e = 0x16;
    state->memory[0x3f16] = 0xf6;

    expected_state->pc = 1;
    expected_state->a = 0x11;
    expected_state->d = 0x3f;
    expected_state->e = 0x16;
    expected_state->memory[0x3f16] = 0x11;

    emulate8080(state);

    if (state->memory[0x3f16] != expected_state->memory[0x3f16]) return FAIL;
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case SHLD: result = test_SHLD(state, expected_state); break;
    case SPHL: result = test_SPHL(state, expected_state); break;
    case STA: result = test_STA(state, expected_state); break;
    case STAX_B: result = test_STAX_B(state, expected_state); break;
    case STAX_D: result = test_STAX_D(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}