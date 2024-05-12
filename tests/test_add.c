#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_ADD_A(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_A;
    state->a = 0x0f;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x1e;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADD_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_B;
    state->a = 0x00;
    state->b = 0x00;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x00;
    expected_state->b = 0x00;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADD_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_C;
    state->a = 0xff;
    state->c = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0xfe;
    expected_state->c = 0xff;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADD_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_D;
    state->a = 0x0c;
    state->d = 0x04;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x10;
    expected_state->d = 0x04;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADD_E(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_E;
    state->a = 0xa6;
    state->e = 0x5a;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x00;
    expected_state->e = 0x5a;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADD_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_H;
    state->a = 0x12;
    state->h = 0x34;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x46;
    expected_state->h = 0x34;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADD_L(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_L;
    state->a = 0xc6;
    state->l = 0xc6;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x8c;
    expected_state->l = 0xc6;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADD_M(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADD_M;
    state->memory[0xcdab] = 0x91;
    state->a = 0xa6;
    state->h = 0xcd;
    state->l = 0xab;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x37;
    expected_state->h = 0xcd;
    expected_state->l = 0xab;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADI_D8(State *state, State *expected_state)
{
    // Set state
    // Example from page 27 of the 8080 Programmers Manual
    state->memory[0] = 0xc6;
    state->memory[1] = 66;
    state->a = 20;
    state->conditions.zero = 1;
    state->conditions.sign = 1;
    state->conditions.aux_carry = 1;
    state->conditions.carry = 1;

    // Set expected state
    expected_state->a = 86;
    expected_state->pc = 2;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_A(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_A;
    state->a = 0x0f;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x1f;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_B;
    state->a = 0x00;
    state->b = 0x00;
    state->conditions.carry = 0;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x00;
    expected_state->b = 0x00;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_C;
    state->a = 0xff;
    state->c = 0xff;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0xff;
    expected_state->c = 0xff;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_D;
    state->a = 0x0c;
    state->d = 0x04;
    state->conditions.carry = 0;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x10;
    expected_state->d = 0x04;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_E(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_E;
    state->a = 0xa6;
    state->e = 0x5a;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x01;
    expected_state->e = 0x5a;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_H;
    state->a = 0x12;
    state->h = 0x34;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x47;
    expected_state->h = 0x34;
    expected_state->conditions.carry = 0;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_L(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_L;
    state->a = 0xc6;
    state->l = 0xc6;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x8d;
    expected_state->l = 0xc6;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ADC_M(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ADC_M;
    state->memory[0xcdab] = 0x91;
    state->a = 0xa6;
    state->h = 0xcd;
    state->l = 0xab;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x38;
    expected_state->h = 0xcd;
    expected_state->l = 0xab;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_ACI(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = ACI;
    state->memory[1] = 0xf2;
    state->a = 0xc6;
    state->conditions.carry = 1;

    // Set up the expected register states
    expected_state->pc = 2;
    expected_state->a = 0xb9;
    expected_state->conditions.carry = 1;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DAD_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DAD_B;
    state->h = 0x89;
    state->l = 0xab;
    state->b = 0xcd;
    state->c = 0xef;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x57;
    expected_state->l = 0x9a;
    expected_state->b = 0xcd;
    expected_state->c = 0xef;
    expected_state->conditions.carry = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DAD_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DAD_D;
    state->h = 0x12;
    state->l = 0x34;
    state->d = 0x56;
    state->e = 0x78;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x68;
    expected_state->l = 0xac;
    expected_state->d = 0x56;
    expected_state->e = 0x78;
    expected_state->conditions.carry = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DAD_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DAD_H;
    state->h = 0x89;
    state->l = 0xab;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x13;
    expected_state->l = 0x56;
    expected_state->conditions.carry = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_DAD_SP(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = DAD_SP;
    state->h = 0x12;
    state->l = 0x34;
    state->sp = 0xffff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x12;
    expected_state->l = 0x33;
    expected_state->sp = 0xffff;
    expected_state->conditions.carry = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_A(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_A;
    state->a = 0x7f;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->a = 0x80;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_B;
    state->b = 0xff;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->b = 0x00;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.zero = 1;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_C(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_C;
    state->c = 0x00;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->c = 0x01;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_D;
    state->d = 0xaa;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0xab;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_E(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_E;
    state->e = 0x0f;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->e = 0x10;
    expected_state->conditions.aux_carry = 1;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_H(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_H;
    state->h = 0x10;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x11;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_L(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_L;
    state->l = 0x45;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->l = 0x46;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 0;
    expected_state->conditions.parity = 0;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INR_M(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INR_M;
    state->memory[0x9876] = 0xd3;
    state->h = 0x98;
    state->l = 0x76;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->memory[0x9876] = 0xd4;
    expected_state->h = 0x98;
    expected_state->l = 0x76;
    expected_state->conditions.aux_carry = 0;
    expected_state->conditions.zero = 0;
    expected_state->conditions.sign = 1;
    expected_state->conditions.parity = 1;

    emulate8080(state);

    if (state_compare(state, expected_state) == 1) return FAIL;
    if (state->memory[0x9876] != expected_state->memory[0x9876]) return FAIL;

    return PASS;
}

int test_INX_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = INX_D;
    state->d = 0x12;
    state->e = 0x34;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0x12;
    expected_state->e = 0x35;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INX_B(State *state, State *expected_state)
{
    // Load the instruction and set up the registers
    state->memory[0] = INX_B;
    state->b = 0x05;
    state->c = 0x20;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->b = 0x05; // B register should remain the same
    expected_state->c = 0x21; // C register should be incremented by 1

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INX_H(State *state, State *expected_state)
{
    // Load the instruction and set up the registers
    state->memory[0] = INX_H;
    state->h = 0x05;
    state->l = 0x20;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->h = 0x05; // H register should remain the same
    expected_state->l = 0x21; // L register should be incremented by 1

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_INX_SP(State *state, State *expected_state)
{
    // Load the instruction
    state->memory[0] = INX_SP;

    // Set up the initial SP value
    state->sp = 0x1000;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->sp = 0x1001; // Expected SP after incrementing

    emulate8080(state);

    return state_compare(state, expected_state);
}

/* Tests for various add instructions
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case ADD_A: result = test_ADD_A(state, expected_state); break;
    case ADD_B: result = test_ADD_B(state, expected_state); break;
    case ADD_C: result = test_ADD_C(state, expected_state); break;
    case ADD_D: result = test_ADD_D(state, expected_state); break;
    case ADD_E: result = test_ADD_E(state, expected_state); break;
    case ADD_H: result = test_ADD_H(state, expected_state); break;
    case ADD_L: result = test_ADD_L(state, expected_state); break;
    case ADD_M: result = test_ADD_M(state, expected_state); break;
    case ADI: result = test_ADI_D8(state, expected_state); break;
    case ADC_A: result = test_ADC_A(state, expected_state); break;
    case ADC_B: result = test_ADC_B(state, expected_state); break;
    case ADC_C: result = test_ADC_C(state, expected_state); break;
    case ADC_D: result = test_ADC_D(state, expected_state); break;
    case ADC_E: result = test_ADC_E(state, expected_state); break;
    case ADC_H: result = test_ADC_H(state, expected_state); break;
    case ADC_L: result = test_ADC_L(state, expected_state); break;
    case ADC_M: result = test_ADC_M(state, expected_state); break;
    case ACI: result = test_ACI(state, expected_state); break;
    case DAD_B: result = test_DAD_B(state, expected_state); break;
    case DAD_D: result = test_DAD_D(state, expected_state); break;
    case DAD_H: result = test_DAD_H(state, expected_state); break;
    case DAD_SP: result = test_DAD_SP(state, expected_state); break;
    case INR_A: result = test_INR_A(state, expected_state); break;
    case INR_B: result = test_INR_B(state, expected_state); break;
    case INR_C: result = test_INR_C(state, expected_state); break;
    case INR_D: result = test_INR_D(state, expected_state); break;
    case INR_E: result = test_INR_E(state, expected_state); break;
    case INR_H: result = test_INR_H(state, expected_state); break;
    case INR_L: result = test_INR_L(state, expected_state); break;
    case INR_M: result = test_INR_M(state, expected_state); break;
    case INX_B: result = test_INX_B(state, expected_state); break;
    case INX_D: result = test_INX_D(state, expected_state); break;
    case INX_H: result = test_INX_H(state, expected_state); break;
    case INX_SP: result = test_INX_SP(state, expected_state); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(state);
    Free8080(expected_state);

    return result;
}