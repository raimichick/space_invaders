/*5/18/24 updates - trying to make it testable but also easy to take what we need from it and integrate it into another file if necessary - still not tested*/
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Space Invaders", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    int quit = 0;
    int ship_x = SCREEN_WIDTH / 2;
    int ship_y = SCREEN_HEIGHT - 30; // Position ship near the bottom

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    ship_x -= 5; // Move left
                    if (ship_x < 0) ship_x = 0; // Keep ship within bounds
                    break;
                case SDLK_RIGHT:
                    ship_x += 5; // Move right
                    if (ship_x > SCREEN_WIDTH) ship_x = SCREEN_WIDTH; // Keep ship within bounds
                    break;
                case SDLK_SPACE:
                    // Fire a bullet 
                    break;
                default:
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render ship (placeholder for actual rendering code)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect ship = {ship_x, ship_y, 20, 10};
        SDL_RenderFillRect(renderer, &ship);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
