#pragma once

#include <Arduino.h>

namespace rlc
{
    class Timer
    {
    public:
        Timer();
        void reset();
        unsigned long seconds();
        unsigned long microseconds();

    private:
        unsigned long _started_at = micros();
    };
}
