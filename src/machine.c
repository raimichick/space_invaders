#include "../include/machine.h"
#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/sound.h"
#include "../include/state.h"
#include "../include/video.h"

#if _WIN32
#include "../include/timer_win.h"
#elif __APPLE__
#include "../include/timer_apple.h"
#elif __linux__
#include "../include/timer_linux.h"
#endif

#include "rom_sections.c"

#include <SDL.h>
#include <time.h>

#define DEBUG 0

static uint8_t shift1, shift0; // hi, lo byte for shift register
static uint8_t shift_offset; // always & with 0x7. only bits 0, 1, 2 matter as value can be 0-7.
static int midscreen_interrupt = 0;
static int emulate_count = 0;
static float cycles_per_frame = 2000000 * 1.f / 60.f; // 2 MHz * 1/60 secs/cycle.

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
        if ((state->a & 0b00000001) != 0) play_audio(0); // bit 0=UFO (repeats)
        else stop_audio(0);
        if ((state->a & 0b00000010) != 0) play_audio(1); // bit 1=Shot
        else stop_audio(1);
        if ((state->a & 0b00000100) != 0) play_audio(2); // bit 2=Flash (player die)
        if ((state->a & 0b00001000) != 0) play_audio(3); // bit 3=Invader die
        if ((state->a & 0b00010000) != 0) play_audio(9); // bit 4=Extended play
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
        if ((state->a & 0b00000001) != 0) play_audio(4); // bit 0=Fleet movement 1
        if ((state->a & 0b00000010) != 0) play_audio(5); // bit 1=Fleet movement 2
        if ((state->a & 0b00000100) != 0) play_audio(6); // bit 2=Fleet movement 3
        if ((state->a & 0b00001000) != 0) play_audio(7); // bit 3=Fleet movement 4
        if ((state->a & 0b00010000) != 0) play_audio(8); // bit 4=UFO Hit
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


State *load_game_state(const char *file, int *game_size)
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
    *game_size = ftell(game_file);
    fseek(game_file, 0L, SEEK_SET);

    fread(state->memory, *game_size, 1, game_file);

    fclose(game_file);
    return state;
}

void handle_interrupts_and_emulate(State *state)
{
    if (DEBUG)
    {
        char message[100];
        print_rom_section_desc(state->pc, message);
        emulate_count++;
        if (strcmp(message, "") != 0)
            SDL_Log("%d: %s\n", emulate_count, message);
    }

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
    case OUT: // machine specific handling for OUT
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
            if (DEBUG) SDL_Log("** Interrupt Called**\n");
            if (midscreen_interrupt == 1 && cycles_elapsed > cycles_per_frame)
            {
                wait_for_frametime_elapsed(1000000.f/120.f); // given in microseconds;
                generate_interrupt(state, 2); // interrupt 2. from emulators 101.
                midscreen_interrupt = 0;
                cycles_elapsed = 0;
                if (DEBUG) SDL_Log("Draw_Screen");
                draw_screen(state);
            }
            if (midscreen_interrupt == 0 && cycles_elapsed > (cycles_per_frame/2.f))
            {
                wait_for_frametime_elapsed(1000000.f/120.f); // given in microseconds;
                generate_interrupt(state, 1); // interrupt 1.
                midscreen_interrupt = 1;
            }
        }
        break;
    }
    }
}