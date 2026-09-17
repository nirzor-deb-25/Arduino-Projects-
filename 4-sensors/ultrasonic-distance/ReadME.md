# Ultrasonic Distance Sensor (HC-SR04)

## Overview
This project uses an HC-SR04 ultrasonic sensor to measure distance by timing how long it takes for a sent pulse to bounce off an object and return. It's the first project in the Sensors category, and the first to measure a physical quantity by timing a signal rather than reading a voltage.

## What I Learned
- How the HC-SR04 works: a short trigger pulse sends an ultrasonic ping, and the echo pin stays HIGH for exactly as long as it takes the pulse to travel to an object and back
- How to use `pulseIn()` to measure the duration a pin stays in a given state, in microseconds
- How to use `delayMicroseconds()` for extremely short, precise timing (needed for the ~10 microsecond trigger pulse, far shorter than `delay()` could handle accurately)
- How to convert a raw time measurement into a real-world physical quantity using a formula based on the speed of sound (343 m/s, or 0.0343 cm/microsecond), dividing by 2 since the pulse travels the distance twice (there and back)
- That some sensors require a calculation to become meaningful, rather than a simple `map()` or direct reading

## Circuit
![Circuit Diagram](./Circuit%20Diagram%2025.png)

- HC-SR04 VCC → Arduino 5V
- HC-SR04 GND → Arduino GND
- HC-SR04 TRIG → Arduino pin 9
- HC-SR04 ECHO → Arduino pin 10

## Components Used
- Arduino Uno
- 1x HC-SR04 Ultrasonic Distance Sensor

## Code Summary
```cpp
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(200);
}
```

## Test Results
- Sensor produced consistent readings around 401 cm with only minor natural fluctuation (401.14 → 401.16 cm), confirming stable and accurate timing-based measurement

## Key Takeaway
Not all sensors give directly usable values — some, like the HC-SR04, require converting a raw measurement (time) into a meaningful physical unit (distance) via a known formula. This is a different category of sensor work than the analog voltage-based sensors used earlier, and a pattern that reappears with other timing-based or physics-based sensors.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Serial-Controlled LED](../../03-serial-communication/serial-controlled-led) — the last Serial Communication project.

## Next Project
[DHT11/DHT22 Temperature & Humidity Sensor](../dht-temp-humidity) — library-based sensor reading.
