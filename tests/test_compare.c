#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_CPI_D8(State *state, State *expected_state)
{
    state->memory[0] = 0xfe;
    state->memory[1] = 0x40;
    state->a = 0x4a;
    state->conditions.carry = 1;
    state->conditions.aux_carry = 1;
    state->conditions.zero = 1;
    state->conditions.parity = 1;
    state->conditions.sign = 1;

    expected_state->pc = 2;
    expected_state->a = 0x4a;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;

    emulate8080(state);
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
        case 0xfe: result = test_CPI_D8(state, expected_state); break;
        default: result = FAIL; // Test failed due to incorrect test parameter
    }
    // clang-format on

    Free8080(state);
    Free8080(expected_state);

    return result;
}