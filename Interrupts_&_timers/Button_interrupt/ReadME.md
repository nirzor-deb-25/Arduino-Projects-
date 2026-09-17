# Button Interrupt (attachInterrupt)

## Overview
This project introduces hardware interrupts using `attachInterrupt()`. Instead of continuously checking the button's state inside `loop()` (a technique called polling), the Arduino is told to react the instant the button is pressed — pausing whatever `loop()` is doing to run a special function called an Interrupt Service Routine (ISR). This is the first project in the Interrupts & Timers stage, and it changes how the whole program is structured: `loop()` no longer needs to know or care about the button at all.

## What I Learned
- The difference between polling (checking a pin's state every loop cycle) and interrupts (being notified the instant a pin's state changes)
- That on an Arduino Uno, only pins 2 and 3 support hardware interrupts via `attachInterrupt()` — this is a hardware limitation of the chip, not something configurable in code
- Why interrupt-related variables must be declared `volatile`, so the compiler doesn't optimize away changes that happen unexpectedly from inside an ISR
- Why debouncing matters even more with interrupts than with polling: a single mechanical button press can trigger the interrupt multiple times within milliseconds due to physical contact bounce
- Why `Serial.print()` and other slow operations should be avoided inside an ISR — the ISR should do the minimum work possible (update a variable) and let `loop()` handle anything slower, like printing

## Circuit
[Circuit Diagram](./Circuit%20Diagram%2036.png)

- Button (one leg) → Arduino pin 2
- Button (other leg) → Arduino GND
- LED anode → 220Ω resistor → Arduino pin 13
- LED cathode → Arduino GND

## Components Used
- Arduino Uno
- 1x Push Button
- 1x LED
- 1x 220Ω Resistor

## Code Summary
```cpp
const int buttonPin = 2;
const int ledPin = 13;

volatile bool ledState = LOW;
volatile unsigned long pressCount = 0;
volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
}

void loop() {
  digitalWrite(ledPin, ledState);

  static unsigned long lastReported = 0;
  if (pressCount != lastReported) {
    Serial.print("Button pressed! Count: ");
    Serial.println(pressCount);
    lastReported = pressCount;
  }
}

void handleButtonPress() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime > debounceDelay) {
    ledState = !ledState;
    pressCount++;
    lastInterruptTime = currentTime;
  }
}
```

## Test Results
- Each button press toggled the LED and incremented the press count exactly once, with no double-counting
- Serial output printed a clean, incrementing sequence (Count: 1, 2, 3, 4...) matching the number of actual clicks
- Rapid repeated clicking was correctly filtered by the debounce window, with no extra counts registered per press

## Key Takeaway
This was the first project where `loop()` was fully decoupled from an input — the button press is caught immediately by the ISR regardless of what else the program might be doing. This pattern becomes essential in more complex projects where `loop()` needs to run longer tasks (sensor readings, display updates, network calls) without risking a missed button press in between.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[RTC + LCD Alarm Clock](../RTC-LCD-Alarm-Clock) — combining I2C devices, timing logic, and physical I/O.

## Next Project
_Coming soon._
