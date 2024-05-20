#include "../include/machine.h"
#include "../include/sound.h"
#include "../include/state.h"

#include <SDL.h>

int main(int argc, char *argv[])
{
    int game_size = 0;

    State *state = load_game_state("../include/invaders_combined", &game_size);

    // Initialize SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    // Test window
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 256, 224, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    // Initialize Audio
    if (initialize_audio()) exit(1);

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
