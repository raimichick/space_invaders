#include "../include/opcodes.h"
#include "../include/sound.h"
#include "../include/state.h"

int main(int argc, char *argv[])
{
    int errorCode = initialize_sdl();
    if (errorCode)
    {
        return errorCode;
    }

    errorCode = initialize_audio();
    if (errorCode)
    {
        return errorCode;
    }

    State *state = Init8080();

    state->a = 0b00000001;
    state->memory[0] = OUT;
    state->memory[1] = 3;
    emulateSound(state);

    state->a = 0b00000010;
    state->memory[2] = OUT;
    state->memory[3] = 3;
    emulateSound(state);

    state->a = 0b00000100;
    state->memory[4] = OUT;
    state->memory[5] = 3;
    emulateSound(state);

    state->a = 0b00001000;
    state->memory[6] = OUT;
    state->memory[7] = 3;
    emulateSound(state);

    state->a = 0b00000001;
    state->memory[8] = OUT;
    state->memory[9] = 5;
    emulateSound(state);

    state->a = 0b00000010;
    state->memory[10] = OUT;
    state->memory[11] = 5;
    emulateSound(state);

    state->a = 0b00000100;
    state->memory[12] = OUT;
    state->memory[13] = 5;
    emulateSound(state);

    state->a = 0b00001000;
    state->memory[14] = OUT;
    state->memory[15] = 5;
    emulateSound(state);

    state->a = 0b00010000;
    state->memory[16] = OUT;
    state->memory[17] = 5;
    emulateSound(state);

    state->a = 0b00010000;
    state->memory[18] = OUT;
    state->memory[19] = 3;
    emulateSound(state);

    clean_up();

    return 0;
}