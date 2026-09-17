// --- Constants ---
const int LED_PIN = 13;          // The pin the LED is connected to
const long BLINK_INTERVAL = 500; // The time interval (in milliseconds) between blinks

// --- Variables ---
int ledState = LOW;              // A variable to store the current state of the LED
unsigned long previousMillis = 0; // Will store the last time the LED was updated

void setup() {
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if the interval has passed since the last toggle
  if (currentMillis - previousMillis >= BLINK_INTERVAL) {
    // Save the last time you blinked the LED
    previousMillis = currentMillis;

    // If the LED is off, turn it on, and vice-versa
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // Set the LED with the new state
    digitalWrite(LED_PIN, ledState);
  }
}
