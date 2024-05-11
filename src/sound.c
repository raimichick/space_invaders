#include "../include/sound.h"
#include "../include/state.h"
#include "SDL.h"

#include <stdlib.h>
#include <string.h>

/* VARIABLES */
static SDL_AudioDeviceID _audioDeviceId = 0;
static Uint8 *_audioBuffer = NULL;
static Uint32 _audioLength = 0;

SoundSample load_sample(char path[], int channels, int freq, int length_ms, SDL_AudioFormat format)
{
    SoundSample sample;
    sample.path = path;
    sample.channels = channels;
    sample.frequency = freq;
    sample.length_ms = length_ms;
    sample.format = format;

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

int initialize_audio(SoundSample *sample)
{
    SDL_AudioSpec audioSpec;

    audioSpec.channels = sample->channels;
    audioSpec.freq = sample->frequency;
    audioSpec.format = sample->format;
    audioSpec.callback = audio_callback;

    _audioDeviceId = SDL_OpenAudioDevice(NULL, 0, &audioSpec, NULL, 0);
    if (_audioDeviceId == INVALID_AUDIO_DEVICE)
    {
        return -2; /* Could not open Device */
    }

    if (SDL_LoadWAV(sample->path, &audioSpec, &_audioBuffer, &_audioLength) == NULL)
    {
        return -3; /* File Not Found */
    }

    return 0;
}

void play_audio(int length_ms)
{
    SDL_PauseAudioDevice(_audioDeviceId, PLAY_AUDIO);
    SDL_Delay(length_ms);
    SDL_PauseAudioDevice(_audioDeviceId, STOP_AUDIO);
}

void audio_callback(void *userData, Uint8 *stream, int length)
{
    if (_audioLength == 0)
    {
        return;
    }
    if (length > (int)_audioLength)
    {
        length = _audioLength;
    }

    memset(stream, 0, length); /* Silence everything */
    SDL_MixAudioFormat(stream, _audioBuffer, SDL_AUDIO_FORMAT, length, SDL_MIX_MAXVOLUME);

    _audioBuffer += length;
    _audioLength -= length;
}

void clean_up()
{
    SDL_CloseAudioDevice(_audioDeviceId);
    SDL_FreeWAV(_audioBuffer);
    SDL_Quit();
}