#include <SDL2/SDL.h>
#include <stdio.h>

if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return 1;
}

SDL_Window *win = SDL_CreateWindow("Space Invaders", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
if (win == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
}

SDL_Event e;
int quit = 0;

while (!quit) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = 1;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                // Move ship left
                break;
            case SDLK_RIGHT:
                // Move ship right
                break;
            case SDLK_SPACE:
                // Fire
                break;
            default:
                break;
            }
        }
    }

    // Update game state
    // Render game state
}

SDL_DestroyWindow(win);
SDL_Quit();

int ship_x = 320; // Initial position of the ship

switch (e.key.keysym.sym) {
case SDLK_LEFT:
    ship_x -= 5; // Move left
    break;
case SDLK_RIGHT:
    ship_x += 5; // Move right
    break;
case SDLK_SPACE:
    // Fire a bullet
    break;
default:
    break;
}

