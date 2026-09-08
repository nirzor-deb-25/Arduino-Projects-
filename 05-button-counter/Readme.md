# 05 - Push-Button Counter with 7-Segment Display

## Overview
This project combines digital input and output in a more complex way: pressing a pushbutton increments a counter, and the current count (0-9) is shown on a 7-segment display. It's the first project using a multi-segment component instead of a single LED.

## What I Learned
- How a 7-segment display works: it's not one component, but 7 individual LED segments (A-G) arranged to form digits
- The difference between common cathode and common anode 7-segment displays, and why common cathode (HIGH = segment on) was used here
- How to use a 2D lookup table (`digitTable`) to store which segments light up for each digit 0-9, instead of writing separate logic for every number
- How to write a reusable function (`displayDigit()`) that reads the lookup table and updates all 7 segment pins at once
- How to detect a single fresh button press (`LOW` after previously being `HIGH`) instead of continuously reacting while the button is held down
- Why a small delay after a detected press helps with basic debouncing

## Circuit
![Circuit Diagram](./Circuit%20Diagram%209.png)

- Segment A → Arduino pin 2
- Segment B → Arduino pin 3
- Segment C → Arduino pin 4
- Segment D → Arduino pin 5
- Segment E → Arduino pin 6
- Segment F → Arduino pin 7
- Segment G → Arduino pin 8
- COM pin → Arduino GND
- Pushbutton → Arduino pin 9 and GND (using `INPUT_PULLUP`, no external resistor needed)

## Components Used
- Arduino Uno
- 1x 7-segment display (common cathode)
- 1x Pushbutton

## Code Summary
```cpp
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int buttonPin = 9;

const byte digitTable[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  // ... remaining digits 2-9
};

int count = 0;
int lastButtonState = HIGH;

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    count++;
    if (count > 9) count = 0;
    displayDigit(count);
    delay(50); // basic debounce
  }

  lastButtonState = buttonState;
}

void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digitTable[digit][i]);
  }
}
```
*(Full code in `sketch.ino`)*

## Key Takeaway
Controlling several outputs together is much cleaner with a lookup table than with repeated if/else logic — this pattern scales far better as complexity grows. Detecting a single button press (rather than a continuous held state) is also a small but important shift from Project 3, and is the foundation for reliable button-based counting or menu navigation in future projects.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[04b - Traffic Light with Pedestrian Button](../04b-traffic-light-pedestrian-button) — state machines and non-blocking timing.

## Next Project
[06 - Potentiometer Controlling LED Brightness](../06-potentiometer-led) — moving into analog input and PWM output.
