# PIR Motion Sensor Alarm (HC-SR501)

## Overview
This project uses an HC-SR501 PIR (Passive Infrared) motion sensor to detect movement and trigger an alarm. Unlike the ultrasonic sensor (which actively measures distance) or the DHT22 (which reads analog-style environmental data), the PIR sensor works passively — it detects changes in infrared radiation caused by a warm body moving through its field of view, and simply outputs HIGH or LOW depending on whether motion is present.

## What I Learned
- How a PIR sensor differs from other sensors: it doesn't measure a continuous value, it just reports a binary motion/no-motion state
- PIR sensors need a warm-up/calibration period (a few seconds) after power-on before readings stabilize
- How to combine a digital sensor input with two separate outputs (LED + buzzer) that react to the same trigger
- How to track state changes using a variable (`pirState`) so the alarm only prints "Motion detected!" once per event, instead of spamming the serial monitor every loop
- How to use `tone()` and `noTone()` to control a buzzer instead of just switching it on/off

## Circuit
[Circuit Diagram](./Circuit_Diagram_27.png)
[Circuit Diagram](./Circuit_Diagram_28.png)

- PIR VCC → Arduino 5V
- PIR GND → Arduino GND
- PIR OUT → Arduino pin 2
- Buzzer + → Arduino pin 8
- Buzzer – → Arduino GND
- LED anode → 220Ω resistor → Arduino pin 13
- LED cathode → Arduino GND

## Components Used
- Arduino Uno
- 1x HC-SR501 PIR Motion Sensor
- 1x Buzzer
- 1x LED
- 1x 220Ω Resistor

## Code Summary
```cpp
const int pirPin    = 2;
const int buzzerPin = 8;
const int ledPin    = 13;

int pirState = LOW;
int val = 0;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(3000); // let PIR sensor settle/calibrate
}

void loop() {
  val = digitalRead(pirPin);

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    if (pirState == HIGH) {
      Serial.println("Motion ended.");
      pirState = LOW;
    }
  }

  delay(100);
}
```

## Test Results
- Sensor correctly triggered the LED and buzzer immediately when motion was simulated
- Serial monitor logged clean "Motion detected!" / "Motion ended." transitions with no repeated spam during continuous motion
- No false triggers observed after the initial calibration delay

## Key Takeaway
This was the first project in the Sensors category using a purely digital, event-based sensor rather than one requiring timing (HC-SR04) or a data protocol (DHT22). It introduced the idea of state tracking — reacting only to *changes* in a signal rather than reading it continuously — which is a pattern that shows up constantly in alarm systems, buttons, and event-driven logic.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[DHT22 Temperature & Humidity Sensor](../DHT22-temperature-humidity) — library-based sensor reading.

## Next Project
_Coming soon._
