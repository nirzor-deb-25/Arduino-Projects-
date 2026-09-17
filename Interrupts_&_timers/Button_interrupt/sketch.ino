// Button Interrupt (attachInterrupt)
// Components: Arduino Uno, Push Button, LED, Resistor
//
// Instead of checking the button's state every loop() cycle (polling),
// this uses a hardware interrupt so the Arduino reacts to a press the
// instant it happens - even if the main loop is busy doing something else.

const int buttonPin = 2;  // Must be pin 2 or 3 on an Uno for attachInterrupt
const int ledPin = 13;

volatile bool ledState = LOW;
volatile unsigned long pressCount = 0;

volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200; // milliseconds

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Button interrupt demo starting...");

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
}

void loop() {
  digitalWrite(ledPin, ledState);

  static unsigned long lastReported = 0;
  if (pressCount != lastReported) {
    Serial.print("Button pressed! Count: ");
    Serial.println(pressCount);
    lastReported = pressCount;
  }
}

void handleButtonPress() {
  unsigned long currentTime = millis();

  if (currentTime - lastInterruptTime > debounceDelay) {
    ledState = !ledState;
    pressCount++;
    lastInterruptTime = currentTime;
  }
}
