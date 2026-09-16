# RGB LED Color Mixer

## Overview
This project combines three potentiometers with an RGB LED to create a color mixer — each potentiometer independently controls one color channel (Red, Green, Blue) using PWM. It's the first project running multiple analog inputs and multiple PWM outputs simultaneously, building directly on the single-channel version from the potentiometer brightness project.

## What I Learned
- How to scale a known pattern (one analog input → one PWM output) across three independent channels at once
- How color mixing works at the hardware level: combining Red, Green, and Blue at different intensities produces any visible color, the same principle used in screens and stage lighting
- How to organize code with multiple related variables (three pins, three values, three brightness calculations) while keeping it readable
- Reinforced `map()` and `analogWrite()` from Project 6, now applied three times in parallel
- The importance of testing each channel individually before testing combinations, to confirm each one works in isolation before relying on the mix

## Circuit
![Circuit Diagram - All Off](./Circuit%20Diagram%2014.png)
![Circuit Diagram - All Max](./Circuit%20Diagram%2015.png)

- Potentiometer 1 (Red) SIG → Arduino A0
- Potentiometer 2 (Green) SIG → Arduino A1
- Potentiometer 3 (Blue) SIG → Arduino A2
- All potentiometers: VCC → 5V, GND → GND
- RGB LED R pin through a 220Ω resistor → Arduino pin 9
- RGB LED G pin through a 220Ω resistor → Arduino pin 10
- RGB LED B pin through a 220Ω resistor → Arduino pin 11
- RGB LED common pin → Arduino GND

## Components Used
- Arduino Uno
- 3x Potentiometers
- 1x RGB LED
- 3x 220Ω resistors

## Code Summary
```cpp
const int redPotPin = A0;
const int greenPotPin = A1;
const int bluePotPin = A2;

const int redLedPin = 9;
const int greenLedPin = 10;
const int blueLedPin = 11;

void loop() {
  int redValue = analogRead(redPotPin);
  int greenValue = analogRead(greenPotPin);
  int blueValue = analogRead(bluePotPin);

  int redBrightness = map(redValue, 0, 1023, 0, 255);
  int greenBrightness = map(greenValue, 0, 1023, 0, 255);
  int blueBrightness = map(blueValue, 0, 1023, 0, 255);

  analogWrite(redLedPin, redBrightness);
  analogWrite(greenLedPin, greenBrightness);
  analogWrite(blueLedPin, blueBrightness);

  Serial.print("R: "); Serial.print(redBrightness);
  Serial.print("  G: "); Serial.print(greenBrightness);
  Serial.print("  B: "); Serial.println(blueBrightness);

  delay(100);
}
```
*(Full code in `sketch.ino`)*

## Test Results
- All potentiometers at minimum: R:0 G:0 B:0 → LED off
- All potentiometers at maximum: R:255 G:255 B:255 → LED at full combined brightness
- Each channel confirmed to respond independently to its own potentiometer

## Key Takeaway
Once a single-channel pattern (analog input → PWM output) is understood, scaling it to multiple channels is mostly about clean code organization rather than new concepts. This project reinforced that embedded programming often builds complexity by repeating known patterns across more inputs and outputs, not by learning something entirely different each time.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[LDR Night Light](../ldr-night-light) — threshold-based reaction to a single analog sensor.

## Next Project
[Servo Motor Control with Potentiometer](../servo-control) — using `map()` to drive a servo's angle instead of an LED's brightness.
