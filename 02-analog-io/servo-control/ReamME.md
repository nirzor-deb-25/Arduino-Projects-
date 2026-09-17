# Servo Motor Control with Potentiometer

## Overview
This project uses a potentiometer to control a servo motor's angle in real time, mapping the pot's analog range (0-1023) to the servo's angular range (0-180°). It's the first project using an external library instead of writing raw pin control logic.

## What I Learned
- How to use the `Servo.h` library instead of manually generating pulse signals
- Working with a library object: creating a `Servo` instance, then calling `.attach()` to bind it to a pin and `.write()` to set its angle
- That the same analog-input-to-mapped-output pattern from earlier projects (potentiometer brightness) applies directly to controlling a completely different type of output — motor angle instead of LED brightness
- Why a small delay after `.write()` helps the servo move smoothly rather than jumping erratically

## Circuit
![Circuit Diagram](./Circuit%20Diagram%2016.png)

- Potentiometer VCC → Arduino 5V
- Potentiometer GND → Arduino GND
- Potentiometer SIG → Arduino A0
- Servo signal (orange) → Arduino pin 9
- Servo power (red) → Arduino 5V
- Servo ground (black/brown) → Arduino GND

## Components Used
- Arduino Uno
- 1x Potentiometer
- 1x Servo motor

## Code Summary
```cpp
#include <Servo.h>

Servo myServo;
const int potPin = A0;
const int servoPin = 9;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);

  myServo.write(angle);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Angle: ");
  Serial.println(angle);

  delay(15);
}
```

## Test Results
- Pot: 562 → Angle: 98
- Pot: 632 → Angle: 111
- Pot: 613 → Angle: 107
- Angle tracked the potentiometer proportionally across its range, confirming the mapping and servo response were both correct

## Key Takeaway
Libraries abstract away complex low-level timing (like the precise pulse widths a servo needs) so the code can focus on logic rather than hardware signal generation. This was also confirmation that a well-understood pattern — reading an analog input and mapping it to an output — generalizes across very different types of outputs.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[RGB LED Color Mixer](../rgb-color-mixer) — multi-channel PWM control.

## Next Project
[DC Motor Speed Control](../dc-motor-speed) — the final analog I/O project before moving into serial communication.
