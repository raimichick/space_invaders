#pragma once

#include "SDL.h"
#include <stdint.h>

static int initialize_sdl();
static int initialize_audio();
static void play_audio(int i);
static void stop_audio(int i);
static void clean_up();
static void audio_callback(void *, uint8_t *, int);

typedef struct SoundSample
{
    int length_ms;
    Uint32 len_buffer;
    Uint8 *buffer;
} SoundSample;