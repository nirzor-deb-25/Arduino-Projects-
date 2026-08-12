# 01 - LED Blink

## Overview
This is the first project in my Arduino learning journey. It demonstrates the most basic digital output operation: turning an LED on and off at a fixed interval using `digitalWrite()` and `delay()`.

## What I Learned
- How to set a pin as `OUTPUT` using `pinMode()`
- How to turn a pin `HIGH` (5V) or `LOW` (0V) using `digitalWrite()`
- How `delay()` pauses program execution for a set number of milliseconds
- Basic LED circuit wiring: current-limiting resistor, anode/cathode orientation, and completing the circuit back to GND

## Circuit

![Circuit Diagram](./Circuit%20Diagram%203.png)

- LED anode connected through a 220Ω resistor to Arduino pin 13
- LED cathode connected to Arduino GND

## Components Used
- Arduino Uno
- 1x LED
- 1x 220Ω resistor

## Code Summary
```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
```

## Key Takeaway
`delay()` blocks the entire program while it waits — nothing else can run during that pause. This limitation is addressed in the next project using `millis()` instead.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Next Project
[02 - Blink Without Delay](../02-blink-without-delay) — same LED blink, but using `millis()` so the program never freezes.
