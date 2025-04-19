#include "GarageDoor.h"
#include "Console.h"

GarageDoor::GarageDoor(rlc::DoorSensor &door, rlc::DoorButton &button) : Service::GarageDoorOpener(),
                                                                         door(door),
                                                                         button(button)
{
    // Allowed States: Open, Closed, Opening, Closing, Stopped
    current = new Characteristic::CurrentDoorState(DOOR_CLOSED);

    // Allowed States: Open, Closed
    target = new Characteristic::TargetDoorState(DOOR_CLOSED);

    isMoving = false;
}

boolean GarageDoor::update()
{
    // Home App can control the target value
    //  - need to react to differences in the target value here
    //
    rlc::Console::Info("Home App Request...");
    if (current->getVal() == target->getNewVal())
    {
        // Already at the target value...nothing to move
        //
        return true;
    }

    if (isMoving)
    {
        // Already moving...not allowed to push button until done
        //
        rlc::Console::Error("...already moving!");
        return true;
    }

    switch (target->getNewVal())
    {
    case DOOR_OPEN:
    case DOOR_CLOSED:
        // Need to press the button to move the door
        //
        pressButton();
        isMoving = true;
        movingTimer.reset();
        break;
    }

    return true;
}

void GarageDoor::pressButton()
{
    rlc::Console::Info("...pressing button!");

    button.push(500);
}

void GarageDoor::loop()
{
    door.read();
    if (isMoving && movingTimer.seconds() < MOVING_TIME_SECONDS)
    {
        // Allow the door time to move
        rlc::Console::Verbose("Moving for " + String(movingTimer.seconds()) + " seconds");
    }
    else
    {
        rlc::Console::Verbose("UPDATE: Position: " + String(this->door.position()) + " for " + String(this->door.seconds_at_position()) + " seconds");

        if (isMoving)
        {
            isMoving = false;
            target->setVal(current->getVal());
        }

        if (door.seconds_at_position() > DOOR_SENSOR_CAPTURE_TIME_SECONDS &&
            current->timeVal() > LAST_CHANGED_THRESHOLD_MILLISECONDS)
        {
            if (door.is_closed() && current->getVal() != DOOR_CLOSED)
            {
                // Update the current state and sync the target state
                //
                rlc::Console::Info("Setting to DOOR CLOSED state.");

                current->setVal(DOOR_CLOSED);
                target->setVal(DOOR_CLOSED);
            }
            else if (door.is_opened() && current->getVal() != DOOR_OPEN)
            {
                // Update the current state and sync the target state
                //
                rlc::Console::Info("Setting to DOOR OPEN state.");

                current->setVal(DOOR_OPEN);
                target->setVal(DOOR_OPEN);
            }
        }
    }
}