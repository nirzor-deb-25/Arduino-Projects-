const int redPin = 10;
const int yellowPin = 11;
const int greenPin = 12;
const int walkPin = 8;
const int dontWalkPin = 9;
const int buttonPin = 2;

bool walkRequested = false;

enum LightState { GREEN, YELLOW, RED };
LightState currentState = GREEN;

unsigned long stateStartTime = 0;
unsigned long previousBlinkTime = 0;
bool walkBlinkOn = true;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(walkPin, OUTPUT);
  pinMode(dontWalkPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  digitalWrite(greenPin, HIGH);
  digitalWrite(dontWalkPin, HIGH);
  stateStartTime = millis();
}

void loop() {
  // continuously check the button, regardless of what the lights are doing
  if (digitalRead(buttonPin) == LOW && !walkRequested) {
    walkRequested = true;
    Serial.println("Pedestrian requested WALK");
  }

  unsigned long now = millis();
  unsigned long elapsed = now - stateStartTime;

  switch (currentState) {
    case GREEN:
      if (elapsed >= 4000) {
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, HIGH);
        currentState = YELLOW;
        stateStartTime = now;
      }
      break;

    case YELLOW:
      if (elapsed >= 1000) {
        digitalWrite(yellowPin, LOW);
        digitalWrite(redPin, HIGH);
        currentState = RED;
        stateStartTime = now;

        if (walkRequested) {
          digitalWrite(dontWalkPin, LOW);
          digitalWrite(walkPin, HIGH);
          Serial.println("Vehicles: RED | Pedestrians: WALK");
        } else {
          Serial.println("Vehicles: RED | No pedestrian request, staying DON'T WALK");
        }
      }
      break;

    case RED:
      if (walkRequested) {
        // Walk for 3s, then blink warning for 2s, then switch back
        if (elapsed < 3000) {
          // steady walk signal
        } else if (elapsed < 5000) {
          // blinking warning phase
          if (now - previousBlinkTime >= 300) {
            walkBlinkOn = !walkBlinkOn;
            digitalWrite(walkPin, walkBlinkOn ? HIGH : LOW);
            previousBlinkTime = now;
          }
        } else {
          digitalWrite(walkPin, LOW);
          digitalWrite(dontWalkPin, HIGH);
        }
      }

      if (elapsed >= 6000) {
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(dontWalkPin, HIGH);
        digitalWrite(walkPin, LOW);
        currentState = GREEN;
        stateStartTime = now;
        walkRequested = false;  // reset for next cycle
        Serial.println("Vehicles: GREEN - Go");
      }
      break;
  }
}
