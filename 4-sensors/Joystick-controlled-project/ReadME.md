# Joystick-Controlled LED Direction Indicator

## Overview
This project uses an analog joystick module to control five LEDs — one for each direction (Up, Down, Left, Right) and one for the joystick's built-in push-button (Select). Moving the joystick lights up the LED matching the direction pushed, and pressing down on the joystick lights up the Select LED. This was the first project combining two analog inputs (X/Y axes) with a digital input (button) in a single sketch.

## What I Learned
- How an analog joystick works internally: it's really just two potentiometers (one per axis) plus a simple pushbutton, all in one module
- How to read two separate analog axes at once and interpret their combined values as directional input
- How to build a "dead zone" around the joystick's resting/center value (~512) so LEDs don't flicker on from tiny amounts of natural drift when the stick isn't being touched
- How to combine `analogRead()` (for direction) and `digitalRead()` with `INPUT_PULLUP` (for the button) in the same loop
- That a joystick module's pin labels (`VERT`, `HORZ`, `SEL`) don't need to match the sketch's variable names — what matters is which physical Arduino pin each one is wired to

## Circuit
[Circuit Diagram 1](./Circuit%20Diagram%2031.png)
[Circuit Diagram 2](./Circuit%20Diagram%2032.png)

- Joystick GND → Arduino GND
- Joystick +5V → Arduino 5V
- Joystick VERT → Arduino A1
- Joystick HORZ → Arduino A0
- Joystick SEL → Arduino pin 2
- LED Up → 220Ω resistor → Arduino pin 8
- LED Down → 220Ω resistor → Arduino pin 9
- LED Left → 220Ω resistor → Arduino pin 10
- LED Right → 220Ω resistor → Arduino pin 11
- LED Select → 220Ω resistor → Arduino pin 12
- All LED cathodes → Arduino GND

## Components Used
- Arduino Uno
- 1x Analog Joystick Module
- 5x LED
- 5x 220Ω Resistor

## Code Summary
```cpp
const int vrxPin = A0;
const int vryPin = A1;
const int swPin  = 2;

const int ledUp     = 8;
const int ledDown    = 9;
const int ledLeft   = 10;
const int ledRight  = 11;
const int ledSelect = 12;

const int centerValue = 512;
const int deadZone    = 150;

void setup() {
  pinMode(swPin, INPUT_PULLUP);
  pinMode(ledUp, OUTPUT);
  pinMode(ledDown, OUTPUT);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledSelect, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(vrxPin);
  int yValue = analogRead(vryPin);
  bool buttonPressed = (digitalRead(swPin) == LOW);

  digitalWrite(ledUp, LOW);
  digitalWrite(ledDown, LOW);
  digitalWrite(ledLeft, LOW);
  digitalWrite(ledRight, LOW);

  if (yValue < centerValue - deadZone) {
    digitalWrite(ledUp, HIGH);
  } else if (yValue > centerValue + deadZone) {
    digitalWrite(ledDown, HIGH);
  }

  if (xValue < centerValue - deadZone) {
    digitalWrite(ledLeft, HIGH);
  } else if (xValue > centerValue + deadZone) {
    digitalWrite(ledRight, HIGH);
  }

  digitalWrite(ledSelect, buttonPressed ? HIGH : LOW);

  delay(100);
}
```

## Test Results
- Pushing the joystick fully up, down, left, and right each correctly lit only the matching LED
- Returning the joystick to center turned all direction LEDs off, confirming the dead zone worked as intended
- Pressing the joystick button reliably lit the Select LED independent of the stick's position

## Key Takeaway
This project showed how to fuse multiple input types — two analog axes and one digital button — into a single coherent output. The dead-zone concept is a pattern that shows up constantly in real joystick-based controls (game controllers, drone remotes, robotic arms) to prevent noise near the resting position from being misread as intentional input.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Soil Moisture Sensor](../Soil-Moisture-Sensor) — analog sensor reading and threshold-based alerts.

## Next Project
_Coming soon._
