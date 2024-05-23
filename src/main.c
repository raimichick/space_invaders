#include "../include/controls.h"
#include "../include/disassemble8080p.h"
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

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

int main(int argc, char *argv[])
{
    int game_size = 0;

    State *state = load_game_state("../include/invaders_combined", &game_size);

    // init timers
    init_timer();

    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    // Test window
    SDL_Window *window =
        SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         SCREEN_SIZE_MULT * SCREEN_WIDTH, SCREEN_SIZE_MULT * SCREEN_HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    // Initialize Audio
    if (initialize_audio()) exit(1);

    // Run ROM
    int endgame = 0;
    while (state->halt != 1 && state->pc < game_size)
    {
        handle_interrupts_and_emulate(state, window, surface);
        if (DEBUG) SDL_Log("%02x\n", state->memory[0x20c0]);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) endgame = 1;
            update_keyboard_input(state, &event);
        }
        if (endgame == 1) break;
    }

    Free8080(state);
    free_audio();
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Close SDL
    return 0;
}
