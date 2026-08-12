# 02 - Blink Without Delay (millis())

## Overview
This project takes the basic LED blink from Project 1 and rebuilds it using `millis()` instead of `delay()`. The LED still blinks every second, but this time the rest of the program is never blocked while waiting — a core habit for any real embedded system.

## What I Learned
- How `millis()` returns the number of milliseconds since the Arduino started running, acting like a stopwatch that never stops
- How to track elapsed time using a `previousMillis` variable instead of freezing the program with `delay()`
- Why `delay()` blocks the entire loop, and why that becomes a problem once a project needs to do more than one thing at a time (e.g. blink an LED while also reading a button or sensor)
- How to toggle a variable's state (`HIGH`/`LOW`) using a simple `if/else` check
- Using `Serial.println()` to monitor what the program is doing in real time via the Serial Monitor

## Circuit
![Circuit Diagram](./Circuit%20Diagram%204.png)

- LED anode connected through a 220Ω resistor to Arduino pin 13
- LED cathode connected to Arduino GND
- Same circuit as Project 1 — only the code changed

## Components Used
- Arduino Uno
- 1x LED
- 1x 220Ω resistor

## Code Summary
```cpp
const int ledPin = 13;
int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    ledState = (ledState == LOW) ? HIGH : LOW;

    digitalWrite(ledPin, ledState);
    Serial.println(ledState == HIGH ? "LED ON" : "LED OFF");
  }

  // other code could run freely here without being blocked
}
```

## Key Takeaway
`millis()` lets the Arduino "check the time" without ever pausing the program. This non-blocking pattern is one of the most important habits in embedded programming — it's what makes it possible to blink an LED, read a sensor, and check a button all in the same loop, at the same time.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[01 - LED Blink](../01-led-blink) — the same blink, done with `delay()`, before learning why that's limiting.

## Next Project
[03 - Button-Controlled LED](../03-button-led) — introducing real user input with a pushbutton.
