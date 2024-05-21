#include "../include/controls.h"
#include "../include/state.h"
#include "SDL.h"
#include <stdio.h>

// Update input state based on SDL events
void get_keyboard_input(State *state, SDL_Event *e)
{
    // Handle key press events
    if (e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_LEFT:
        {
            state->ports[1] |= 0b00100000;     // P1 joystick left
            state->ports[2] = state->ports[1]; // for player two
            break;
        }
        case SDLK_RIGHT:
        {
            state->ports[1] |= 0b01000000;     // P1 joystick right
            state->ports[2] = state->ports[1]; // for player two
            break;
        }
        case SDLK_SPACE:
        {
            state->ports[1] |= 0b00010000;     // P1 shoot button
            state->ports[2] = state->ports[1]; // for player two
            break;
        }
        case SDLK_1:
        {
            state->ports[1] |= 0b00000100; // P1 start button
            break;
        }
        case SDLK_2:
        {
            state->ports[1] |= 0b00000010; // P2 start button
            break;
        }
        case SDLK_c:
        {
            state->ports[1] |= 0b00000001; // Coin insert (active low)
            break;
        }
        default: break;
        }
    }
    // Handle key release events
    else if (e->type == SDL_KEYUP)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_LEFT:
        {
            state->ports[1] &= ~0b00100000;    // P1 joystick left
            state->ports[2] = state->ports[1]; // for player two
            break;
        }
        case SDLK_RIGHT:
        {
            state->ports[1] &= ~(1 << 6);      // P1 joystick right
            state->ports[2] = state->ports[1]; // for player two
            break;
        }
        case SDLK_SPACE:
        {
            state->ports[1] &= ~(1 << 4);      // P1 shoot button
            state->ports[2] = state->ports[1]; // for player two
            break;
        }
        case SDLK_1:
        {
            state->ports[1] &= ~(1 << 2); // P1 start button
            break;
        }
        case SDLK_2:
        {
            state->ports[1] &= ~(1 << 1); // P2 start button
            break;
        }
        case SDLK_c:
        {
            state->ports[1] |= (1 << 0); // Coin insert (inactive)
            break;
        }
        default: break;
        }
    }
}
