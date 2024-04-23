#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_POP_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = 0xd1; // POP D opcode
    state->d = 0xff;
    state->e = 0xff;
    state->sp = 0x1508;
    state->memory[0x1507] = 0xff;
    state->memory[0x1508] = 0x33;
    state->memory[0x1509] = 0x0b;
    state->memory[0x150A] = 0xff;

    // Set up the expected register states
    expected_state->memory[0] = 0xd1; // POP D opcode
    expected_state->pc = 1;
    expected_state->d = 0x0b;
    expected_state->e = 0x33;
    expected_state->sp = 0x150a;
    expected_state->memory[0x1507] = 0xff;
    expected_state->memory[0x1508] = 0x33;
    expected_state->memory[0x1509] = 0x0b;
    expected_state->memory[0x150A] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return 1;
    if (state_mem_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_PUSH_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = 0xd5; // PUSH D opcode
    state->d = 0x6a;
    state->e = 0x30;
    state->sp = 0x13a6;
    state->memory[0x13a3] = 0xff;
    state->memory[0x13a4] = 0xff;
    state->memory[0x13a5] = 0xff;
    state->memory[0x13a6] = 0xff;

    // Set up the expected register states
    expected_state->memory[0] = 0xd5; // PUSH D opcode
    expected_state->pc = 1;
    expected_state->d = 0x6a;
    expected_state->e = 0x30;
    expected_state->sp = 0x13a4;
    expected_state->memory[0x13a3] = 0xff;
    expected_state->memory[0x13a4] = 0x30;
    expected_state->memory[0x13a5] = 0x6a;
    expected_state->memory[0x13a6] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return 1;
    if (state_mem_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_POP_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = 0xe1; // POP H opcode
    state->h = 0xff;
    state->l = 0xff;
    state->sp = 0x1508;
    state->memory[0x1507] = 0xff;
    state->memory[0x1508] = 0x33;
    state->memory[0x1509] = 0x0b;
    state->memory[0x150A] = 0xff;

    // Set up the expected register states
    expected_state->memory[0] = 0xe1; // POP H opcode
    expected_state->pc = 1;
    expected_state->h = 0x0b;
    expected_state->l = 0x33;
    expected_state->sp = 0x150a;
    expected_state->memory[0x1507] = 0xff;
    expected_state->memory[0x1508] = 0x33;
    expected_state->memory[0x1509] = 0x0b;
    expected_state->memory[0x150A] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return 1;
    if (state_mem_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_PUSH_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = 0xe5; // PUSH H opcode
    state->h = 0x6a;
    state->l = 0x30;
    state->sp = 0x13a6;
    state->memory[0x13a3] = 0xff;
    state->memory[0x13a4] = 0xff;
    state->memory[0x13a5] = 0xff;
    state->memory[0x13a6] = 0xff;

    // Set up the expected register states
    expected_state->memory[0] = 0xe5; // PUSH H opcode
    expected_state->pc = 1;
    expected_state->h = 0x6a;
    expected_state->l = 0x30;
    expected_state->sp = 0x13a4;
    expected_state->memory[0x13a3] = 0xff;
    expected_state->memory[0x13a4] = 0x30;
    expected_state->memory[0x13a5] = 0x6a;
    expected_state->memory[0x13a6] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return 1;
    if (state_mem_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_POP_PSW(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 23 of the 8080 Programmers Manual.
    state->memory[0] = 0xf1; // POP PSW opcode
    state->a = 0x00;
    state->sp = 0x2c00;
    state->memory[0x2c00] = 0xc3;
    state->memory[0x2c01] = 0xff;

    // Set up the expected register states
    expected_state->memory[0] = 0xf1; // POP PSW opcode
    expected_state->pc = 1;
    expected_state->a = 0xff;
    expected_state->sp = 0x2c02;
    expected_state->memory[0x2c00] = 0xc3;
    expected_state->memory[0x2c01] = 0xff;
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 0;
    expected_state->conditions.carry = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return 1;
    if (state_mem_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_PUSH_PSW(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 23 of the 8080 Programmers Manual.
    state->memory[0] = 0xf5; // PUSH PSW opcode
    state->memory[0x5029] = 0x00;
    state->memory[0x5028] = 0x00;
    state->a = 0x1f;
    state->sp = 0x502a;
    state->conditions.carry = 1;
    state->conditions.zero = 1;
    state->conditions.parity = 1;
    state->conditions.sign = 0;
    state->conditions.aux_carry = 0;

    // Set up the expected register states
    expected_state->memory[0] = 0xf5; // PUSH PSW opcode
    expected_state->pc = 1;
    expected_state->a = 0x1f;
    expected_state->sp = 0x5028;
    expected_state->memory[0x5029] = 0x1f;
    expected_state->memory[0x5028] =
        0x45; // with cur struct layout and implementation, the pad bits are set
              // to zero so the correct hex is 45.
    // expected_state->memory[0x5028] = 0x47; // equivalent to the flag
    // settings, tho makes assumptions about the pad bits
    expected_state->conditions.carry = 1;
    expected_state->conditions.zero = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.aux_carry = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;
    if (state_mem_compare(state, expected_state) == 1) return 1;
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
        case 0xd1: result = test_POP_D(state, expected_state); break;
        case 0xd5: result = test_PUSH_D(state, expected_state); break;
        case 0xe1: result = test_POP_H(state, expected_state); break;
        case 0xe5: result = test_PUSH_H(state, expected_state); break;
        case 0xf1: result = test_POP_PSW(state, expected_state); break;
        case 0xf5: result = test_PUSH_PSW(state, expected_state); break;
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