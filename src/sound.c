#include "../include/sound.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* VARIABLES */
#define NUM_WAVEFORMS 10
static Mix_Chunk *_sample[NUM_WAVEFORMS];
static bool _shoot_sound_played;

static const char *_waveFilePaths[] = {
    "../assets/0_spaceship.wav",   "../assets/1_shoot.wav", "../assets/2_base_hit.wav",
    "../assets/3_invader_hit.wav", "../assets/4_walk1.wav", "../assets/5_walk2.wav",
    "../assets/6_walk3.wav",       "../assets/7_walk4.wav", "../assets/8_spaceship_hit.wav",
    "../assets/9_extra_life.wav"};

// static const int _sampleLength[] = {171, 374, 1327, 459, 73, 66, 69, 74, 2208, 1896};

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
    // Check if the sample is already playing
    // prevents samples from triggering multiple times in quick succession
    if (!Mix_Playing(i))
    {
        if (i == 0)
        {
            Mix_PlayChannel(i, _sample[i], -1);
        }
        else if (i == 1)
        {
            if (_shoot_sound_played == false)
            {
                _shoot_sound_played = true;
                Mix_PlayChannel(i, _sample[i], 0);
            }
        }
        else
        {
            Mix_PlayChannel(i, _sample[i], 0);
        }
    }
}

void stop_audio(int i)
{
    if (i == 1)
    {
        _shoot_sound_played = false;
    }
    else
    {
        Mix_HaltChannel(i);
    }
}

void free_audio()
{
    for (int i = 0; i < NUM_WAVEFORMS; i++)
    {
        Mix_FreeChunk(_sample[i]);
    }
    Mix_CloseAudio();
}
