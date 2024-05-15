#include "../include/sound.h"
#include "../src/sound.c"

int main()
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

    state->ports[3] = 0b00000001;
    emulateSound(state);

    state->ports[3] = 0b00000010;
    emulateSound(state);

    state->ports[3] = 0b00000100;
    emulateSound(state);

    state->ports[3] = 0b00001000;
    emulateSound(state);

    state->ports[5] = 0b00000001;
    emulateSound(state);

    state->ports[5] = 0b00000010;
    emulateSound(state);

    state->ports[5] = 0b00000100;
    emulateSound(state);

    state->ports[5] = 0b00001000;
    emulateSound(state);

    state->ports[5] = 0b00010000;
    emulateSound(state);

    state->ports[3] = 0b00010000;
    emulateSound(state);

    clean_up();

    return 0;
}