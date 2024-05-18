#pragma once
#include "../include/state.h"
#include <SDL.h>

#define VIDEO_MEMORY_START 0x2400
#define VIDEO_MEMORY_END 0x3FFF // 0x2400 + 256*224/8 = 7168 (7K bytes)
#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 224

void spinvaders_vram_matrix_to_png(State *state, int lbl_prefix);

void spinvaders_vram_matrix_to_surface(State *state, SDL_Surface *surface);
