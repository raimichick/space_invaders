#include "../include/shell.h"
#include "../include/state.h"

#include <string.h>

/* Tests for moving a value from one register to another
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "0x7a") == 0) // Test MOV A,D
    {
        // Initialize state
        State *state = Init8080();
        // Modify state for tests
        state->d = 5;
        state->memory[0] = 0x7a;
        state->memory[1] = 1;
        // Run command to test
        emulate8080(state);
        // Validate output - Reg A = 5, pc advanced by 1
        if ((state->a == 5) && state->pc == 1) return 0;
    }
    if (strcmp(argv[1], "0x7b") == 0) // Test MOV A,E
    {
        // Initialize state
        State *state = Init8080();
        // Modify state for tests
        state->e = 5;
        state->memory[0] = 0x7b;
        state->memory[1] = 1;
        // Run command to test
        emulate8080(state);
        // Validate output - Reg A = 5, pc advanced by 1
        if ((state->a == 5) && state->pc == 1) return 0;
    }
    if (strcmp(argv[1], "0x7c") == 0) // Test MOV A,H
    {
        // Initialize state
        State *state = Init8080();
        // Modify state for tests
        state->h = 5;
        state->memory[0] = 0x7c;
        state->memory[1] = 1;
        // Run command to test
        emulate8080(state);
        // Validate output - Reg A = 5, pc advanced by 1
        if ((state->a == 5) && state->pc == 1) return 0;
    }
    return 1;
}