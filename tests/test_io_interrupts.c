#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
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
    expected_state->halt = 1;

    for (size_t i = 0; state->halt == 0 && i < 10; i++) emulate8080(state);

    return state_compare(state, expected_state);
}

int test_RST_NUM(State *state, State *expected_state, uint8_t rst_opcode, int pc_target)
{
    state->memory[0xFAAA] = rst_opcode;
    state->pc = 0xFAAA;
    state->sp = 0x1155;

    expected_state->pc = pc_target;
    expected_state->sp = 0x1153;
    expected_state->memory[0x1153] = 0xAA;
    expected_state->memory[0x1154] = 0xFA;

    emulate8080(state);

    if (state->memory[0x1154] != expected_state->memory[0x1154]) return FAIL;
    if (state->memory[0x1153] != expected_state->memory[0x1153]) return FAIL;
    return state_compare(state, expected_state);
}

int test_IN(State *state, State *expected_state)
{
    state->memory[0] = IN;
    state->memory[1] = 3;
    state->ports[3] = 0x11;
    state->a = 0x55;

    expected_state->pc = 2;
    expected_state->memory[1] = 3;
    expected_state->ports[3] = 0x11;
    expected_state->a = 0x11;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_OUT(State *state, State *expected_state)
{
    state->memory[0] = OUT;
    state->pc = 0;
    state->memory[1] = 3;
    state->ports[3] = 0x11;
    state->a = 0x55;

    expected_state->pc = 2;
    expected_state->memory[1] = 3;
    expected_state->ports[3] = 0x55;
    expected_state->a = 0x55;

    emulate8080(state);

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
    case RST_0: result = test_RST_NUM(state, expected_state, RST_0, 8 * 0); break;
    case RST_1: result = test_RST_NUM(state, expected_state, RST_1, 8 * 1); break;
    case RST_2: result = test_RST_NUM(state, expected_state, RST_2, 8 * 2); break;
    case RST_3: result = test_RST_NUM(state, expected_state, RST_3, 8 * 3); break;
    case RST_4: result = test_RST_NUM(state, expected_state, RST_4, 8 * 4); break;
    case RST_5: result = test_RST_NUM(state, expected_state, RST_5, 8 * 5); break;
    case RST_6: result = test_RST_NUM(state, expected_state, RST_6, 8 * 6); break;
    case RST_7: result = test_RST_NUM(state, expected_state, RST_7, 8 * 7); break;
    case IN: result = test_IN(state, expected_state); break;
    case OUT: result = test_OUT(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    Free8080(state);
    Free8080(expected_state);

    return result;
}