#pragma once

#include "SDL.h"
#include <stdint.h>

int initialize_sdl();
int initialize_audio();
void play_audio(int i);
void stop_audio(int i);
void free_audio();
void audio_callback(void *, uint8_t *, int);

typedef struct SoundSample
{
    int length_ms;
    Uint32 len_buffer;
    Uint8 *buffer;
} SoundSample;