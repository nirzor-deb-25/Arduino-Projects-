const int ledPin = 13;
int ledState = LOW;           // current state of the LED

unsigned long previousMillis = 0;  // stores last time LED was updated
const long interval = 1000;         // interval at which to blink (ms)

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);          // let's also print to serial so you can see it working
}

void loop() {
  unsigned long currentMillis = millis();  // get current time since program started

  // check if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // save the last time we blinked

    // toggle the LED state
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
    Serial.println(ledState == HIGH ? "LED ON" : "LED OFF");
  }

  // imagine other code running here too — it won't be blocked!
  // e.g., checking a button, reading a sensor, etc.
}
