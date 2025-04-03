#include "Timer.h"

namespace rlc
{
    Timer::Timer()
    {
        reset();
    }

    void Timer::reset()
    {
        _started_at = micros();
    }

    unsigned long Timer::microseconds()
    {
        return micros() - _started_at;
    }

    unsigned long Timer::seconds()
    {
        return microseconds() / 1000000;
    }
}