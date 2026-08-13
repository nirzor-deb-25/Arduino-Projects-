# 04b - Traffic Light with Pedestrian Button

## Overview
This project extends the basic traffic light simulation by adding a pedestrian crossing signal and a pushbutton "beg button" — just like a real crosswalk. Pressing the button requests a Walk signal, which only activates during the vehicle Red phase. This project also introduces a proper state machine using `millis()`, replacing the simple `delay()`-based sequencing from Project 4.

## What I Learned
- How to structure a program as a state machine using `enum` (GREEN, YELLOW, RED) instead of a linear sequence
- How to track elapsed time per state using `millis()`, allowing the button to be checked continuously without freezing the traffic sequence
- How to implement event-driven logic: the button press sets a flag, which is only acted on at the correct moment later (Red phase), rather than immediately
- How to synchronize two independent outputs (vehicle lights and pedestrian signal) based on shared timing logic
- How to create a blinking "walk ending" warning using non-blocking timing inside a specific state

## Circuit
![Circuit Diagram - Traffic Lights](./Circuit%20Diagram%207.png)
![Circuit Diagram - Pedestrian Button](./Circuit%20Diagram%208.png)

- Red LED → 220Ω resistor → pin 10 → GND
- Yellow LED → 220Ω resistor → pin 11 → GND
- Green LED → 220Ω resistor → pin 12 → GND
- Pedestrian Walk LED (green) → 220Ω resistor → pin 8 → GND
- Pedestrian Don't Walk LED (red) → 220Ω resistor → pin 9 → GND
- Pushbutton → pin 2 and GND (using `INPUT_PULLUP`, no external resistor needed)

## Components Used
- Arduino Uno
- 5x LEDs (red, yellow, green, pedestrian green, pedestrian red)
- 5x 220Ω resistors
- 1x Pushbutton

## Code Summary
```cpp
enum LightState { GREEN, YELLOW, RED };
LightState currentState = GREEN;

// Button sets a flag; state machine checks it during RED phase
if (digitalRead(buttonPin) == LOW && !walkRequested) {
  walkRequested = true;
}

// Each state tracks its own elapsed time using millis()
unsigned long elapsed = millis() - stateStartTime;
```
*(Full code in `sketch.ino`)*

## Key Takeaway
This project marks a shift from simple sequential code to a proper state machine — a pattern used constantly in real embedded systems. Combined with non-blocking timing, it allows the Arduino to track multiple things at once (light timing, button presses, blink warnings) without ever freezing, which simple `delay()`-based code cannot do.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[04 - Traffic Light Simulation](../04-traffic-light) — the base version using a simple `delay()` sequence.

## Next Project
[05 - Push-Button Counter with 7-Segment Display](../05-button-counter)
