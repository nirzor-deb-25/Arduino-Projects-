# Potentiometer Controlling LED Brightness

## Overview
This is the first analog project in the series. A potentiometer provides a variable input (instead of a simple HIGH/LOW), and that value controls the brightness of an LED using PWM. This marks the shift from digital I/O into analog input and PWM output.

## What I Learned
- How `analogRead()` reads a voltage and converts it into a number from 0 to 1023 (10-bit resolution)
- How `analogWrite()` (PWM) simulates a variable output by rapidly switching a pin on and off, using a value from 0 to 255
- Why PWM only works on specific pins (marked with `~` on the Arduino, e.g. 3, 5, 6, 9, 10, 11), and why using a non-PWM pin would silently behave as simple on/off
- How to use `map()` to convert a value from one numeric range (0-1023) to another (0-255)
- How to read and interpret live sensor data through the Serial Monitor while adjusting an input in real time

## Circuit
![Circuit Diagram - Minimum Position](./Circuit%20Diagram%2010.png)
![Circuit Diagram - Maximum Position](./Circuit%20Diagram%2011.png)

- Potentiometer VCC → Arduino 5V
- Potentiometer GND → Arduino GND
- Potentiometer SIG (wiper) → Arduino A0
- LED anode through a 220Ω resistor → Arduino pin 9 (PWM-capable)
- LED cathode → Arduino GND

## Components Used
- Arduino Uno
- 1x Potentiometer
- 1x LED
- 1x 220Ω resistor

## Code Summary
```cpp
const int potPin = A0;
const int ledPin = 9;  // must be a PWM (~) pin

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);               // 0 to 1023
  int brightness = map(potValue, 0, 1023, 0, 255);  // convert to 0-255

  analogWrite(ledPin, brightness);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Brightness: ");
  Serial.println(brightness);

  delay(50);
}
```

## Test Results
- Potentiometer at minimum: Pot = 0, Brightness = 0 (LED off)
- Potentiometer at maximum: Pot = 1023, Brightness = 255 (LED at full brightness)
- LED brightness scaled smoothly between these extremes as the knob was turned

## Key Takeaway
Analog input opens up a whole new category of sensors and controls beyond simple on/off. Converting between different numeric ranges with `map()` is a pattern that will show up constantly with future sensors, and understanding which pins support PWM is essential — using the wrong pin is a very common beginner mistake.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Push-Button Counter with 7-Segment Display](../../01-digital-io/button-counter-7segment) — the last digital I/O project before moving into analog.

## Next Project
[LDR Night Light](../ldr-night-light) — reading real environmental light levels instead of a manually-turned knob.
