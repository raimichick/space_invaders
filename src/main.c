#include "../include/disassemble8080p.h"
#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"
#include <SDL.h>
#include "../include/video.h"
#include "rom_sections.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int game_size = 0;
uint8_t shift1, shift0; // hi byte and lo byte for shift register
uint8_t shift_offset;   // always & with 0x7. only bits 0, 1, 2 matter as shift_offset can be 0-7.
time_t last_interrupt = 0;
int scanline96 = 0;
int scanline224 = 0;

void machine_in(State *state, uint8_t port)
{
    // clang-format off
    switch (port)
    {
    case 0: { printf("ERR NEED TO HANDLE IN 0\n"); break; }
    case 1: { printf("ERR NEED TO HANDLE IN 1\n"); break; }
    case 2: { printf("ERR NEED TO HANDLE IN 2\n"); break; }
    case 3: {
        printf("****IN 3 GOOD***");
        uint16_t v = (shift1 << 8) | shift0;
        state->a = ((v >> (8 - shift_offset)) & 0xff);
        break;
    }
    case 4: { printf("ERR NEED TO HANDLE IN 4\n"); break; }
    case 5: { printf("ERR NEED TO HANDLE IN 5\n"); break; }
    case 6: { printf("ERR NEED TO HANDLE IN 6\n"); break; }
    case 7: { printf("ERR NEED TO HANDLE IN 7\n"); break; }
    default: break;
    }
}

void machine_out(State *state, uint8_t port)
{
    switch (port)
    {
    case 0: { printf("ERR NEED TO HANDLE OUT 0\n"); break; }
    case 1: { printf("ERR NEED TO HANDLE OUT 1\n"); break; }
    case 2:
        printf("****OUT 2 GOOD***");
        shift_offset = state->a & 0x7;
        break;

    case 3: { printf("ERR NEED TO HANDLE OUT 3\n"); break; }
    case 4:
        //printf("****OUT 4 GOOD***");
        shift0 = shift1;
        shift1 = state->a;
        break;
    case 5: { printf("ERR NEED TO HANDLE OUT 5\n"); break; }
    case 6: { printf("IGNORE: OUT 6 is debug port?. gets written to when writing text to screen\n"); break; }
    case 7: { printf("ERR NEED TO HANDLE OUT 7\n"); break; }
    default: break;
    }
}

void generate_interrupt(State *state, int interrupt_num) { call_helper(state, 8 * interrupt_num); }

State *load_game_state(const char *file)
{
    // Open the game file
    FILE *game_file = fopen(file, "rb");
    if (game_file == NULL)
    {
        perror("Error: Could not open invaders_combined");
        exit(1);
    }

    State *state = Init8080();

    // Allocate space for the game data
    fseek(game_file, 0L, SEEK_END);
    game_size = ftell(game_file);
    fseek(game_file, 0L, SEEK_SET);

    fread(state->memory, game_size, 1, game_file);

    fclose(game_file);
    return state;
}

void handle_interrupts_and_emulate(State *state)
{
    int printed_rom_section = print_rom_section_desc(state->pc);
    uint8_t *opcode = &state->memory[state->pc];
    switch (*opcode)
    {
        case IN: // machine specific handling for IN
        {
            uint8_t port = opcode[1];
            machine_in(state, port);
            state->pc += 2;
            break;
        }
        case OUT: // machine specific handling forOUT
        {
            uint8_t port = opcode[1];
            machine_out(state, port);
            state->pc += 2;
            break;
        }
        default:
        {
            emulate8080(state);
            if (time(NULL) - last_interrupt > 1.f / 120.f ) // 1/120 second has elapsed
            {
                if (state->interrupt_enabled)
                {
                    printf("** Interrupt Called**\n");
                    if (scanline96 == 0 & scanline224 == 0)
                    {
                        generate_interrupt(state, 1); // interrupt 1.
                        scanline96 = 1;
                    }
                    else
                    {
                        generate_interrupt(state, 2); // interrupt 2. from emulators 101.
                        scanline96 = 0;
                        // draw screen here.
                    }
                    last_interrupt = time(NULL); // save time.
                }
            }
            break;
        }
    }
    // CAREFUL WITH THIS: YOU WILL CAN ACCIDENTALLY CREATE A LOT OF IMAGES
    // if (emulate_count > 40000000 && emulate_count % 100000000 <= 0)
    // {
    //     printf("printing...");
    //     // spinvaders_vram_matrix_to_png(state, emulate_count);
    //     printf("printed.");
    //     state->halt = 1
    // }
    emulate8080(state);
}

int main(int argc, char *argv[])
{
    State *state = load_game_state("../include/invaders_combined");

    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    // Test window
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 680, 480, 0);
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    // Run ROM
    int endgame = 0;
    SDL_Event event;
    while (state->halt != 1 && state->pc < game_size)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) endgame = 1;
        }
        if (endgame == 1) break;
    }

    Free8080(state);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Close SDL
    return 0;
}
