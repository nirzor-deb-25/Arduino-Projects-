const int potPin = A0;
const int ledPin = 9;  // must be a PWM (~) pin

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // potPin doesn't need pinMode() for analogRead — it's automatic
}

void loop() {
  int potValue = analogRead(potPin);           // 0 to 1023
  int brightness = map(potValue, 0, 1023, 0, 255); // convert to 0-255

  analogWrite(ledPin, brightness);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Brightness: ");
  Serial.println(brightness);

  delay(50); // small delay just to keep Serial output readable
}
