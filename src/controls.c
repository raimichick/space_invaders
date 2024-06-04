#include "../include/controls.h"

// clang-format off
void update_keyboard_input(State *state, SDL_Event *e)
{
    // Handle key press events
    if (e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_c:     { state->ports[1] &= ~(1 << 0); break; } // Coin insert (active low)
        case SDLK_2:     { state->ports[1] |=  (1 << 1); break; } // P2 start button
        case SDLK_1:     { state->ports[1] |=  (1 << 2); break; } // P1 start button
        case SDLK_f:
        case SDLK_UP:
        case SDLK_SPACE: { state->ports[1] |=  (1 << 4); state->ports[2] = state->ports[1]; break; } // P1 & P2 shoot button
        case SDLK_a:
        case SDLK_LEFT:  { state->ports[1] |=  (1 << 5); state->ports[2] = state->ports[1]; break; } // P1 & P2 joystick left
        case SDLK_d:
        case SDLK_RIGHT: { state->ports[1] |=  (1 << 6); state->ports[2] = state->ports[1]; break; } // P1 & P2 joystick right

        case SDLK_l:     { state->ports[2] |=  ((state->ports[2] + 1) % 4); break; } // # of lives (0:3,1:4,2:5,3:6)
        case SDLK_t:     { state->ports[2] |=  (1 << 2); break; } // tilt 'button'
        case SDLK_b:     { state->ports[2] |=  (1 << 3); break; } // dipswitch bonus life at 1:1000,0:1500
        case SDLK_i:     { state->ports[2] |=  (1 << 7); break; } // dipswitch coin info 1:off,0:on
        case SDLK_q:     { state->halt = 1; break;}
        default: break;
        }
    }
    // Handle key release events
    else if (e->type == SDL_KEYUP)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_c:     { state->ports[1] |=  (1 << 0); break; } // Coin insert (inactive)
        case SDLK_2:     { state->ports[1] &= ~(1 << 1); break; } // P2 start button
        case SDLK_1:     { state->ports[1] &= ~(1 << 2); break; } // P1 start button
        case SDLK_f:
        case SDLK_UP:
        case SDLK_SPACE: { state->ports[1] &= ~(1 << 4); state->ports[2] = state->ports[1]; break; } // P1 & P2 shoot button
        case SDLK_a:
        case SDLK_LEFT:  { state->ports[1] &= ~(1 << 5); state->ports[2] = state->ports[1]; break; } // P1 & P2 joystick left
        case SDLK_d:
        case SDLK_RIGHT: { state->ports[1] &= ~(1 << 6); state->ports[2] = state->ports[1]; break; } // P1 & P2 joystick right

        case SDLK_t:     { state->ports[2] &=  (1 << 2); break; } // tilt 'button'
        case SDLK_b:     { state->ports[2] &=  (1 << 3); break; } // dipswitch bonus life at 1:1000,0:1500
        case SDLK_i:     { state->ports[2] &=  (1 << 7); break; } // dipswitch coin info 1:off,0:on
        default: break;
        }
    }
}
