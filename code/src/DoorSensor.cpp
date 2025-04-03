#include "DoorSensor.h"

namespace rlc
{
    DoorSensor::DoorSensor(const int &pin) : _pin(pin)
    {
        pinMode(_pin, INPUT_PULLUP);
    }

    void DoorSensor::read()
    {
        int new_door_sensor_val = digitalRead(_pin);
        if (new_door_sensor_val != _current_val)
        {
            // Position has changed...reset the timer
            _val_timer.reset();
        }
        _current_val = new_door_sensor_val;
    }

    bool DoorSensor::is_closed()
    {
        return _current_val == LOW;
    }

    bool DoorSensor::is_opened()
    {
        return _current_val == HIGH;
    }

    const char *DoorSensor::position()
    {
        const char *pos = _current_val == LOW ? "CLOSED" : "OPENED";
        return pos;
    }

    unsigned long DoorSensor::seconds_at_position()
    {
        return _val_timer.seconds();
    }
}