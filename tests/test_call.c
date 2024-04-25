#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_CALL(State *state, State *expected_state)
{
    state->memory[0] = 0xcd; // CALL 0x5511
    state->memory[1] = 0x11; // 0x5511 stored in little-endian
    state->memory[2] = 0x55;
    state->sp = 0xcccf;

    // Set up the expected register states
    expected_state->pc = 0x5511;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;

    emulate8080(state);
    return state_compare(state, expected_state) == 1;
}

int test_CALL_RET(State *state, State *expected_state)
{
    /*** This function assumes that RET and DAD B are working. ***/
    state->memory[0] = 0xcd; // CALL 0x5511
    state->memory[1] = 0x11;
    state->memory[2] = 0x55;
    state->sp = 0xcccf;
    state->memory[0x5511] = 0x09; // DAD B
    state->memory[0x5512] = 0xc9; // RET
    state->h = 0xa1;
    state->l = 0x7b;
    state->b = 0x33;
    state->c = 0x9f;
    state->conditions.carry = 0;

    // Set up the expected register states just after CALL
    expected_state->pc = 0x5511;
    expected_state->memory[0xccce] = 0x55;
    expected_state->memory[0xcccd] = 0x11;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;
    expected_state->h = 0xa1;
    expected_state->l = 0x7b;
    expected_state->b = 0x33;
    expected_state->c = 0x9f;
    expected_state->conditions.carry = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states just after DAD B
    expected_state->pc = 0x5512;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;
    expected_state->h = 0xd5;
    expected_state->l = 0x1a;
    expected_state->b = 0x33;
    expected_state->c = 0x9f;
    expected_state->conditions.carry = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states just RET
    expected_state->pc = 3;
    expected_state->sp = 0xcccf;
    expected_state->h = 0xd5;
    expected_state->l = 0x1a;
    expected_state->b = 0x33;
    expected_state->c = 0x9f;
    expected_state->conditions.carry = 0;
    emulate8080(state); // runs RET
    if (state_compare(state, expected_state) == 1) return 1;

    return 0;
}

/* Tests for loading values into registers
 * Select a test by passing the opcode value as the first argument
 */
int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;
    // clang-format off
    switch (strtol(argv[1], NULL, 16))
    {
        case 0xcd:
        {
            int c1 = test_CALL(state, expected_state);
            state = Init8080();
            expected_state = Init8080();
            int c2 = test_CALL_RET(state, expected_state);
            result = c1 | c2;
        }
        break;
        default: return 1; // Test failed due to incorrect test parameter
    }
    // clang-format on

    // Clean up the state memory
    free(state->memory);
    free(expected_state->memory);
    free(state);
    free(expected_state);

    return result;
}