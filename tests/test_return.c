#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_RET(State *state, State *expected_state) { return 0; }

int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *state = Init8080();
    State *expected_state = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case 0xc9:
        result = test_RET(state, expected_state);
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