// PIR Motion Sensor Alarm
// Components: Arduino Uno, HC-SR501 PIR sensor, Buzzer, LED

const int pirPin    = 2;   // PIR OUT pin
const int buzzerPin = 8;   // Buzzer +
const int ledPin    = 13;  // Alarm LED

int pirState = LOW;   // start assuming no motion
int val = 0;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
  Serial.println("PIR alarm system initializing...");
  delay(3000); // let PIR sensor settle/calibrate
  Serial.println("Ready. Monitoring for motion.");
}

void loop() {
  val = digitalRead(pirPin);

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // 1kHz alarm tone

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
