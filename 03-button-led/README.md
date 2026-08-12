# 03 - Button-Controlled LED

## Overview
This project introduces real user input to the Arduino. A pushbutton controls an LED directly — pressing the button turns the LED on, releasing it turns the LED off.

## What I Learned
- How to read a digital input using `digitalRead()`
- Why a floating input pin is unreliable, and how a pull-up resistor fixes that
- How to use `INPUT_PULLUP` to enable the Arduino's internal pull-up resistor
- Why the logic is inverted with `INPUT_PULLUP`: HIGH = not pressed, LOW = pressed
- How to combine a digital input (button) with a digital output (LED)

## Circuit
![Circuit Diagram](./Circuit%20Diagram%205.png)

- LED anode connected through a 220Ω resistor to Arduino pin 13
- LED cathode connected to Arduino GND
- One leg of the pushbutton connected to Arduino pin 2
- The opposite leg of the pushbutton connected to Arduino GND

## Components Used
- Arduino Uno
- 1x LED
- 1x 220Ω resistor
- 1x Pushbutton

## Code Summary
\`\`\`cpp
const int buttonPin = 2;
const int ledPin = 13;
int buttonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Button pressed - LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Button released - LED OFF");
  }
}
\`\`\`

## Key Takeaway
Digital inputs need a defined electrical state at all times. `INPUT_PULLUP` solves the floating-pin problem using the Arduino's built-in resistor, at the cost of inverted logic (LOW = pressed).

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[02 - Blink Without Delay](../02-blink-without-delay)

## Next Project
[04 - Traffic Light Simulation](../04-traffic-light)
