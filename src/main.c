#include "../include/disassemble8080p.h"
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

    // Allocate space for the game data
    fseek(game_file, 0L, SEEK_END);
    const int game_size = ftell(game_file);
    fseek(game_file, 0L, SEEK_SET);
    unsigned char *game = malloc(game_size);

    // Copy file into allocated space
    fread(game, game_size, 1, game_file);

    // Close the file
    fclose(game_file);

    // Print disassembly
    output_disassemble(game, game_size);

    free(game);
}
