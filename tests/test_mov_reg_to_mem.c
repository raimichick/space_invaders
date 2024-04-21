#include "../src/shell.c"

#include <string.h>

/* Tests for moving a value from a register to memory
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "0x77") == 0) // Test MOV M,A
    {
        // Initialize state
        State *state = Init8080();
        // Modify state for tests
        state->a = 5;
        state->memory[0] = 0x77;
        state->memory[1] = 1;
        state->l = 2;
        // Run command to test
        emulate8080(state);
        // Validate output - Reg A = 5, pc advanced by 1
        if ((state->memory[2] == 5) && state->pc == 1) return 0;
    }
    return 1;
}