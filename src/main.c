#include "../include/disassemble8080p.h"
#include <stdio.h>
#include <stdlib.h>

void output_disassemble(unsigned char *game, int game_size);

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

void output_disassemble(unsigned char *game, int game_size)
{
    // Create or open a file to save the opcode output
    FILE *output_file = freopen("../include/output_file", "w", stdout);

    // Print disassembly to output_file
    int dis_i = 0;
    int opcode_count[256] = {0};
    while (dis_i < game_size)
    {
        int opbytes = disassemble8080p(game, dis_i);
        dis_i += opbytes;
        opcode_count[game[dis_i]] += 1;
    }

    // Close output_file
    fclose(output_file);

    // Create or open a file to save the opcode count
    FILE *output_count = freopen("../include/output_count", "w", stdout);

    // Print opcode counts to opcode_count file
    for (int i = 0; i < 0xff; i++)
    {
        printf("0x%02x occurrences: %d\n", i, opcode_count[i]);
    }

    // Close opcode_count file
    fclose(output_count);
}