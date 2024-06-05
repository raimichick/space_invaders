#include "../include/machine.h"
#include "../include/opcodes.h"
#include "../include/sound.h"
#include "../include/state.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "Error: Failed to initiialize SDL audio system");
        return FAIL;
    }

    if (initialize_audio() != 0) return FAIL;

    State *state = Init8080();

    // Sound 0 - Spaceship
    state->a = 0b00000001;
    state->memory[0] = OUT;
    state->memory[1] = 3;
    machine_out(state, 3);
    SDL_Delay(5000);
    stop_audio(0);
    SDL_Delay(1000);

    // Sound 1 - Shoot
    state->a = 0b00000010;
    state->memory[2] = OUT;
    state->memory[3] = 3;
    machine_out(state, 3);
    SDL_Delay(1000);

    // Sound 2 - Base Hit
    state->a = 0b00000100;
    state->memory[4] = OUT;
    state->memory[5] = 3;
    machine_out(state, 3);
    SDL_Delay(2000);

    // Sound 3 - Invader Hit
    state->a = 0b00001000;
    state->memory[6] = OUT;
    state->memory[7] = 3;
    machine_out(state, 3);
    SDL_Delay(1000);

    // Sound 4 - Walk 1
    state->a = 0b00000001;
    state->memory[8] = OUT;
    state->memory[9] = 5;
    machine_out(state, 5);
    SDL_Delay(1000);

    // Sound 5 - Walk 2
    state->a = 0b00000010;
    state->memory[10] = OUT;
    state->memory[11] = 5;
    machine_out(state, 5);
    SDL_Delay(1000);

    // Sound 6 - Walk 3
    state->a = 0b00000100;
    state->memory[12] = OUT;
    state->memory[13] = 5;
    machine_out(state, 5);
    SDL_Delay(1000);

    // Sound 7 - Walk 4
    state->a = 0b00001000;
    state->memory[14] = OUT;
    state->memory[15] = 5;
    machine_out(state, 5);
    SDL_Delay(1000);

    // Sound 8 - Spaceship Hit
    state->a = 0b00010000;
    state->memory[16] = OUT;
    state->memory[17] = 5;
    machine_out(state, 5);
    SDL_Delay(3000);

    // Sound 9 - Extra Life
    state->a = 0b00010000;
    state->memory[18] = OUT;
    state->memory[19] = 3;
    machine_out(state, 3);
    SDL_Delay(2000);

    // All sounds at once
    state->a = 0b00011111;
    state->memory[20] = OUT;
    state->memory[21] = 3;
    machine_out(state, 3);
    state->memory[22] = OUT;
    state->memory[23] = 5;
    machine_out(state, 5);
    SDL_Delay(3000);
    stop_audio(0);
    SDL_Delay(1000);

    free_audio();
    SDL_Quit();

    return PASS;
}