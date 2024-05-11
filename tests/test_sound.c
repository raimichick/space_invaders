#include "../include/sound.h"
#include "../src/sound.c"

int main()
{

    SoundSample samples[10];

    samples[0] = load_sample("../assets/0_spaceship.wav", 1, 44100, 171, AUDIO_S16);
    samples[1] = load_sample("../assets/1_shoot.wav", 1, 44100, 150, AUDIO_S16);
    samples[2] = load_sample("../assets/2_base_hit.wav", 1, 11025, 1219, AUDIO_S16);
    samples[3] = load_sample("../assets/3_invader_hit.wav", 1, 44100, 318, AUDIO_S16);
    samples[4] = load_sample("../assets/4_walk1.wav", 1, 11025, 73, AUDIO_S8);
    samples[5] = load_sample("../assets/5_walk2.wav", 1, 11025, 66, AUDIO_S8);
    samples[6] = load_sample("../assets/6_walk3.wav", 1, 11025, 69, AUDIO_S8);
    samples[7] = load_sample("../assets/7_walk4.wav", 1, 11025, 74, AUDIO_S8);
    samples[8] = load_sample("../assets/8_spaceship_hit.wav", 1, 44100, 1091, AUDIO_S16);
    samples[9] = load_sample("../assets/9_extra_life.wav", 1, 44100, 1896, AUDIO_S16);

    int errorCode = initialize_sdl();
    if (errorCode)
    {
        return errorCode;
    }

    for (int i = 0; i < 10; i++)
    {
        errorCode = initialize_audio(&samples[i]);
        if (errorCode)
        {
            return errorCode;
        }
        play_audio(samples[i].length_ms);
    }

    clean_up();

    return 0;
}