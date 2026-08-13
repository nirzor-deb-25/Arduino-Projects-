# 04 - Traffic Light Simulation

## Overview
This project simulates a real traffic light using three LEDs (red, yellow, green) controlled in a fixed timed sequence: Red → Green → Yellow → repeat. It's the first project that controls multiple outputs together as a coordinated sequence rather than a single LED in isolation.

## What I Learned
- How to control multiple digital outputs independently using separate pins
- How to structure a sequence of states using `digitalWrite()` and `delay()` in order
- Why real traffic lights use different durations for each light (red/green held longer for safety, yellow kept brief as a short warning)
- How to keep code organized and readable when multiple components are involved, using clear pin naming and comments
- Reinforced understanding of `Serial.println()` for tracking program state during simulation

## Circuit
![Circuit Diagram](./Circuit%20Diagram%206.png)

- Red LED anode through a 220Ω resistor to Arduino pin 10, cathode to GND
- Yellow LED anode through a 220Ω resistor to Arduino pin 11, cathode to GND
- Green LED anode through a 220Ω resistor to Arduino pin 12, cathode to GND

## Components Used
- Arduino Uno
- 3x LEDs (red, yellow, green)
- 3x 220Ω resistors

## Code Summary
\`\`\`cpp
const int redPin = 10;
const int yellowPin = 11;
const int greenPin = 12;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(redPin, HIGH);
  Serial.println("RED - Stop");
  delay(3000);
  digitalWrite(redPin, LOW);

  digitalWrite(greenPin, HIGH);
  Serial.println("GREEN - Go");
  delay(3000);
  digitalWrite(greenPin, LOW);

  digitalWrite(yellowPin, HIGH);
  Serial.println("YELLOW - Caution");
  delay(1000);
  digitalWrite(yellowPin, LOW);
}
\`\`\`

## Key Takeaway
Coordinating multiple outputs is really just running multiple single-LED patterns in a defined order. This project used `delay()` deliberately since the goal was sequencing logic, not multitasking — but the non-blocking pattern from Project 2 (`millis()`) will become necessary again as soon as a future project needs to do something else (like check a button) while the sequence is running.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[03 - Button-Controlled LED](../03-button-led) — reading digital input with a pushbutton.

## Next Project
[05 - Push-Button Counter with 7-Segment Display](../05-button-counter) — combining input and output with a more complex display component.
