const int ldrPin = A0;
const int ledPin = 9;

const int darkThreshold = 500; // adjust based on testing — higher value = darker

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(ldrPin); // 0 (bright) to 1023 (dark), depends on wiring

  Serial.print("Light level: ");
  Serial.println(lightLevel);

  if (lightLevel > darkThreshold) {
    digitalWrite(ledPin, HIGH); // dark enough — turn on the night light
  } else {
    digitalWrite(ledPin, LOW); // bright enough — keep it off
  }

  delay(200);
}
