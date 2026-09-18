const int clkPin = 2;
const int dtPin = 3;
const int swPin = 4;

int counter = 0;
int lastClkState;

void setup() {
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);

  Serial.begin(9600);

  lastClkState = digitalRead(clkPin); // record starting state
}

void loop() {
  int currentClkState = digitalRead(clkPin);

  // a change in CLK means the knob moved one "step"
  if (currentClkState != lastClkState) {
    // check DT's state at this moment to determine direction
    if (digitalRead(dtPin) != currentClkState) {
      counter++; // clockwise
    } else {
      counter--; // counter-clockwise
    }

    Serial.print("Counter: ");
    Serial.println(counter);
  }
  lastClkState = currentClkState;

  // check the built-in button
  if (digitalRead(swPin) == LOW) {
    Serial.println("Button pressed - Reset counter");
    counter = 0;
    delay(300); // simple debounce for the button
  }
}
