// https://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c

#include "../include/timer_apple.h"
#include <mach/mach_time.h>
#include <stdint.h>

static uint64_t freq_numerator = 0;
static uint64_t freq_denominator = 0;
uint64_t cur_tick_val = 0;
uint64_t prev_tick_val = 0;
uint64_t elapsed_usecs = 0;

void initialize_timer()
{
    prev_tick_val = mach_absolute_time();
    mach_timebase_info_data_t tb;
    if (mach_timebase_info(&tb) == KERN_SUCCESS && tb.denom != 0)
    {
        freq_numerator = (uint64_t)tb.numer;
        freq_denominator = (uint64_t)tb.denom;
    }
}

void wait_for_frametime_elapsed(float frametime_usecs)
{
    cur_tick_val = mach_absolute_time();
    elapsed_usecs = cur_tick_val - prev_tick_val;

    /* To prevent overflow */
    elapsed_usecs /= 1000;

    elapsed_usecs *= freq_numerator;
    elapsed_usecs /= freq_denominator;

    // Keep checking until you pass the frametime.
    while (elapsed_usecs < frametime_usecs)
    {
        cur_tick_val = mach_absolute_time();
        elapsed_usecs = cur_tick_val - prev_tick_val;

        /* To prevent overflow */
        elapsed_usecs /= 1000;

        elapsed_usecs *= freq_numerator;
        elapsed_usecs /= freq_denominator;
    }
    prev_tick_val = cur_tick_val;
}
