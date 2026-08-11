#include <Servo.h>

// Pin definitions
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

Servo radarServo;   // create a Servo object to control our servo

// Function to measure distance using the HC-SR04
long readDistanceCM() {
  // Send a short pulse on trigPin to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure how long the echo pulse lasts (in microseconds)
  long duration = pulseIn(echoPin, HIGH);

  // Convert time to distance: speed of sound = 0.034 cm/microsecond
  // Divide by 2 because the sound travels there AND back
  long distance = duration * 0.034 / 2;

  return distance;
}

void setup() {
  Serial.begin(9600);          // start serial communication so we can see readings
  pinMode(trigPin, OUTPUT);    // Trig sends signals OUT
  pinMode(echoPin, INPUT);     // Echo receives signals IN
  radarServo.attach(servoPin); // tell the servo object which pin to control
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    radarServo.write(angle);          // move servo to this angle
    delay(30);                        // give it time to physically move
    long distance = readDistanceCM(); // take a reading at this angle

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);         // print "angle,distance"
  }

  // Sweep back from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    radarServo.write(angle);
    delay(30);
    long distance = readDistanceCM();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }
}
