#include "../src/shell.c"

#include <string.h>

/* Tests for moving a value from memory to a register
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "0x7e") == 0) // Test MOV A,M
    {
        // Initialize state
        State *state = Init8080();
        // Modify state for tests
        state->memory[0] = 0x7e;
        state->memory[1] = 1;
        state->memory[2] = 5;
        state->l = 2;
        // Run command to test
        emulate8080(state);
        // Validate output - Reg A = 5, pc advanced by 1
        if ((state->a == 5) && state->pc == 1) return 0;
    }
    return 1;
}