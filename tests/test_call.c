#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

#define	CNZ	0xc4
#define	CZ	0xcc
#define	CALL	0xcd
#define	CNC	0xd4
#define	CC	0xdc
#define	CPO	0xe4
#define	CPE	0xec
#define	CP	0xf4
#define	CM	0xfc

int test_CALL(State *state, State *expected_state)
{
    state->memory[0] = CALL; // CALL 0x5511
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
    state->memory[0] = CALL; // CALL 0x5511
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
    expected_state->memory[0xcccd] = 0x03;
    expected_state->memory[0xccce] = 0x00;
    expected_state->sp = 0xcccd;
    expected_state->h = 0xa1;
    expected_state->l = 0x7b;
    expected_state->b = 0x33;
    expected_state->c = 0x9f;
    expected_state->conditions.carry = 0;
    emulate8080(state); // Runs Call
    if (state->memory[0xccce] != expected_state->memory[0xccce]) return 1;
    if (state->memory[0xcccd] != expected_state->memory[0xcccd]) return 1;
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
    emulate8080(state); // Runs DAD B
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

int test_CNZ(State *state, State *expected_state)
{
    /*** This function assumes that RET and MVI B are working. ***/
    // The first CNZ should be skipped.
    state->memory[0] = CNZ; // CNZ 0x5511
    state->memory[1] = 0x11;
    state->memory[2] = 0x55;
    state->conditions.zero = 1;
    expected_state->pc = 0x3;
    expected_state->conditions.zero = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // The second CNZ should execute.
    state->memory[3] = CNZ; // CNZ 0x5511
    state->memory[4] = 0x11;
    state->memory[5] = 0x55;
    state->conditions.zero = 0;
    state->sp = 0xcccf;
    state->memory[0x5511] = 0x06; // MVI B D8
    state->memory[0x5512] = 0x55; // D8 to be put in B is 0x55
    state->memory[0x5513] = 0xc9; // RET
    state->b = 0x00;

    // Set up the expected register states just after executed CNZ, before MVI B
    expected_state->pc = 0x5511;
    expected_state->memory[0xcccd] = 0x06; // return pc
    expected_state->memory[0xccce] = 0x00;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x00;
    expected_state->conditions.zero = 0;
    emulate8080(state); // Runs CNZ
    if (state->memory[0xccce] != expected_state->memory[0xccce]) return 1;
    if (state->memory[0xcccd] != expected_state->memory[0xcccd]) return 1;
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states just after MVI B, D8
    expected_state->pc = 0x5513;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x55;
    emulate8080(state); // Runs MVI B, D8
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states after RET
    expected_state->pc = 6;
    expected_state->sp = 0xcccf;
    expected_state->b = 0x55;
    expected_state->conditions.zero = 0;
    emulate8080(state); // runs RET
    if (state_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_CZ(State *state, State *expected_state)
{
    /*** This function assumes that RET and MVI B are working. ***/
    // The first CZ should be skipped.
    state->memory[0] = CZ; // CZ 0x5511
    state->memory[1] = 0x11;
    state->memory[2] = 0x55;
    state->conditions.zero = 0;
    expected_state->pc = 0x3;
    expected_state->conditions.zero = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // The second CNZ should execute.
    state->memory[3] = CZ; // CZ 0x5511
    state->memory[4] = 0x11;
    state->memory[5] = 0x55;
    state->conditions.zero = 1;
    state->sp = 0xcccf;
    state->memory[0x5511] = 0x06; // MVI B D8
    state->memory[0x5512] = 0x55; // D8 to be put in B is 0x55
    state->memory[0x5513] = 0xc9; // RET
    state->b = 0x00;

    // Set up the expected register states just after executed CZ, before MVI B
    expected_state->pc = 0x5511;
    expected_state->memory[0xcccd] = 0x06; // return pc
    expected_state->memory[0xccce] = 0x00;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x00;
    expected_state->conditions.zero = 1;
    emulate8080(state); // Runs CZ
    if (state->memory[0xccce] != expected_state->memory[0xccce]) return 1;
    if (state->memory[0xcccd] != expected_state->memory[0xcccd]) return 1;
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states just after MVI B, D8
    expected_state->pc = 0x5513;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x55;
    emulate8080(state); // Runs MVI B, D8
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states after RET
    expected_state->pc = 6;
    expected_state->sp = 0xcccf;
    expected_state->b = 0x55;
    expected_state->conditions.zero = 1;
    emulate8080(state); // runs RET
    if (state_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_CNC(State *state, State *expected_state)
{
    /*** This function assumes that RET and MVI B are working. ***/
    // The first CNC should be skipped.
    state->memory[0] = CNC; // CNC 0x5511
    state->memory[1] = 0x11;
    state->memory[2] = 0x55;
    state->conditions.carry = 1;
    expected_state->pc = 0x3;
    expected_state->conditions.carry = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // The second CNC should execute.
    state->memory[3] = CNC; // CNC 0x5511
    state->memory[4] = 0x11;
    state->memory[5] = 0x55;
    state->conditions.carry = 0;
    state->sp = 0xcccf;
    state->memory[0x5511] = 0x06; // MVI B D8
    state->memory[0x5512] = 0x55; // D8 to be put in B is 0x55
    state->memory[0x5513] = 0xc9; // RET
    state->b = 0x00;

    // Set up the expected register states just after executed CNC, before MVI B
    expected_state->pc = 0x5511;
    expected_state->memory[0xcccd] = 0x06; // return pc
    expected_state->memory[0xccce] = 0x00;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x00;
    expected_state->conditions.carry = 0;
    emulate8080(state); // Runs CNC
    if (state->memory[0xccce] != expected_state->memory[0xccce]) return 1;
    if (state->memory[0xcccd] != expected_state->memory[0xcccd]) return 1;
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states just after MVI B, D8
    expected_state->pc = 0x5513;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x55;
    emulate8080(state); // Runs MVI B, D8
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states after RET
    expected_state->pc = 6;
    expected_state->sp = 0xcccf;
    expected_state->b = 0x55;
    expected_state->conditions.carry = 0;
    emulate8080(state); // runs RET
    if (state_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_CC(State *state, State *expected_state)
{
    /*** This function assumes that RET and MVI B are working. ***/
    // The first CC should be skipped.
    state->memory[0] = CC; // CC 0x5511
    state->memory[1] = 0x11;
    state->memory[2] = 0x55;
    state->conditions.carry = 0;
    expected_state->pc = 0x3;
    expected_state->conditions.carry = 0;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // The second CNZ should execute.
    state->memory[3] = CC; // CC 0x5511
    state->memory[4] = 0x11;
    state->memory[5] = 0x55;
    state->conditions.carry = 1;
    state->sp = 0xcccf;
    state->memory[0x5511] = 0x06; // MVI B D8
    state->memory[0x5512] = 0x55; // D8 to be put in B is 0x55
    state->memory[0x5513] = 0xc9; // RET
    state->b = 0x00;

    // Set up the expected register states just after executed CC, before MVI B
    expected_state->pc = 0x5511;
    expected_state->memory[0xcccd] = 0x06; // return pc
    expected_state->memory[0xccce] = 0x00;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x00;
    expected_state->conditions.carry = 1;
    emulate8080(state); // Runs CC
    if (state->memory[0xccce] != expected_state->memory[0xccce]) return 1;
    if (state->memory[0xcccd] != expected_state->memory[0xcccd]) return 1;
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states just after MVI B, D8
    expected_state->pc = 0x5513;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x55;
    emulate8080(state); // Runs MVI B, D8
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states after RET
    expected_state->pc = 6;
    expected_state->sp = 0xcccf;
    expected_state->b = 0x55;
    expected_state->conditions.carry = 1;
    emulate8080(state); // runs RET
    if (state_compare(state, expected_state) == 1) return 1;
    return 0;
}

int test_CPO(State *state, State *expected_state)
{
    /*** This function assumes that RET and MVI B are working. ***/
    // The first CPO should be skipped.
    state->memory[0] = CPO; // CPO 0x5511
    state->memory[1] = 0x11;
    state->memory[2] = 0x55;
    state->conditions.parity = 1;
    expected_state->pc = 0x3;
    expected_state->conditions.parity = 1;
    emulate8080(state);
    if (state_compare(state, expected_state) == 1) return 1;

    // The second CPO should execute.
    state->memory[3] = CPO; // CPO 0x5511
    state->memory[4] = 0x11;
    state->memory[5] = 0x55;
    state->conditions.parity = 0;
    state->sp = 0xcccf;
    state->memory[0x5511] = 0x06; // MVI B D8
    state->memory[0x5512] = 0x55; // D8 to be put in B is 0x55
    state->memory[0x5513] = 0xc9; // RET
    state->b = 0x00;

    // Set up the expected register states just after executed CPO, before MVI B
    expected_state->pc = 0x5511;
    expected_state->memory[0xcccd] = 0x06; // return pc
    expected_state->memory[0xccce] = 0x00;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x00;
    expected_state->conditions.parity = 0;
    emulate8080(state); // Runs CPO
    if (state->memory[0xccce] != expected_state->memory[0xccce]) return 1;
    if (state->memory[0xcccd] != expected_state->memory[0xcccd]) return 1;
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states just after MVI B, D8
    expected_state->pc = 0x5513;
    expected_state->memory[state->sp - 1] = 0x55;
    expected_state->memory[state->sp] = 0x11;
    expected_state->sp = 0xcccd;
    expected_state->b = 0x55;
    emulate8080(state); // Runs MVI B, D8
    if (state_compare(state, expected_state) == 1) return 1;

    // Set up the expected register states after RET
    expected_state->pc = 6;
    expected_state->sp = 0xcccf;
    expected_state->b = 0x55;
    expected_state->conditions.parity = 0;
    emulate8080(state); // runs RET
    if (state_compare(state, expected_state) == 1) return 1;
    return 0;
}
int main(int argc, char *argv[])
{
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;
    // clang-format off
    switch (strtol(argv[1], NULL, 16))
    {
        case CALL:
        {
            int c1 = test_CALL(state, expected_state);
            state = Init8080();
            expected_state = Init8080();
            int c2 = test_CALL_RET(state, expected_state);
            result = c1 | c2;
            break;
        }
        case CNZ: result = test_CNZ(state, expected_state); break;
        case CZ: result = test_CZ(state, expected_state); break;
        case CNC: result = test_CNC(state, expected_state); break;
        case CC: result = test_CC(state, expected_state); break;
        case CPO: result = test_CPO(state, expected_state); break;
//        case CPE: result = test_CPE(state, expected_state); break;
//        case CP: result = test_CP(state, expected_state); break;
//        case CM: result = test_CM(state, expected_state); break;
        default: return 1; // Test failed due to incorrect test parameter
    }
    // clang-format on

    Free8080(state);
    Free8080(expected_state);

    return result;
}