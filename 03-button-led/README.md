03 - Button-Controlled LED
Overview

This project introduces real user input to the Arduino. A pushbutton controls an LED directly — pressing the button turns the LED on, releasing it turns the LED off. This is the first project in the series that reads a digital input instead of only writing outputs.

What I Learned
How to read a digital input using digitalRead()
Why a floating input pin is unreliable, and how a pull-up or pull-down resistor fixes that by guaranteeing a definite HIGH or LOW when the button isn't pressed
How to use INPUT_PULLUP to enable the Arduino's internal pull-up resistor, avoiding the need for an external resistor on the button
Why, with INPUT_PULLUP, the logic is inverted: the pin reads HIGH when not pressed and LOW when pressed — because pressing the button connects the pin directly to GND
How to combine a digital input (button) with a digital output (LED) in the same loop()
Circuit

Show Image

LED anode connected through a 220Ω resistor to Arduino pin 13
LED cathode connected to Arduino GND
One leg of the pushbutton connected to Arduino pin 2
The opposite leg of the pushbutton connected to Arduino GND
No external resistor needed for the button — INPUT_PULLUP handles this internally
Components Used
Arduino Uno
1x LED
1x 220Ω resistor
1x Pushbutton
Code Summary
cpp
const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // internal pull-up: pin reads HIGH when not pressed
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    // LOW means the button IS pressed (because of INPUT_PULLUP logic)
    digitalWrite(ledPin, HIGH);
    Serial.println("Button pressed - LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Button released - LED OFF");
  }
}
Key Takeaway

Digital inputs need a defined electrical state at all times — a button by itself can leave a pin "floating," causing unpredictable readings. INPUT_PULLUP solves this using the Arduino's built-in resistor, at the cost of inverted logic (LOW = pressed). This pull-up pattern reappears constantly in future projects involving buttons, switches, and many digital sensors.

Simulation

Built and tested on Wokwi.
