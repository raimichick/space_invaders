#include "../include/sound.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

/* VARIABLES */
#define NUM_WAVEFORMS 10
static SDL_AudioDeviceID _audioDeviceId = 0;
static SDL_AudioSpec _audioSpec;
static Mix_Chunk *_sample[NUM_WAVEFORMS];

static const char *_waveFilePaths[] = {
    ROOT_DIR "/assets/0_spaceship.wav",     ROOT_DIR "/assets/1_shoot.wav",
    ROOT_DIR "/assets/2_base_hit.wav",      ROOT_DIR "/assets/3_invader_hit.wav",
    ROOT_DIR "/assets/4_walk1.wav",         ROOT_DIR "/assets/5_walk2.wav",
    ROOT_DIR "/assets/6_walk3.wav",         ROOT_DIR "/assets/7_walk4.wav",
    ROOT_DIR "/assets/8_spaceship_hit.wav", ROOT_DIR "/assets/9_extra_life.wav"};

// static const int _sampleLength[] = {171, 374, 1327, 459, 73, 66, 69, 74, 2208, 1896};

int load_samples() { return 0; }

int initialize_audio()
{

    // Set up the audio stream
    int errCode = Mix_OpenAudio(44100, AUDIO_S16, 1, 512);
    if (errCode < 0)
    {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        return 1;
    }

    // Determine the number of mixing channels
    errCode = Mix_AllocateChannels(10);
    if (errCode < 0)
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
        return 1;
    }

    // Load Samples
    for (int i = 0; i < NUM_WAVEFORMS; i++)
    {
        _sample[i] = Mix_LoadWAV(_waveFilePaths[i]);
        if (_sample[i] == NULL)
        {
            fprintf(stderr, "Unable to load wave file: %s\n", _waveFilePaths[i]);
            return 1;
        }
    }

    return 0;
}

void play_audio(int i)
{
    if (i == 0)
    {
        Mix_PlayChannel(i, _sample[i], -1);
    }
    else
    {
        Mix_PlayChannel(i, _sample[i], 0);
    }
}

void stop_audio(int i) { Mix_HaltChannel(i); }

void free_audio()
{
    for (int i = 0; i < NUM_WAVEFORMS; i++)
    {
        Mix_FreeChunk(_sample[i]);
    }
    Mix_CloseAudio();
}
