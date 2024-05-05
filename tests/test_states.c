#include "../include/shell.h"
#include "../include/state.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_states_at_10(State *state, State *expected_state)
{
    for (size_t i = 0; i < 10; i++)
        emulate8080(state);

    expected_state->pc = 0x1a32;
    expected_state->sp = 0x23fe;
    expected_state->a = 0x00;
    expected_state->b = 0x00;
    expected_state->c = 0x00;
    expected_state->d = 0x1b;
    expected_state->e = 0x00;
    expected_state->h = 0x20;
    expected_state->l = 0x00;
    return state_compare(state, expected_state);
}

int test_states_at_25(State *state, State *expected_state)
{
    for (size_t i = 0; i < 25; i++)
        emulate8080(state);

    expected_state->pc = 0x1a35;
    expected_state->sp = 0x23fe;
    expected_state->a = 0x00;
    expected_state->b = 0xfe;
    expected_state->c = 0x00;
    expected_state->d = 0x1b;
    expected_state->e = 0x02;
    expected_state->h = 0x20;
    expected_state->l = 0x03;
    set_conditions(expected_state, 0x84); // sign, parity

    return state_compare(state, expected_state);
}

State* init_game_state()
{
    FILE *game_file = fopen("../include/invaders_combined", "rb");
    if (game_file == NULL)
    {
        perror("Error: Could not open invaders_combined");
        exit(1);
    }

    State *state = Init8080();

    fseek(game_file, 0L, SEEK_END);
    const long game_size = ftell(game_file);
    fseek(game_file, 0L, SEEK_SET);

    fread(state->memory, game_size, 1, game_file);

    fclose(game_file);
    return state;
}

int main(int argc, char *argv[])
{
    State *state = init_game_state();
    State *expected_state = Init8080();

    int result = FAIL;
    switch (strtol(argv[1], NULL, 10))
    {
        case 10: result = test_states_at_10(state, expected_state); break;
        case 25: result = test_states_at_25(state, expected_state); break;
        default: result = FAIL; // Test failed due to incorrect test parameter
    }

    Free8080(state);
    Free8080(expected_state);

    return result;
}

