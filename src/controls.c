#include "../include/state.h"
#include "../include/shell.h"
#include "SDL.h"
#include <stdio.h>
#include <stdint.h>

// Define the State structure
typedef struct {
    uint8_t a;
    uint16_t pc;
    uint8_t memory[0x10000];
    uint8_t input_state;
    // Add other CPU state variables as needed
} State;

// Function prototypes
void init_emulator(State *state);
void emulate8080(State *state);
void update_input_state(State *state, SDL_Event *e);

int main(int argc, char *argv[]) {
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
    State state;

    // Initialize the emulator state
    init_emulator(&state);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else {
                // Update the input state based on the SDL event
                update_input_state(&state, &e);
            }
        }

        // Update game state
        emulate8080(&state);

        // Render game state

        // Delay to limit frame rate
        SDL_Delay(16);
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

// Initialize the emulator state
void init_emulator(State *state) {
    // Initialize all necessary parts of the state
    state->a = 0;
    state->pc = 0;
    state->input_state = 0;
    // Initialize other parts of the state as needed
}

// Emulate 8080 processor (stub function)
void emulate8080(State *state) {
    // Implement the 8080 emulation logic here
}

// Update input state based on SDL events
void update_input_state(State *state, SDL_Event *e) {
    // Handle key press events
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
        case SDLK_LEFT:
            state->input_state |= (1 << 5); // P1 joystick left
            break;
        case SDLK_RIGHT:
            state->input_state |= (1 << 6); // P1 joystick right
            break;
        case SDLK_SPACE:
            state->input_state |= (1 << 4); // P1 shoot button
            break;
        case SDLK_1:
            state->input_state |= (1 << 2); // P1 start button
            break;
        case SDLK_2:
            state->input_state |= (1 << 1); // P2 start button
            break;
        case SDLK_c:
            state->input_state &= ~(1 << 0); // Coin insert (active low)
            break;
        default:
            break;
        }
    }
    // Handle key release events
    else if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_LEFT:
            state->input_state &= ~(1 << 5); // P1 joystick left
            break;
        case SDLK_RIGHT:
            state->input_state &= ~(1 << 6); // P1 joystick right
            break;
        case SDLK_SPACE:
            state->input_state &= ~(1 << 4); // P1 shoot button
            break;
        case SDLK_1:
            state->input_state &= ~(1 << 2); // P1 start button
            break;
        case SDLK_2:
            state->input_state &= ~(1 << 1); // P2 start button
            break;
        case SDLK_c:
            state->input_state |= (1 << 0); // Coin insert (inactive)
            break;
        default:
            break;
        }
    }
}
