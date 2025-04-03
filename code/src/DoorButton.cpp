#include "DoorButton.h"

namespace rlc
{
    DoorButton::DoorButton(const int &pin) : _pin(pin)
    {
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, LOW);
    }

    void DoorButton::push(int push_time_ms)
    {
        digitalWrite(_pin, HIGH);
        delay(push_time_ms);
        digitalWrite(_pin, LOW);
    }
}