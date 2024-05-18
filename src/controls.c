#include "../include/controls.h"
#include "SDL.h"
#include <stdio.h>

// Function definitions
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
        switch (e->key.keysym.sym)
        {
        case SDLK_LEFT:
        {
            state->input_state |= (1 << 5); // P1 joystick left
            break;
        }
        case SDLK_RIGHT:
        {
            state->input_state |= (1 << 6); // P1 joystick right
            break;
        }
        case SDLK_SPACE:
        {
            state->input_state |= (1 << 4); // P1 shoot button
            break;
        }
        case SDLK_1:
        {
            state->input_state |= (1 << 2); // P1 start button
            break;
        }
        case SDLK_2:
        {
            state->input_state |= (1 << 1); // P2 start button
            break;
        }
        case SDLK_c:
        {
            state->input_state &= ~(1 << 0); // Coin insert (active low)
            break;
        }
        default:
            break;
        }
    }
    // Handle key release events
    else if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym)
        {
        case SDLK_LEFT:
        {
            state->input_state &= ~(1 << 5); // P1 joystick left
            break;
        }
        case SDLK_RIGHT:
        {
            state->input_state &= ~(1 << 6); // P1 joystick right
            break;
        }
        case SDLK_SPACE:
        {
            state->input_state &= ~(1 << 4); // P1 shoot button
            break;
        }
        case SDLK_1:
        {
            state->input_state &= ~(1 << 2); // P1 start button
            break;
        }
        case SDLK_2:
        {
            state->input_state &= ~(1 << 1); // P2 start button
            break;
        }
        case SDLK_c:
        {
            state->input_state |= (1 << 0); // Coin insert (inactive)
            break;
        }
        default:
            break;
        }
    }
}
