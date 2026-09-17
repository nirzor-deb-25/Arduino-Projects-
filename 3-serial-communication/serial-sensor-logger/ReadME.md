# Serial Monitor Sensor Logger

## Overview
This project treats Serial output as an actual deliverable rather than just a debugging tool. A potentiometer stands in for a generic analog sensor, and its readings are logged once per second in clean, timestamped CSV format — output structured enough to be copied directly into a spreadsheet for analysis.

## What I Learned
- How to structure Serial output as valid CSV (comma-separated values) with a header row, so it can be opened directly in Excel or Google Sheets
- How to use `millis()` for timestamping each log entry, a different use case than the non-blocking timing pattern from earlier projects (recording *when* something happened, not just *how often* to act)
- How to convert a raw ADC reading (0-1023) into its actual voltage equivalent (0-5V) using `sensorValue * (5.0 / 1023.0)`
- How `Serial.println(value, 2)` formats a float to a fixed number of decimal places for consistent, readable output
- That logging on a schedule with `millis()` (rather than `delay()`) keeps the loop free to do other work simultaneously

## Circuit
![Circuit Diagram - Minimum](./Circuit%20Diagram%2020.png)
![Circuit Diagram - Maximum](./Circuit%20Diagram%2021.png)

- Potentiometer VCC → Arduino 5V
- Potentiometer GND → Arduino GND
- Potentiometer SIG → Arduino A0

## Components Used
- Arduino Uno
- 1x Potentiometer (standing in for a generic analog sensor)

## Code Summary
```cpp
const int sensorPin = A0;
unsigned long lastLogTime = 0;
const long logInterval = 1000; // log once per second

void setup() {
  Serial.begin(9600);
  Serial.println("Timestamp(ms),SensorValue,VoltageEquivalent");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastLogTime >= logInterval) {
    lastLogTime = currentTime;

    int sensorValue = analogRead(sensorPin);
    float voltage = sensorValue * (5.0 / 1023.0);

    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(sensorValue);
    Serial.print(",");
    Serial.println(voltage, 2);
  }
}
```

## Test Results
- Sensor at minimum: `36000,0,0.00` — timestamp, raw value 0, voltage 0.00V
- Sensor at maximum: `42000,1023,5.00` — raw value 1023, voltage 5.00V
- Timestamps incremented in exact 1000ms steps, confirming reliable non-blocking interval logging

## Key Takeaway
Serial output can be more than a debugging afterthought — with a small amount of structure (headers, consistent delimiters, fixed decimal formatting) it becomes usable data output. This distinction between "print for me to glance at" and "print for a program or spreadsheet to consume" is a useful habit for any project that needs to log or export data.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Stepper Motor Speed Control](../../02-analog-io/stepper-motor-speed-control) — the final analog I/O project.

## Next Project
[Serial-Controlled LED](../serial-controlled-led) — parsing incoming Serial commands to control hardware.
