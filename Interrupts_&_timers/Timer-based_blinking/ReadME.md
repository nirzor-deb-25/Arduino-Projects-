# Timer-Based Blinking (millis-based)

## Overview
This project revisits non-blocking LED blinking using `millis()`, now framed explicitly as a software timing technique within the Interrupts & Timers category. It uses the same core pattern introduced in the early "Blink Without Delay" project, reinforced here as a foundation before moving into hardware interrupts and rotary encoders.

## What I Learned
- Reinforced the `millis()`-based non-blocking timing pattern: tracking elapsed time with a `previousMillis` variable instead of freezing execution with `delay()`
- The distinction between a software timer (checking elapsed time each loop cycle, as done here) and a hardware timer/interrupt (where the microcontroller itself triggers an event at a precise interval, independent of the main loop) — this project uses the software approach
- How to structure clearly named constants (`LED_PIN`, `BLINK_INTERVAL`) and state variables (`ledState`, `previousMillis`) for readable, maintainable timing code
- Why this pattern is the necessary foundation before working with true hardware interrupts: understanding software-based timing makes the value of hardware timers much clearer by comparison

## Circuit
![Circuit Diagram](./Circuit%20Diagram%2037.png)

- LED anode through a resistor to Arduino pin 13
- LED cathode to Arduino GND

## Components Used
- Arduino Uno
- 1x LED
- 1x Resistor

## Code Summary
```cpp
const int LED_PIN = 13;
const long BLINK_INTERVAL = 500;

int ledState = LOW;
unsigned long previousMillis = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= BLINK_INTERVAL) {
    previousMillis = currentMillis;

    ledState = (ledState == LOW) ? HIGH : LOW;
    digitalWrite(LED_PIN, ledState);
  }
}
```

## Test Results
- LED blinked reliably at the configured 500ms interval, confirmed visually in simulation

## Key Takeaway
This project cemented the software-timer pattern as second nature before moving on to true hardware interrupts (`attachInterrupt()`) and timer-driven designs later in this stage. The core idea — comparing elapsed time against a threshold every loop cycle — is the same mental model that scales up to far more complex multitasking behavior in later, more advanced projects.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[DHT11/DHT22 Temperature & Humidity Sensor](../../04-sensors/dht-temp-humidity) — library-based multi-value sensor reading.

## Next Project
[Button Interrupt (attachInterrupt)](../button-interrupt) — moving from software timing into true hardware interrupts.
