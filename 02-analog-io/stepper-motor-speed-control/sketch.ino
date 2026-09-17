#include <Stepper.h>

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

const int potPin = A0;

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int motorSpeed = map(potValue, 0, 1023, 1, 20); // RPM range 1-20

  myStepper.setSpeed(motorSpeed);
  myStepper.step(stepsPerRevolution / 20);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Speed (RPM): ");
  Serial.println(motorSpeed);
}
