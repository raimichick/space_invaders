#include "../include/shell.h"
#include "../include/state.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int test_state_after_x_runs(State *state, State *expected_state, int run_count)
{
    // run emulator x times
    for (size_t i = 0; state->halt == 0 && i < run_count; i++)
    {
        if (DEBUG)
        {
            setbuf(stdout, 0);
            print_next_x_operations(state, 10, i);
        }
        emulate8080(state);
    }

    switch (run_count)
    {
    case 10:
    {
        set_reg_pair(expected_state, "af", 0x0000);
        set_reg_pair(expected_state, "bc", 0x0000);
        set_reg_pair(expected_state, "de", 0x1b00);
        set_reg_pair(expected_state, "hl", 0x2000);
        expected_state->pc = 0x1a32;
        expected_state->sp = 0x23fe;
        break;
    }
    case 15:
    {
        set_reg_pair(expected_state, "af", 0x0190);
        set_reg_pair(expected_state, "bc", 0xff00);
        set_reg_pair(expected_state, "de", 0x1b01);
        set_reg_pair(expected_state, "hl", 0x2001);
        expected_state->pc = 0x1a37;
        expected_state->sp = 0x23fe;
        break;
    }
    case 25:
    {
        set_reg_pair(expected_state, "af", 0x0084);
        set_reg_pair(expected_state, "bc", 0xfe00);
        set_reg_pair(expected_state, "de", 0x1b02);
        set_reg_pair(expected_state, "hl", 0x2003);
        expected_state->pc = 0x1a35;
        expected_state->sp = 0x23fe;
        break;
    }
    case 100:
    {
        set_reg_pair(expected_state, "af", 0xf880);
        set_reg_pair(expected_state, "bc", 0xf100);
        set_reg_pair(expected_state, "de", 0x1b0f);
        set_reg_pair(expected_state, "hl", 0x200f);
        expected_state->pc = 0x1a32;
        expected_state->sp = 0x23fe;
        break;
    }
    case 1000:
    {
        set_reg_pair(expected_state, "af", 0x1400);
        set_reg_pair(expected_state, "bc", 0x5b00);
        set_reg_pair(expected_state, "de", 0x1ba5);
        set_reg_pair(expected_state, "hl", 0x20a5);
        expected_state->pc = 0x1a32;
        expected_state->sp = 0x23fe;
        break;
    }
    case 10000:
    {
        set_reg_pair(expected_state, "af", 0x2a85);
        set_reg_pair(expected_state, "bc", 0x0000);
        set_reg_pair(expected_state, "de", 0x1c00);
        set_reg_pair(expected_state, "hl", 0x2a9a);
        expected_state->pc = 0x1a5f;
        expected_state->sp = 0x23fc;
        break;
    }
    case 25000:
    {
        set_reg_pair(expected_state, "af", 0x3685);
        set_reg_pair(expected_state, "bc", 0x0000);
        set_reg_pair(expected_state, "de", 0x1c00);
        set_reg_pair(expected_state, "hl", 0x3652);
        expected_state->pc = 0x1a5f;
        expected_state->sp = 0x23fc;
        break;
    }
    case 37500:
    {
        set_reg_pair(expected_state, "af", 0x1200);
        set_reg_pair(expected_state, "bc", 0x001b);
        set_reg_pair(expected_state, "de", 0x1e00);
        set_reg_pair(expected_state, "hl", 0x1e90);
        expected_state->pc = 0x090a;
        expected_state->sp = 0x23f6;
        break;
    }
    case 50000:
    {
        set_reg_pair(expected_state, "af", 0x3d20);
        set_reg_pair(expected_state, "bc", 0x0000);
        set_reg_pair(expected_state, "de", 0x1fb0);
        set_reg_pair(expected_state, "hl", 0x3e01);
        expected_state->pc = 0x0add;
        expected_state->sp = 0x23fe;
        break;
    }
    case 100000:
    {
        set_reg_pair(expected_state, "af", 0x2d20);
        set_reg_pair(expected_state, "bc", 0x0000);
        set_reg_pair(expected_state, "de", 0x1fb0);
        set_reg_pair(expected_state, "hl", 0x3e01);
        expected_state->pc = 0x0add;
        expected_state->sp = 0x23fe;
        break;
    }

    default: return FAIL;
    }

    return state_compare_to_js_site(state, expected_state);
}

State *init_game_state()
{
    FILE *game_file = fopen(ROOT_DIR "/include/invaders_combined", "rb");
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

    if (DEBUG) print_next_x_operations(state, 10, 0);

    const int run_count = strtol(argv[1], NULL, 10);
    const int result = test_state_after_x_runs(state, expected_state, run_count);

    Free8080(state);
    Free8080(expected_state);

    return result;
}
