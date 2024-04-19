#include "../include/disassemble8080p.h"
#include "../include/shell.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Conditions
{
    uint8_t zero : 1;
    uint8_t sign : 1;
    uint8_t parity : 1;
    uint8_t carry : 1;
    uint8_t aux_carry : 1;
    uint8_t pad : 3;
} Conditions;

typedef struct State
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t stack_pointer;
    uint16_t program_counter;
    uint8_t *memory;
    Conditions conditions;
    uint8_t int_enable;
} State;

int main()
{
    // Open the game file
    FILE *game_file = fopen("../include/invaders_combined", "rb");
    if (game_file == NULL)
    {
        perror("Error: Could not open invaders_combined");
        exit(1);
    }

    // Initialize the 8080 state
    State *state = Init8080();

    // Allocate space for the game data
    fseek(game_file, 0L, SEEK_END);
    const int game_size = ftell(game_file);
    fseek(game_file, 0L, SEEK_SET);

    // Copy file into memory
    fread(state->memory, game_size, 1, game_file);

    // Close the file
    fclose(game_file);

    // Print disassembly
    while (state->program_counter < game_size)
    {
        int opbytes = disassemble8080p(state->memory, state->program_counter);

        state->program_counter += opbytes;
    }

    free(state->memory);
}
