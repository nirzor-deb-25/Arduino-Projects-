# LDR (Light Sensor) Night Light

## Overview
This project uses a light sensor module to automatically turn an LED on in the dark and off in bright conditions, like a real night light. It introduces reading real environmental data and reacting to it with threshold-based logic.

## What I Learned
- How a photoresistor (LDR) changes resistance based on light level, and how that's converted into a readable analog voltage
- How to use a pre-built light sensor module (VCC, GND, AO, DO pins) instead of building a voltage divider manually
- The difference between the module's AO (Analog Output, variable) and DO (Digital Output, simple HIGH/LOW threshold set on the module itself)
- How to implement threshold-based decision logic: comparing a live sensor reading against a fixed value to trigger an action
- That a sensor's raw reading direction (higher value = brighter or darker) depends on the specific wiring/module, and must be confirmed by testing rather than assumed

## Circuit
![Circuit Diagram - Bright Light](./Circuit%20Diagram%2012.png)
![Circuit Diagram - Darkness](./Circuit%20Diagram%2013.png)

- Light sensor module VCC → Arduino 5V
- Light sensor module GND → Arduino GND
- Light sensor module AO → Arduino A0
- LED anode through a 220Ω resistor → Arduino pin 9
- LED cathode → Arduino GND

## Components Used
- Arduino Uno
- 1x Light sensor module (LDR-based, with AO/DO output)
- 1x LED
- 1x 220Ω resistor

## Code Summary
```cpp
const int ldrPin = A0;
const int ledPin = 9;
const int darkThreshold = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(ldrPin);

  Serial.print("Light level: ");
  Serial.println(lightLevel);

  if (lightLevel > darkThreshold) {
    digitalWrite(ledPin, HIGH); // dark enough — turn on the night light
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(200);
}
```

## Test Results
- At 550 lux (bright): Light level = 237 → below threshold → LED off
- At 0.1 lux (dark): Light level = 1015 → above threshold → LED on
- Confirms higher analog reading corresponds to darker conditions with this module's wiring

## Key Takeaway
Threshold-based logic — comparing a live sensor reading to a fixed value — is one of the most common patterns in embedded systems. This project also reinforced that assumptions about sensor behavior (which direction values move) should always be verified through testing, not assumed from datasheets alone.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Potentiometer Controlling LED Brightness](../potentiometer-led-brightness) — manually-controlled analog input.

## Next Project
[RGB LED Color Mixer](../rgb-color-mixer) — controlling three PWM channels at once.
