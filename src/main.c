//
// Created by cxhx4 on 4/13/2024.
//
#include "../include/disassemble8080p.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Open the game file
    FILE *invaders_file = fopen("../include/invaders_combined", "rb");
    if (invaders_file == NULL)
    {
        perror("Error: Could not open invaders_combined");
        exit(1);
    }

    // Allocate space for the game data
    fseek(invaders_file, 0L, SEEK_END);
    const int invaders_size = ftell(invaders_file);
    fseek(invaders_file, 0L, SEEK_SET);
    unsigned char *invaders_game = malloc(invaders_size);

    // Copy file into allocated space
    fread(invaders_game, invaders_size, 1, invaders_file);

    // Close the file
    fclose(invaders_file);

    // Print disassembly
    int dis_i = 0;
    while (dis_i < invaders_size)
    {
        int opbytes = disassemble8080p(invaders_game, dis_i);
        dis_i += opbytes;
    }
}
