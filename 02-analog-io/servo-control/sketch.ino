#include <Servo.h>

Servo myServo;
const int potPin = A0;
const int servoPin = 9;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);              // 0 to 1023
  int angle = map(potValue, 0, 1023, 0, 180);      // convert to 0-180 degrees

  myServo.write(angle);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Angle: ");
  Serial.println(angle);

  delay(15); // small delay lets the servo catch up smoothly
}
