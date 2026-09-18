# Rotary Encoder

## Overview
This project reads a rotary encoder (KY-040 style module) to detect rotation direction and count discrete "steps" as the knob turns, plus its built-in pushbutton for resetting the counter. Unlike a potentiometer's continuous analog value, an encoder gives quantized pulses and requires comparing two signals to determine direction.

## What I Learned
- How quadrature encoding works: comparing the relative states of two signals (CLK and DT) to determine both that movement occurred and which direction it happened in
- How to detect a change in the CLK signal as a "step" event, then check DT's state at that exact moment to resolve clockwise vs counter-clockwise rotation
- How to combine a rotational input with a built-in pushbutton (SW pin) on the same module, applying the edge-detection and debounce patterns from earlier button projects
- That this same direction-sensing principle extends to far more advanced applications, such as precise position feedback on motors

## Circuit
![Circuit Diagram 1](./Circuit%20Diagram%2038.png)
![Circuit Diagram 2](./Circuit%20Diagram%2039.png)

- Encoder VCC → Arduino 5V
- Encoder GND → Arduino GND
- Encoder CLK → Arduino pin 2
- Encoder DT → Arduino pin 3
- Encoder SW → Arduino pin 4

## Components Used
- Arduino Uno
- 1x Rotary Encoder module (KY-040 style, with built-in pushbutton)

## Code Summary
```cpp
const int clkPin = 2;
const int dtPin = 3;
const int swPin = 4;

int counter = 0;
int lastClkState;

void setup() {
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  Serial.begin(9600);
  lastClkState = digitalRead(clkPin);
}

void loop() {
  int currentClkState = digitalRead(clkPin);

  if (currentClkState != lastClkState) {
    if (digitalRead(dtPin) != currentClkState) {
      counter++; // clockwise
    } else {
      counter--; // counter-clockwise
    }
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  lastClkState = currentClkState;

  if (digitalRead(swPin) == LOW) {
    Serial.println("Button pressed - Reset counter");
    counter = 0;
    delay(300);
  }
}
```

## Test Results
- Turning the knob one direction: Counter incremented (1 → 2)
- Turning the opposite direction: Counter decremented (2 → 1 → 0)
- Pressing the built-in button: printed "Button pressed - Reset counter" and reset the count to 0

## Key Takeaway
Reading two related signals together to extract more information than either provides alone — direction, not just movement — is a pattern that reappears throughout embedded systems, especially anywhere precise position or motion tracking is needed. This project also reinforced that modules often bundle multiple input types (rotation + button) that can be handled with techniques already learned individually.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Timer-Based Blinking (millis-based)](../timer-based-blinking) — software timing fundamentals.

## Next Project
[RFID Door Lock (SPI)](../../07-communication-protocols/rfid-door-lock) — moving into the Communication Protocols category.
