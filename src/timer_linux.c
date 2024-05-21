// https://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c

#include "../include/timer_linux.h"
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#ifdef _SC_MONOTONIC_CLOCK
if (sysconf(_SC_MONOTONIC_CLOCK) > 0)
{
    /* A monotonic clock is present */
    uint64_t get_posix_clock_time_usecs()
    {
        struct timespec ts;

        if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
            return (uint64_t)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
        else
            return 0;
    }
}
else // monotonic clock is not present
{
    uint64_t get_gtod_clock_time_usecs()
    {
        struct timeval tv;

        if (gettimeofday(&tv, NULL) == 0)
            return (uint64_t)(tv.tv_sec * 1000000 + tv.tv_usec);
        else
            return 0;
    }
}
#endif

uint64_t cur_time_val = 0;
uint64_t prev_time_val = 0;
uint64_t elapsed_usecs = 0;

void init_timer() { prev_time_val = get_posix_clock_time_usec(); }

void wait_for_frametime_elapsed(float frametime_us)
{
    cur_time_val = get_posix_clock_time_usec();
    elapsed_usecs = cur_time_val - prev_time_val;

    // Keep checking until you pass the frametime.
    while (elapsed_usecs < frametime_us)
    {
        cur_time_val = get_posix_clock_time_usec();
        elapsed_usecs = cur_time_val - prev_time_val;
    }

    prev_time_val = cur_time_val;
}
