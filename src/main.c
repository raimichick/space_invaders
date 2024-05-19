#include "../include/disassemble8080p.h"
#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"
#include "../include/video.h"
#include "../include/controls.h"
#include "rom_sections.c"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int game_size = 0;
uint8_t shift1, shift0; // hi byte and lo byte for shift register
uint8_t shift_offset;   // always & with 0x7. only bits 0, 1, 2 matter as shift_offset can be 0-7.
time_t last_interrupt = 0;
int scanline96 = 0;
int emulate_count = 0;
float cycles_per_frame = 2000000 * 1.f / 60.f; // 2 million cycles/second * 1/60 seconds/cycle.

void machine_in(State *state, uint8_t port)
{
    // clang-format off
    switch (port)
    {
    case 0: { state->a = 0x70; break; }
    case 1: { state->a = state->ports[1]; break; }
    case 2: { state->a = state->ports[2]; break; }
    case 3: {
        uint16_t v = (shift1 << 8) | shift0;
        state->a = ((v >> (8 - shift_offset)) & 0xff);
        break;
    }
    case 4: { SDL_Log("ERR NEED TO HANDLE IN 4\n"); break; }
    case 5: { SDL_Log("ERR NEED TO HANDLE IN 5\n"); break; }
    case 6: { SDL_Log("ERR NEED TO HANDLE IN 6\n"); break; }
    case 7: { SDL_Log("ERR NEED TO HANDLE IN 7\n"); break; }
    default: break;
    }
}

void machine_out(State *state, uint8_t port)
{
    switch (port)
    {
    case 0: { SDL_Log("ERR NEED TO HANDLE OUT 0\n"); break; }
    case 1: { SDL_Log("ERR NEED TO HANDLE OUT 1\n"); break; }
    case 2: shift_offset = state->a & 0x7; break;
    case 3:
    {
//        SDL_Log("ERR NEED TO HANDLE OUT 3 SOUND\n");
        // bit 0=UFO (repeats)        SX0 0.raw
        // bit 1=Shot                 SX1 1.raw
        // bit 2=Flash (player die)   SX2 2.raw
        // bit 3=Invader die          SX3 3.raw
        // bit 4=Extended play        SX4
        // bit 5= AMP enable          SX5
        // bit 6= NC (not wired)
        // bit 7= NC (not wired)
        // Port 4: (discrete sounds)
        // bit 0-7 shift data (LSB on 1st write, MSB on 2nd)
        break;
    }
    case 4: { shift0 = shift1; shift1 = state->a; break; }
    case 5:
    {
//        SDL_Log("ERR NEED TO HANDLE OUT 5 SOUND\n");
        // bit 0=Fleet movement 1     SX6 4.raw
        // bit 1=Fleet movement 2     SX7 5.raw
        // bit 2=Fleet movement 3     SX8 6.raw
        // bit 3=Fleet movement 4     SX9 7.raw
        // bit 4=UFO Hit              SX10 8.raw
        // bit 5= NC (Cocktail mode control ... to flip screen)
        // bit 6= NC (not wired)
        // bit 7= NC (not wired)
        break;
    }
//    case 6: { SDL_Log("IGNORE: OUT 6 is debug port?. gets written to when writing text to screen\n"); break; }
//    case 7: { SDL_Log("ERR NEED TO HANDLE OUT 7\n"); break; }
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

void handle_interrupts_and_emulate(State *state, SDL_Window *window, SDL_Surface* surface)
{
    char message[100];
    print_rom_section_desc(state->pc, message);
    emulate_count++;
//    if (strcmp(message, "") != 0)
//        SDL_Log("%d: %s\n", emulate_count, message);
    //state->memory[0x20c1] = 1; // turn demo on.

    uint8_t *opcode = &state->memory[state->pc];
    switch (*opcode)
    {
    case IN: // machine specific handling for IN
    {
        uint8_t port = opcode[1];
        machine_in(state, port);
        state->pc += 2;
        wait_cycles(10);
        break;
    }
    case OUT: // machine specific handling forOUT
    {
        uint8_t port = opcode[1];
        machine_out(state, port);
        state->pc += 2;
        wait_cycles(10);
        break;
    }
    default:
    {
        emulate8080(state);
        if (state->interrupt_enabled)
        {
//            SDL_Log("** Interrupt Called**\n");
            if (scanline96 == 0 && cycles_elapsed > (cycles_per_frame/2.f))
            {
                generate_interrupt(state, 1); // interrupt 1.
                scanline96 = 1;
            }
            if (scanline96 == 1 && cycles_elapsed > cycles_per_frame)
            {
                generate_interrupt(state, 2); // interrupt 2. from emulators 101.
                scanline96 = 0;
                cycles_elapsed = 0;
                // draw screen here.
//                SDL_Log("Draw_Screen");
                spinvaders_vram_matrix_to_surface(state, surface);
                SDL_UpdateWindowSurface(window);
            }
            last_interrupt = time(NULL); // save time.
        }
        break;
    }
    }
}

int main(int argc, char *argv[])
{
    State *state = load_game_state("../include/invaders_combined");

    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    // Test window
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 2*224, 2*256, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    // Run ROM
    int endgame = 0;
    while (state->halt != 1 && state->pc < game_size)
    {
        handle_interrupts_and_emulate(state, window, surface);
//        SDL_Log("%02x\n", state->memory[0x20c0]);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) endgame = 1;
            update_keyboard_input(state, &event);

        }
        if (endgame == 1) break;
    }

    Free8080(state);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Close SDL
    return 0;
}
