#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_subtract_helper(State *state, State *expected_state)
{
    // 10 - 1
    uint8_t val = 10;
    uint8_t res = subtract_8b(state, val, 1);
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    if (res != 9) return FAIL;
    if (state_compare(state, expected_state) != PASS) return FAIL;

    // 0 - 1
    val = 0x00;
    res = subtract_8b(state, val, 1);
    expected_state->conditions.zero = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 1;
    expected_state->conditions.carry = 1;

    if (res != 0xff) return FAIL;
    if (state_compare(state, expected_state) != PASS) return FAIL;

    // Test from page 18 manual
    val = 0x3E;
    res = subtract_8b(state, val, 0x3E);
    expected_state->conditions.zero = 1;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;

    if (res != 0x0) return FAIL;
    if (state_compare(state, expected_state) != PASS) return FAIL;

    return PASS;
}

int test_DCR_A(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_A;
    state->a = 0xab;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0xaa;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_B;
    state->memory[1] = DCR_B;
    state->b = 0x01;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->b = 0x00;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) != PASS) return FAIL;

    // Set up the expected register states
    expected_state->pc = 2;
    expected_state->b = 0xff;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_C;
    state->c = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->c = 0xfe;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_D;
    state->d = 0x80;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0x7f;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_E(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_E;
    state->e = 0x62;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->e = 0x61;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_H;
    state->h = 0x99;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x98;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_L(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_L;
    state->l = 0x02;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->l = 0x01;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCR_M(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCR_M;
    state->memory[0x1234] = 0x56;
    state->h = 0x12;
    state->l = 0x34;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x12;
    expected_state->l = 0x34;
    expected_state->memory[0x1234] = 0x55;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return FAIL;
    if (state->memory[0x1234] != expected_state->memory[0x1234]) return FAIL;

    // Load the instruction and set up the memory
    // Example from the book
    state->memory[0] = DCR_M;
    state->pc = 0;
    state->memory[0x3A7C] = 0x40;
    state->h = 0x3A;
    state->l = 0x7C;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x3A;
    expected_state->l = 0x7C;
    expected_state->memory[0x3A7C] = 0x3F;
    expected_state->conditions.aux_carry = 1; // flags not shown in book...
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return FAIL;
    if (state->memory[0x1234] != expected_state->memory[0x1234]) return FAIL;

    return PASS;
}

int test_DCX_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCX_B;
    state->b = 0x00;
    state->c = 0x00;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->b = 0xff;
    expected_state->c = 0xff;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCX_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCX_D;
    state->d = 0xff;
    state->e = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0xff;
    expected_state->e = 0xfe;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCX_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCX_H;
    state->h = 0x01;
    state->l = 0x00;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x00;
    expected_state->l = 0xff;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DCX_SP(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DCX_SP;
    state->sp = 0x5678;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->sp = 0x5677;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_A(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_A;
    state->a = 0x3e;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_B;
    state->a = 0x3e; // Set A register
    state->b = 0x3c; // Set B register

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 2; // Expected result of A - B
    expected_state->b = 0x3c;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_C;
    state->a = 0x3e;
    state->c = 0x3c;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 2;
    expected_state->c = 0x3c;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_D;
    state->a = 0x3e;
    state->d = 0x3c;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 2;
    expected_state->d = 0x3c;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_E(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_E;
    state->a = 0x3e;
    state->e = 0x3c;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 2;
    expected_state->e = 0x3c;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_H;
    state->a = 0x3e;
    state->h = 0x3c;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 2;
    expected_state->h = 0x3c;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_L(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_L;
    state->a = 0x3e;
    state->l = 0x3c;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 2;
    expected_state->l = 0x3c;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SUB_M(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SUB_M;
    state->a = 0x0a;
    state->h = 0x20;
    state->l = 0x05;
    state->memory[0x2005] = 0x03;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x07;
    expected_state->h = 0x20;
    expected_state->l = 0x05;
    expected_state->memory[0x2005] = 0x03;

    // Set up flags
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_SBB_A(State *state, State *expected_state)
{
    // test carry = 0. A - A = 0.
    state->memory[0] = SBB_A;
    state->a = 0x3e;
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 1;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // test carry = 1. A - (A + 1) = -1.
    state->pc = 0; // move back to operation code
    state->a = 0x3e;
    state->conditions.carry = 1;

    expected_state->pc = 1;
    expected_state->a = -1;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 1;
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBB_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SBB_B;
    state->a = 0x0a;
    state->b = 0x03;

    // Set carry flag to 1
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x06;
    expected_state->b = 0x03;

    // Expected flags
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry is 0.
    state->pc = 0;
    state->memory[0] = SBB_B;
    state->a = 0x3e; // Set A register
    state->b = 0x3c; // Set B register
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 2; // Expected result of A - B
    expected_state->b = 0x3c;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBB_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SBB_C;
    state->a = 0x0a;
    state->c = 0x03;

    // Set carry flag to 1
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x06;
    expected_state->c = 0x03;

    // Expected flags
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry is 0.
    state->pc = 0;
    state->memory[0] = SBB_C;
    state->a = 0x3e; // Set A register
    state->c = 0x3c; // Set B register
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 2; // Expected result of A - B
    expected_state->c = 0x3c;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBB_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SBB_D;
    state->a = 0x0a;
    state->d = 0x03;

    // Set carry flag to 1
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x06;
    expected_state->d = 0x03;

    // Expected flags
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry is 0.
    state->pc = 0;
    state->memory[0] = SBB_D;
    state->a = 0x3e; // Set A register
    state->d = 0x3c; // Set B register
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 2; // Expected result of A - B
    expected_state->d = 0x3c;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBB_E(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SBB_E;
    state->a = 0x0a;
    state->e = 0x03;

    // Set carry flag to 1
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x06;
    expected_state->e = 0x03;

    // Expected flags
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry is 0.
    state->pc = 0;
    state->memory[0] = SBB_E;
    state->a = 0x3e; // Set A register
    state->e = 0x3c; // Set B register
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 2; // Expected result of A - B
    expected_state->e = 0x3c;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBB_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SBB_H;
    state->a = 0x0a;
    state->h = 0x03;

    // Set carry flag to 1
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x06;
    expected_state->h = 0x03;

    // Expected flags
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry is 0.
    state->pc = 0;
    state->memory[0] = SBB_H;
    state->a = 0x3e; // Set A register
    state->h = 0x3c; // Set B register
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 2; // Expected result of A - B
    expected_state->h = 0x3c;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBB_L(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SBB_L;
    state->a = 0x0a;
    state->l = 0x03;

    // Set carry flag to 1
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x06;
    expected_state->l = 0x03;

    // Expected flags
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry is 0.
    state->pc = 0;
    state->memory[0] = SBB_L;
    state->a = 0x3e; // Set A register
    state->l = 0x3c; // Set B register
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 2; // Expected result of A - B
    expected_state->l = 0x3c;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBB_M(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = SBB_M;
    state->a = 0x0A; // Initial accumulator value
    state->h = 0x20; // Set HL address
    state->l = 0x05;
    state->memory[0x2005] = 0x03; // Value at HL address

    // Set carry flag to 1
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x06; // Expected accumulator value after subtraction
    expected_state->h = 0x20; // HL should not be affected
    expected_state->l = 0x05;
    expected_state->memory[0x2005] = 0x03;

    // Expected flags
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry = 0.
    state->pc = 0;
    state->memory[0] = SBB_M;
    state->a = 0x0a;
    state->h = 0x20;
    state->l = 0x05;
    state->memory[0x2005] = 0x03;
    state->conditions.carry = 0;

    expected_state->pc = 1;
    expected_state->a = 0x07;
    expected_state->h = 0x20;
    expected_state->l = 0x05;
    expected_state->memory[0x2005] = 0x03;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.parity = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SBI(State *state, State *expected_state)
{
    // Test when carry = 0.
    state->memory[0] = SBI;
    state->memory[1] = 0x01;
    state->a = 0x00;
    state->conditions.carry = 0;

    expected_state->pc = 2;
    expected_state->a = 0xff;

    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == FAIL) return FAIL;

    // Test when carry = 1.
    state->pc = 0;
    state->memory[0] = SBI;
    state->memory[1] = 0x01;
    state->a = 0x00;
    state->conditions.carry = 1;

    expected_state->pc = 2;
    expected_state->a = 0xfe;

    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);
    if (state_compare(state, expected_state) == FAIL) return FAIL;
    return PASS;
}

int test_SUI(State *state, State *expected_state)
{
    state->memory[0] = SUI;
    state->memory[1] = 0x01;
    state->a = 0x00;
    state->conditions.carry = 1;

    expected_state->pc = 2;
    expected_state->a = 0xff;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

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
    case DCR_A: result = test_DCR_A(state, expected_state); break;
    case DCR_B: result = test_DCR_B(state, expected_state); break;
    case DCR_C: result = test_DCR_C(state, expected_state); break;
    case DCR_D: result = test_DCR_D(state, expected_state); break;
    case DCR_E: result = test_DCR_E(state, expected_state); break;
    case DCR_H: result = test_DCR_H(state, expected_state); break;
    case DCR_L: result = test_DCR_L(state, expected_state); break;
    case DCR_M: result = test_DCR_M(state, expected_state); break;
    case DCX_B: result = test_DCX_B(state, expected_state); break;
    case DCX_D: result = test_DCX_D(state, expected_state); break;
    case DCX_H: result = test_DCX_H(state, expected_state); break;
    case DCX_SP: result = test_DCX_SP(state, expected_state); break;
    case SUB_A: result = test_SUB_A(state, expected_state); break;
    case SUB_B: result = test_SUB_B(state, expected_state); break;
    case SUB_C: result = test_SUB_C(state, expected_state); break;
    case SUB_D: result = test_SUB_D(state, expected_state); break;
    case SUB_E: result = test_SUB_E(state, expected_state); break;
    case SUB_H: result = test_SUB_H(state, expected_state); break;
    case SUB_L: result = test_SUB_L(state, expected_state); break;
    case SUB_M: result = test_SUB_M(state, expected_state); break;
    case SBB_A: result = test_SBB_A(state, expected_state); break;
    case SBB_B: result = test_SBB_B(state, expected_state); break;
    case SBB_C: result = test_SBB_C(state, expected_state); break;
    case SBB_D: result = test_SBB_D(state, expected_state); break;
    case SBB_E: result = test_SBB_E(state, expected_state); break;
    case SBB_H: result = test_SBB_H(state, expected_state); break;
    case SBB_L: result = test_SBB_L(state, expected_state); break;
    case SBB_M: result = test_SBB_M(state, expected_state); break;
    case SBI: result = test_SBI(state, expected_state); break;
    case SUI: result = test_SUI(state, expected_state); break;
    case 0xFFFF: result = test_subtract_helper(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }
    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}
