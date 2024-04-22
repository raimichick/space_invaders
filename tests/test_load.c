#include "../src/shell.c"

#include <string.h>

int state_compare(State *state, State *expected_state)
{
    // Compares each of the registers and conditions between the two states
    // If both states are the same, returns 0, else 1
    // Does not check memory

    if (state->a != expected_state->a) return 1;
    if (state->b != expected_state->b) return 1;
    if (state->c != expected_state->c) return 1;
    if (state->d != expected_state->d) return 1;
    if (state->e != expected_state->e) return 1;
    if (state->h != expected_state->h) return 1;
    if (state->l != expected_state->l) return 1;
    if (state->sp != expected_state->sp) return 1;
    if (state->pc != expected_state->pc) return 1;
    if (state->int_enable != expected_state->int_enable) return 1;

    if (state->conditions.zero != expected_state->conditions.zero) return 1;
    if (state->conditions.sign != expected_state->conditions.sign) return 1;
    if (state->conditions.parity != expected_state->conditions.parity) return 1;
    if (state->conditions.carry != expected_state->conditions.carry) return 1;
    if (state->conditions.aux_carry != expected_state->conditions.aux_carry)
        return 1;
    if (state->conditions.pad != expected_state->conditions.pad) return 1;

    return 0;
}

int test_LXI_B(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x01;
    state->memory[1] = 0xaa;
    state->memory[2] = 0x35;

    // Set up the expected register states
    expected_state->pc = 3;
    expected_state->b = 0x35;
    expected_state->c = 0xaa;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_LXI_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x11;
    state->memory[1] = 0x27;
    state->memory[2] = 0x89;

    // Set up the expected register states
    expected_state->pc = 3;
    expected_state->d = 0x89;
    expected_state->e = 0x27;

    emulate8080(state);

    return state_compare(state, expected_state);
}

int test_LDAX_D(State *state, State *expected_state)
{
    // Load the instruction and set up the memory
    state->memory[0] = 0x1a;
    state->memory[0x1234] = 0xf6;
    state->d = 0x12;
    state->e = 0x34;

    // Set up the expected register states
    expected_state->pc = 1;
    expected_state->d = 0x12;
    expected_state->e = 0x34;
    expected_state->a = 0xf6;

    emulate8080(state);

    return state_compare(state, expected_state);
}

/* Tests for loading values into registers
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
    case 0x01:
        result = test_LXI_B(state, expected_state);
        break;
    case 0x11:
        result = test_LXI_D(state, expected_state);
        break;
    case 0x1a:
        result = test_LDAX_D(state, expected_state);
        break;
    default:
        return 1; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    free(state->memory);
    free(expected_state->memory);
    free(state);
    free(expected_state);

    return result;
}