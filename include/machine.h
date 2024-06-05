#pragma once

#include "../include/state.h"
#include <SDL.h>

void machine_in(State *state, uint8_t port);
void machine_out(State *state, uint8_t port);

void generate_interrupt(State *state, int interrupt_num);

State *load_game_state(const char *file, int *game_size);
void handle_interrupts_and_emulate(State *state);
