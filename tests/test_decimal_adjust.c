#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdlib.h>

int test_DAA(State *state, State *expected_state)
{
    state->memory[0] = DAA;
    state->a = 0x9b;
    state->conditions.carry = 0;
    state->conditions.aux_carry = 0;

    expected_state->pc = 1;
    expected_state->a = 0x01;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 1;

    emulate8080(state);
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
    case DAA: result = test_DAA(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}