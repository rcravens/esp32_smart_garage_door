#pragma once

#include <Arduino.h>
#include "Timer.h"

namespace rlc
{
    class DoorSensor
    {
    public:
        DoorSensor(const int &pin);
        void read();
        bool is_closed();
        bool is_opened();
        int value() { return _current_val; }
        const char *position();
        unsigned long seconds_at_position();

    private:
        const int _pin;
        int _current_val = LOW; // Closed
        Timer _val_timer;
    };
}
