#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_POP_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = POP_B;
    state->b = 0xff;
    state->c = 0xff;
    state->sp = 0x1508;
    state->memory[0x1507] = 0xff;
    state->memory[0x1508] = 0x33;
    state->memory[0x1509] = 0x0b;
    state->memory[0x150A] = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->b = 0x0b;
    expected_state->c = 0x33;
    expected_state->sp = 0x150a;
    expected_state->memory[0x1507] = 0xff;
    expected_state->memory[0x1508] = 0x33;
    expected_state->memory[0x1509] = 0x0b;
    expected_state->memory[0x150A] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x1507] != expected_state->memory[0x1507]) return FAIL;
    if (state->memory[0x1508] != expected_state->memory[0x1508]) return FAIL;
    if (state->memory[0x1509] != expected_state->memory[0x1509]) return FAIL;
    if (state->memory[0x150a] != expected_state->memory[0x150a]) return FAIL;
    return PASS;
}

int test_PUSH_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = PUSH_B;
    state->b = 0x6a;
    state->c = 0x30;
    state->sp = 0x13a6;
    state->memory[0x13a3] = 0xff;
    state->memory[0x13a4] = 0xff;
    state->memory[0x13a5] = 0xff;
    state->memory[0x13a6] = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->b = 0x6a;
    expected_state->c = 0x30;
    expected_state->sp = 0x13a4;
    expected_state->memory[0x13a3] = 0xff;
    expected_state->memory[0x13a4] = 0x30;
    expected_state->memory[0x13a5] = 0x6a;
    expected_state->memory[0x13a6] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x13a3] != expected_state->memory[0x13a3]) return FAIL;
    if (state->memory[0x13a4] != expected_state->memory[0x13a4]) return FAIL;
    if (state->memory[0x13a5] != expected_state->memory[0x13a5]) return FAIL;
    if (state->memory[0x13a6] != expected_state->memory[0x13a6]) return FAIL;
    return PASS;
}

int test_POP_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = POP_D;
    state->d = 0xff;
    state->e = 0xff;
    state->sp = 0x1508;
    state->memory[0x1507] = 0xff;
    state->memory[0x1508] = 0x33;
    state->memory[0x1509] = 0x0b;
    state->memory[0x150A] = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0x0b;
    expected_state->e = 0x33;
    expected_state->sp = 0x150a;
    expected_state->memory[0x1507] = 0xff;
    expected_state->memory[0x1508] = 0x33;
    expected_state->memory[0x1509] = 0x0b;
    expected_state->memory[0x150A] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x1507] != expected_state->memory[0x1507]) return FAIL;
    if (state->memory[0x1508] != expected_state->memory[0x1508]) return FAIL;
    if (state->memory[0x1509] != expected_state->memory[0x1509]) return FAIL;
    if (state->memory[0x150a] != expected_state->memory[0x150a]) return FAIL;
    return PASS;
}

int test_PUSH_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = PUSH_D;
    state->d = 0x6a;
    state->e = 0x30;
    state->sp = 0x13a6;
    state->memory[0x13a3] = 0xff;
    state->memory[0x13a4] = 0xff;
    state->memory[0x13a5] = 0xff;
    state->memory[0x13a6] = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0x6a;
    expected_state->e = 0x30;
    expected_state->sp = 0x13a4;
    expected_state->memory[0x13a3] = 0xff;
    expected_state->memory[0x13a4] = 0x30;
    expected_state->memory[0x13a5] = 0x6a;
    expected_state->memory[0x13a6] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x13a3] != expected_state->memory[0x13a3]) return FAIL;
    if (state->memory[0x13a4] != expected_state->memory[0x13a4]) return FAIL;
    if (state->memory[0x13a5] != expected_state->memory[0x13a5]) return FAIL;
    if (state->memory[0x13a6] != expected_state->memory[0x13a6]) return FAIL;
    return PASS;
}

int test_POP_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = POP_H;
    state->h = 0xff;
    state->l = 0xff;
    state->sp = 0x1508;
    state->memory[0x1507] = 0xff;
    state->memory[0x1508] = 0x33;
    state->memory[0x1509] = 0x0b;
    state->memory[0x150A] = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x0b;
    expected_state->l = 0x33;
    expected_state->sp = 0x150a;
    expected_state->memory[0x1507] = 0xff;
    expected_state->memory[0x1508] = 0x33;
    expected_state->memory[0x1509] = 0x0b;
    expected_state->memory[0x150A] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x1507] != expected_state->memory[0x1507]) return FAIL;
    if (state->memory[0x1508] != expected_state->memory[0x1508]) return FAIL;
    if (state->memory[0x1509] != expected_state->memory[0x1509]) return FAIL;
    if (state->memory[0x150a] != expected_state->memory[0x150a]) return FAIL;
    return PASS;
}

int test_PUSH_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 4 of the 8080 Programmers Manual.
    state->memory[0] = PUSH_H;
    state->h = 0x6a;
    state->l = 0x30;
    state->sp = 0x13a6;
    state->memory[0x13a3] = 0xff;
    state->memory[0x13a4] = 0xff;
    state->memory[0x13a5] = 0xff;
    state->memory[0x13a6] = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x6a;
    expected_state->l = 0x30;
    expected_state->sp = 0x13a4;
    expected_state->memory[0x13a3] = 0xff;
    expected_state->memory[0x13a4] = 0x30;
    expected_state->memory[0x13a5] = 0x6a;
    expected_state->memory[0x13a6] = 0xff;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x13a3] != expected_state->memory[0x13a3]) return FAIL;
    if (state->memory[0x13a4] != expected_state->memory[0x13a4]) return FAIL;
    if (state->memory[0x13a5] != expected_state->memory[0x13a5]) return FAIL;
    if (state->memory[0x13a6] != expected_state->memory[0x13a6]) return FAIL;
    return PASS;
}

int test_POP_PSW(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 23 of the 8080 Programmers Manual.
    state->memory[0] = POP_PSW;
    state->a = 0x00;
    state->sp = 0x2c00;
    state->memory[0x2c00] = 0xc3;
    state->memory[0x2c01] = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0xff;
    expected_state->sp = 0x2c02;
    expected_state->memory[0x2c00] = 0xc3;
    expected_state->memory[0x2c01] = 0xff;
    // below is equivalent to 0xc3
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 1;
    expected_state->conditions.pad5 = 0; // always 0, per manual
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.pad3 = 0; // always 0, per manual
    expected_state->conditions.parity = 0;
    expected_state->conditions.pad1 = 1; // always 1, per manual
    expected_state->conditions.carry = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x2c00] != expected_state->memory[0x2c00]) return FAIL;
    if (state->memory[0x2c01] != expected_state->memory[0x2c01]) return FAIL;
    return PASS;
}

int test_PUSH_PSW(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    // Example from pg 23 of the 8080 Programmers Manual.
    state->memory[0] = PUSH_PSW;
    state->memory[0x5028] = 0x00;
    state->memory[0x5029] = 0x00;
    state->a = 0x1f;
    state->sp = 0x502a;
    state->conditions.sign = 0;
    state->conditions.zero = 1;
    state->conditions.pad5 = 0;
    state->conditions.aux_carry = 0;
    state->conditions.pad3 = 0;
    state->conditions.parity = 1;
    state->conditions.pad1 = 0;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x1f;
    expected_state->sp = 0x5028;
    expected_state->memory[0x5028] = 0x47; // pad1 is set to 1 in memory on PUSH PSW.
    expected_state->memory[0x5029] = 0x1f;
    expected_state->memory[0x5028] = 0x47; // equivalent to the flag's below but with pad1 = 1.

    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.pad5 = 0; // always 0, per manual
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.pad3 = 0; // always 0, per manual
    expected_state->conditions.parity = 1;
    expected_state->conditions.pad1 = 0; // set as 1 in memory, but not updated in the flag.
    expected_state->conditions.carry = 1;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    if (state->memory[0x5029] != expected_state->memory[0x5029]) return FAIL;
    if (state->memory[0x5028] != expected_state->memory[0x5028]) return FAIL;
    return PASS;
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
        case POP_B: result = test_POP_B(state, expected_state); break;
        case PUSH_B: result = test_PUSH_B(state, expected_state); break;
        case POP_D: result = test_POP_D(state, expected_state); break;
        case PUSH_D: result = test_PUSH_D(state, expected_state); break;
        case POP_H: result = test_POP_H(state, expected_state); break;
        case PUSH_H: result = test_PUSH_H(state, expected_state); break;
        case POP_PSW: result = test_POP_PSW(state, expected_state); break;
        case PUSH_PSW: result = test_PUSH_PSW(state, expected_state); break;
        default: result = FAIL; // Test failed due to incorrect test parameter
    }
    // clang-format on

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}