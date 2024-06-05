// https://learn.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps?redirectedfrom=MSDN

#include "../include/timer_win.h"
#include <profileapi.h>

LARGE_INTEGER frequency, cur_tick_val, prev_tick_val, elapsed_usecs;
void initialize_timer()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&prev_tick_val);
}

void wait_for_frametime_elapsed(float frametime_us)
{
    QueryPerformanceCounter(&cur_tick_val);
    elapsed_usecs.QuadPart = cur_tick_val.QuadPart - prev_tick_val.QuadPart; // elapsed ticks
    elapsed_usecs.QuadPart *= 1000000;                                       // micro_ticks
    elapsed_usecs.QuadPart /= frequency.QuadPart;                            // elapsed ticks

    // Keep checking until you pass the frametime.
    while (elapsed_usecs.QuadPart < frametime_us)
    {
        QueryPerformanceCounter(&cur_tick_val);
        elapsed_usecs.QuadPart = cur_tick_val.QuadPart - prev_tick_val.QuadPart; // elapsed ticks
        elapsed_usecs.QuadPart *= 1000000;                                       // micro_ticks
        elapsed_usecs.QuadPart /= frequency.QuadPart;                            // elapsed ticks
    }

    prev_tick_val.QuadPart = cur_tick_val.QuadPart;
}
