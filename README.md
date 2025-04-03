# ESP32 Smart Garage Door

## Purpose
Ever come home to find your garage door has been opened while you were gone? This project converts an existing garage door into a "smart" garage door by adding the following features:

1. Open/Closed Indicator
2. Remote Door Switch

These features are provided via an integration into Apple HomeKit (a.k.a. Home App). Here are a few screenshots from the Apple Home app:

<img alt="Status Page" src="imgs/apple_home_status_page.jpeg" width="200">
<img alt="Toggle Page" src="imgs/apple_home_toggle.jpeg" width="200">

## Circuit Diagram
<img alt="Circuit Diagram" src="imgs/circuit_diagram.png" width="500">

The ESP32 has the following interactions:

- **Garage Door Magnetic Sensor** is a magnetic reed switch in a NC (normally closed) configuration. This ensures if the wire gets cut, the sensor faults to "open" and will send alerts.
- **Garage Door Button** are two wires that connect to the garage door motor unit. This only works on units that provide two terminals that when shorted together starts the door moving. One of the wires will be at a higher voltage and it IS IMPORTANT THAT ONE IS CONNECTED to the collector of the driving transistor.
- **Status LED** is an indicator used by the HomeSpan code. It flashes based on mode and status. Refer to <a href="https://github.com/HomeSpan/HomeSpan">HomeSpan documentation</a> for details.
- **Control Button** is used to manually toggle the device into various configuration modes. Refer to <a href="https://github.com/HomeSpan/HomeSpan">HomeSpan documentation</a>.


## Parts
- [ESP32 Board + Breakout Kit](https://www.amazon.com/dp/B0C8DBN29X)
- [Project Box](https://www.amazon.com/dp/B083H9FNRT)
- [Magnetic Switch](https://www.amazon.com/dp/B085XQLQ3N)
- [Control Button](https://www.amazon.com/DAOKI-Miniature-Momentary-Tactile-Quality/dp/B01CGMP9GY)
- [Status LED](https://www.amazon.com/MCIGICM-Circuit-Assorted-Science-Experiment/dp/B07PG84V17)
- [LED Resistor (220ohm)](https://www.amazon.com/California-JOS-Resistance-CJ50-004-220/dp/B0BDKQSZHM)
- [2N2222 Transistor](https://www.amazon.com/ALLECIN-2N2222-Amplifier-Transistors-Transistor/dp/B0CBK1T5FQ)
- [Base Resistor (1kohm)](https://www.amazon.com/California-JOS-Carbon-Resistor-Tolerance/dp/B0BR66ZN6B)
- [Wire](https://www.amazon.com/dp/B0DP3TGB3W)

## Code
The code for this project is in the "code" directory. It consists of the following files in the `src` directory:

- `Console.cpp` & `Console.h` - Wrapper around `Serial.print` functions to control when to print Error, Info, and Verbose message.
- `DoorButton.cpp` & `DoorButton.h` - Wrapper around the "Garage Door Button" features.
- `DoorSensor.cpp` & `DoorSensor.h` - Wrapper around the "Garagae Door Magnetic Sensor" features.
- `GarageDoor.cpp` & `GarageDoor.h` - Wrapper around the high-level garage door features. Provides the integration with Apple Home via <a href="https://github.com/HomeSpan/HomeSpan">HomeSpan</a>.
- `main.cpp` - Entry point for the application. Provides the setup and main loop.
- `Timer.cpp` & `Timer.h` - Wrapper around a simple timer features that is used in multiple places.

Other files of interest are:
- `platformio.ini` - This configures the board, framework, and external dependencies.

## Connect to WiFi
After installing and powering on the device:

1. Click and hold the "control button" until the "status LED" flashed rapidly.
2. Release the "control button" and you should be in "configuration mode" with the "status LED" blink once.
3. Press and release the "control button" and the "status LED" should blink twice.
4. Press and release the "control button" and the "status LED" should blink three times.
5. Press and HOLD the "control button" to enter launch HomeSpan's temporary WiFi network.
6. Use your iPhone to connect to the HomeSpan WiFi access point.
7. Configure your WiFi SSID and password.
8. Enter a pairing code (you will need this when you pair). The default is 1112-2333.

For more info: <a href="https://github.com/HomeSpan/HomeSpan/blob/master/docs/UserGuide.md">HomeSpan User Guide</a>

## Pairing to Home App
After the device has WiFi connectivity:

1. On your iPhone open the Home App.
2. Select the "Add Accessory" or the "+" option in the upper-right corner.
3. Follow the directions in Home App. When asked, enter the pairing code.

For more info: <a href="https://github.com/HomeSpan/HomeSpan/blob/master/docs/UserGuide.md">HomeSpan User Guide</a>

## Over-The-Air Updates
Once installed, the device can receive over-the-air (OTA) updates. The `main.cpp` file enables this along with automated rollback if the new release doesn't make it through the setup phase. To peform an OTA update in VS Code:

1. Determine the IP Address of the device.
2. In the `platformio.ini` file uncomment the `upload_protocol` and `upload_flags` lines.
3. At the bottom, click the "Set upload/monitor/test port" button. Select "Custom..." and enter the IP Address.

The upload should now be pushed OTA to the device.