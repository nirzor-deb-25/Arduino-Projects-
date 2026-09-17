# Stepper Motor Speed Control (Adapted from DC Motor Speed Control)

## Overview
This project was originally planned as DC motor speed control, but the Wokwi environment used didn't include a DC motor or motor driver component. It was adapted to use a Bipolar Stepper Motor instead — a closely related, arguably more relevant embedded systems component — controlled by a potentiometer to vary rotation speed.

## What I Learned
- How stepper motors differ fundamentally from DC motors and servos: they move in precise, fixed increments ("steps") rather than spinning continuously or holding a fixed angle
- How to use the `Stepper.h` library, specifically `setSpeed()` (sets RPM) and `step()` (commands a number of steps)
- That adapting a project when the ideal component isn't available is a normal and valuable part of real engineering work, not a failure of the original plan
- Reapplying the analog-input-to-mapped-output pattern once again, this time mapping potentiometer position to motor RPM instead of brightness or angle

## Circuit
![Circuit Diagram - Low Speed](./Circuit%20Diagram%2019.png)
![Circuit Diagram - High Speed](./Circuit%20Diagram%2018.png)

- Potentiometer VCC → Arduino 5V
- Potentiometer GND → Arduino GND
- Potentiometer SIG → Arduino A0
- Stepper motor coil pins → Arduino pins 8, 9, 10, 11

## Components Used
- Arduino Uno
- 1x Potentiometer
- 1x Bipolar Stepper Motor

## Code Summary
```cpp
#include <Stepper.h>

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

const int potPin = A0;

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int motorSpeed = map(potValue, 0, 1023, 1, 20); // RPM range 1-20

  myStepper.setSpeed(motorSpeed);
  myStepper.step(stepsPerRevolution / 20);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Speed (RPM): ");
  Serial.println(motorSpeed);
}
```

## Test Results
- Potentiometer at minimum: Pot = 0, Speed = 1 RPM, ~89 steps taken over the test period
- Potentiometer at maximum: Pot = 1023, Speed = 20 RPM, ~798 steps taken over a similar period
- Higher pot values consistently produced a much higher step count, confirming speed control was working correctly

## Key Takeaway
Not every planned component is always available, and adapting to a related alternative — while keeping the core learning goal (PWM-adjacent variable control of a motor) intact — is a realistic and valuable skill. Stepper motors also introduced a genuinely different control model (discrete steps vs. continuous output) compared to every previous project in this series.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Servo Motor Control with Potentiometer](../servo-control) — angle-based control using the Servo library.

## Next Project
[Serial Monitor Sensor Logger](../../03-serial-communication/serial-sensor-logger) — moving into serial communication and debugging.
