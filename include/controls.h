#ifndef CONTROLS_H
#define CONTROLS_H

#include "SDL.h"
#include <stdint.h>

// Define the State structure
typedef struct
{
    uint8_t a;
    uint16_t pc;
    uint8_t memory[0x10000];
    uint8_t input_state;
} State;

// Function prototypes
void init_emulator(State *state);
void emulate8080(State *state);
void update_input_state(State *state, SDL_Event *e);

#endif // CONTROLS_H
