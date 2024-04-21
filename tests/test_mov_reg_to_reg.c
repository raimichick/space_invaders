#include "../src/shell.c"

#include <string.h>

/* Tests for moving a value from one register to another
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "0x7a") == 0)
    {
        // Initialize state
        State *state = Init8080();
        // Modify state for tests
        state->d = 5;
        state->memory[1] = 1;
        // Run command to test
        mov_reg_to_reg(state, &state->a, &state->d);
        // Validate output - Reg A = D, pc advanced by 1
        if ((state->a == state->d) && state->pc == 1) return 0;
    }
    return 1;
}