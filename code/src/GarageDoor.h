#pragma once

#include <HomeSpan.h>
#include "DoorSensor.h"
#include "DoorButton.h"
#include "Timer.h"

// HAP Spec: https://forum.iobroker.net/assets/uploads/files/1634848447889-apple-spezifikation-homekit.pdf
#define DOOR_OPEN 0
#define DOOR_CLOSED 1
#define DOOR_OPENING 2
#define DOOR_CLOSING 3
#define DOOR_STOPPED 4
#define MOVING_TIME_SECONDS 30
#define DOOR_SENSOR_CAPTURE_TIME_SECONDS 10
#define LAST_CHANGED_THRESHOLD_MILLISECONDS 10000

// HomeSpan Service: https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md#garagedooropener-41
struct GarageDoor : Service::GarageDoorOpener
{
    bool isMoving;

    SpanCharacteristic *current;
    SpanCharacteristic *target;
    rlc::DoorSensor &door;
    rlc::DoorButton &button;
    rlc::Timer movingTimer;

    GarageDoor(rlc::DoorSensor &door, rlc::DoorButton &button);
    boolean update();
    void loop();
    void pressButton();
};