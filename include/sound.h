#pragma once

#include "SDL.h"
#include <stdint.h>

static int initialize_sdl();
static int initialize_audio();
static void play_audio();
static void clean_up();
static void audio_callback(void *, uint8_t *, int);

/* DEFINES */
#define INVALID_AUDIO_DEVICE 0
#define PLAY_AUDIO 0
#define STOP_AUDIO 1
#define CHANNELS 1
#define SDL_AUDIO_FORMAT AUDIO_S16

typedef struct SoundSample
{
    int channels;
    int frequency;
    int length_ms;
    SDL_AudioFormat format;
    char *path;
} SoundSample;