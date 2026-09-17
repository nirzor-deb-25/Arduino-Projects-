# Serial-Controlled LED

## Overview
This project introduces two-way Serial communication. Instead of only sending data out (as in the previous logging project), the Arduino now reads text commands typed into the Serial Monitor and acts on them — turning an LED on or off based on what was typed.

## What I Learned
- How to check for incoming Serial data with `Serial.available()` before attempting to read it
- How to read a full line of typed input using `Serial.readStringUntil('\n')`, rather than reading one character at a time
- Why `.trim()` is necessary on received input, since typed commands often carry a trailing `\r` (carriage return) that would otherwise break an exact string comparison
- How to write a simple command parser using `if`/`else if` string comparisons, and how to handle unrecognized input gracefully instead of silently ignoring it
- That Serial communication can flow both directions — this is the foundation for any project involving external control, whether from a computer script, another microcontroller, or eventually Bluetooth/WiFi

## Circuit
![Circuit Diagram 1](./Circuit%20Diagram%2022.png)
![Circuit Diagram 2](./Circuit%20Diagram%2023.png)
![Circuit Diagram 3](./Circuit%20Diagram%2024.png)

- LED anode through a 220Ω resistor to Arduino pin 13
- LED cathode to Arduino GND

## Components Used
- Arduino Uno
- 1x LED
- 1x 220Ω resistor

## Code Summary
```cpp
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Type 'on' or 'off' and press Enter to control the LED.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "on") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED turned ON");
    } else if (command == "off") {
      digitalWrite(ledPin, LOW);
      Serial.println("LED turned OFF");
    } else {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }
}
```

## Test Results
- Typing `on` → LED lit up, Serial responded "LED turned ON"
- Typing `off` → LED turned off, Serial responded "LED turned OFF"
- Physical LED state on the board matched each typed command exactly

## Key Takeaway
Reading and parsing incoming Serial text is the same basic pattern used by far more advanced communication setups later on — the only thing that changes is where the commands come from (a person typing, a script, another device) and how many commands need to be handled. Getting comfortable with `Serial.available()`, reading lines, and string comparison here pays off directly in later projects.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Serial Monitor Sensor Logger](../serial-sensor-logger) — one-way Serial output for data logging.

## Next Project
[Ultrasonic Distance Sensor (HC-SR04)](../../04-sensors/ultrasonic-distance) — moving into the Sensors category.
