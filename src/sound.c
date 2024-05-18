#include "../include/sound.h"
#include "../include/state.h"
#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* VARIABLES */
static SDL_AudioDeviceID _audioDeviceId = 0;
static SDL_AudioSpec _audioSpec;
static SoundSample _samples[10];

SoundSample load_sample(char path[], int length_ms)
{
    SoundSample sample;
    sample.length_ms = length_ms;

    SDL_LoadWAV(path, &_audioSpec, &sample.buffer, &sample.len_buffer);

    return sample;
}

int initialize_sdl()
{
    if (SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "Error: Failed to initialize Audio System");
        return 1;
    }

    return 0;
}

int initialize_audio()
{

    _audioSpec.channels = 1;
    _audioSpec.freq = 44100;
    _audioSpec.format = AUDIO_S16;

    _samples[0] = load_sample(ROOT_DIR "/assets/0_spaceship.wav", 171);
    _samples[1] = load_sample(ROOT_DIR "/assets/1_shoot.wav", 347);
    _samples[2] = load_sample(ROOT_DIR "/assets/2_base_hit.wav", 1327);
    _samples[3] = load_sample(ROOT_DIR "/assets/3_invader_hit.wav", 459);
    _samples[4] = load_sample(ROOT_DIR "/assets/4_walk1.wav", 73);
    _samples[5] = load_sample(ROOT_DIR "/assets/5_walk2.wav", 66);
    _samples[6] = load_sample(ROOT_DIR "/assets/6_walk3.wav", 69);
    _samples[7] = load_sample(ROOT_DIR "/assets/7_walk4.wav", 74);
    _samples[8] = load_sample(ROOT_DIR "/assets/8_spaceship_hit.wav", 2208);
    _samples[9] = load_sample(ROOT_DIR "/assets/9_extra_life.wav", 1896);

    _audioDeviceId = SDL_OpenAudioDevice(NULL, 0, &_audioSpec, NULL, 0);
    if (_audioDeviceId == 0)
    {
        fprintf(stderr, "Error: Failed to initialize Audio Device");
        return 1; /* Could not open Device */
    }

    return 0;
}

void play_audio(int i)
{
    SDL_QueueAudio(_audioDeviceId, _samples[i].buffer, _samples[i].len_buffer);
    SDL_PauseAudioDevice(_audioDeviceId, 0);
    SDL_Delay(_samples[i].length_ms);
    SDL_PauseAudioDevice(_audioDeviceId, 1);
}

void emulateSound(State *state)
{
    // Sound 0 - Spaceship
    if ((state->ports[3] & 0b00000001) != 0)
    {
        state->ports[3] = state->ports[3] & 0b11111110;
        play_audio(0);
    }

    // Sound 1 - Shoot
    if ((state->ports[3] & 0b00000010) != 0)
    {
        state->ports[3] = state->ports[3] & 0b11111101;
        play_audio(1);
    }

    // Sound 2 - Base Hit
    if ((state->ports[3] & 0b00000100) != 0)
    {
        state->ports[3] = state->ports[3] & 0b11111011;
        play_audio(2);
    }

    // Sound 3 - Invader Hit
    if ((state->ports[3] & 0b00001000) != 0)
    {
        state->ports[3] = state->ports[3] & 0b11110111;
        play_audio(3);
    }

    // Sound 4 - Walk 1
    if ((state->ports[5] & 0b00000001) != 0)
    {
        state->ports[5] = state->ports[5] & 0b11111110;
        play_audio(4);
    }

    // Sound 5 - Walk 2
    if ((state->ports[5] & 0b00000010) != 0)
    {
        state->ports[5] = state->ports[5] & 0b11111101;
        play_audio(5);
    }

    // Sound 6 - Walk 3
    if ((state->ports[5] & 0b00000100) != 0)
    {
        state->ports[5] = state->ports[5] & 0b11111011;
        play_audio(6);
    }

    // Sound 7 - Walk 4
    if ((state->ports[5] & 0b00001000) != 0)
    {
        state->ports[5] = state->ports[3] & 0b11110111;
        play_audio(7);
    }

    // Sound 8 - Spaceship Hit
    if ((state->ports[5] & 0b00010000) != 0)
    {
        state->ports[5] = state->ports[5] & 0b11101111;
        play_audio(8);
    }

    // Sound 9 - Extra Life
    if ((state->ports[3] & 0b00010000) != 0)
    {
        state->ports[3] = state->ports[3] & 0b11101111;
        play_audio(9);
    }
}

void clean_up()
{
    SDL_CloseAudioDevice(_audioDeviceId);
    for (int i = 0; i < 10; i++)
    {
        SDL_FreeWAV(_samples[i].buffer);
    }
    SDL_Quit();
}
