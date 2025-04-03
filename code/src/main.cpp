#include "GarageDoor.h"
#include "DoorSensor.h"
#include "DoorButton.h"
#include "Console.h"
#include "SpanRollback.h"

#define CONTROL_PIN 18
#define PIN_STATUS_LED 5
#define DOOR_SENSOR 19
#define DOOR_BUTTON 17

rlc::DoorSensor door(DOOR_SENSOR);
rlc::DoorButton button(DOOR_BUTTON);

void setup()
{
  Serial.begin(9600);

  rlc::Console::setVerbose(false);
  rlc::Console::setInfo(true);
  rlc::Console::setError(true);

  // HomeSpan setup
  homeSpan.setPairingCode("11122333");   // security code needed when pairing
  homeSpan.setControlPin(CONTROL_PIN);   // button to toggle between modes
  homeSpan.setStatusPin(PIN_STATUS_LED); // indicator of status / mode
  homeSpan.enableAutoStartAP();          // enable access point if no wifi credentials found
  homeSpan.enableOTA();                  // enable over-the-air updates
  homeSpan.enableWatchdog(180);          // reboot if poll method not called within timout specified

  // Initialize home span
  homeSpan.begin(Category::GarageDoorOpeners, "Garage Door");

  // Create new HAP accessory
  new SpanAccessory();
  {
    // Accessory Information Service
    new Service::AccessoryInformation();
    {
      new Characteristic::Identify();
      new Characteristic::Model("HomeSpan - ESP32");
      new Characteristic::FirmwareRevision("1.0.0");
    }

    // Garage Door Service
    new GarageDoor(door, button);
  }

  // For automatic rollbacks
  homeSpan.markSketchOK();
}

void loop()
{
  // Read sensor, check for HAP requests...
  homeSpan.poll();
}