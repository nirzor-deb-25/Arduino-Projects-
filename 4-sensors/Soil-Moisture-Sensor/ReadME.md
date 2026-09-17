# Soil Moisture Sensor

## Overview
This project simulates a soil moisture sensor using a potentiometer, since Wokwi doesn't have a native soil moisture sensor component. A real soil moisture sensor outputs a variable analog voltage on its AOUT pin depending on how much water is in the soil — the potentiometer's wiper pin mimics that exact behavior, letting you "turn the knob" to simulate wetter or drier soil. An LED lights up as a dry-soil alert when the reading crosses a set threshold.

## What I Learned
- How to substitute an unavailable simulator component with an equivalent one that produces the same type of signal (analog voltage) as the real sensor
- How to use `map()` to convert a raw analog reading (0-1023) into a more human-readable percentage (0-100%)
- How to use `constrain()` to keep a calculated value safely within an expected range
- That sensor calibration matters: the direction of the reading (higher value = wetter or drier) and the exact threshold for "too dry" varies between real sensor modules, so the code needs adjustable constants rather than hardcoded assumptions
- How a single analog pin can drive both a percentage readout and a simple digital alert (LED) at the same time

## Circuit
[Circuit Diagram 1](./Circuit%20Diagram%2029.png)
[Circuit Diagram 2](./Circuit%20Diagram%2030.png)

- Potentiometer VCC → Arduino 5V
- Potentiometer GND → Arduino GND
- Potentiometer SIG (wiper) → Arduino A0
- LED anode → 220Ω resistor → Arduino pin 8
- LED cathode → Arduino GND

## Components Used
- Arduino Uno
- 1x Potentiometer (simulating a soil moisture sensor's analog output)
- 1x LED
- 1x 220Ω Resistor

## Code Summary
```cpp
const int sensorPin = A0;
const int ledPin    = 8;
const int dryThreshold = 500;

int sensorValue = 0;
int moisturePercent = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  moisturePercent = map(sensorValue, 1023, 0, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Raw: ");
  Serial.print(sensorValue);
  Serial.print("  Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  if (sensorValue > dryThreshold) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Soil is DRY - consider watering!");
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(1000);
}
```

## Test Results
- Turning the simulated sensor to its minimum raw value produced a 100% moisture reading with the LED off
- Turning it to maximum raw value (1023) produced a 0% moisture reading, correctly triggering the "Soil is DRY" alert and turning the LED on
- Transitions between wet and dry states were detected reliably each loop cycle

## Key Takeaway
This project highlighted the difference between a sensor's *raw* signal and its *meaningful* value — the interesting engineering work isn't just reading a pin, it's converting that raw number into something useful (a percentage) and deciding what action to take at what threshold. It also showed that when a simulator lacks a specific component, an equivalent analog stand-in can still validate the logic before deploying to real hardware.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[PIR Motion Sensor Alarm](../PIR-motion-sensor-alarm) — event-based digital sensor with state tracking.

## Next Project
_Coming soon._
