#pragma once

#include <Arduino.h>

namespace rlc
{
    class DoorButton
    {
    public:
        DoorButton(const int &pin);
        void push(int push_time_ms = 250);

    private:
        const int _pin;
    };
}
