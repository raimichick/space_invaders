#include "../include/disassemble8080p.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Open the game file
    FILE *game_file = fopen("../include/invaders_combined", "rb");
    if (game_file == NULL)
    {
        perror("Error: Could not open invaders_combined");
        exit(1);
    }

    State *state = Init8080();

    // Allocate space for the game data
    fseek(game_file, 0L, SEEK_END);
    const int game_size = ftell(game_file);
    fseek(game_file, 0L, SEEK_SET);

    fread(state->memory, game_size, 1, game_file);

    fclose(game_file);

    // Print disassembly
    while (state->pc < game_size)
    {
        int opbytes = disassemble8080p(state->memory, state->pc);

        state->pc += opbytes;
    }

    Free8080(state);
}
