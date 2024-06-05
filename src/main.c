#include "../include/controls.h"
#include "../include/machine.h"
#include "../include/sound.h"
#include "../include/video.h"

#if _WIN32
#include "../include/timer_win.h"
#elif __APPLE__
#include "../include/timer_apple.h"
#elif __linux__
#include "../include/timer_linux.h"
#endif

#include <SDL.h>

#define DEBUG 0

int main(int argc, char *argv[])
{
    int game_size = 0;

    State *state = load_game_state("../include/invaders_combined", &game_size);

    // init timer
    initialize_timer();

    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);

    // init video
    if (initialize_video() != 0) exit(1);

    // Initialize Audio
    if (initialize_audio() != 0) exit(1);

    // Run ROM
    int endgame = 0;
    while (state->halt != 1 && state->pc < game_size)
    {
        handle_interrupts_and_emulate(state);
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
    free_video();
    SDL_Quit();
    return 0;
}
