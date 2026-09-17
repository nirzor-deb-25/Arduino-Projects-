// Joystick-Controlled LED Direction Indicator
// Components: Arduino Uno, Analog Joystick Module, 5x LED, 5x 220 ohm Resistor
//
// Moving the joystick lights up the LED matching the direction pushed.
// Pressing the joystick button lights up the "Select" LED.

const int vrxPin = A0;  // Joystick X-axis
const int vryPin = A1;  // Joystick Y-axis
const int swPin  = 2;   // Joystick push-button (active LOW)

const int ledUp     = 8;
const int ledDown    = 9;
const int ledLeft   = 10;
const int ledRight  = 11;
const int ledSelect = 12;

// Center of a typical joystick's resting analog range is ~512 (0-1023 scale).
// These thresholds create a "dead zone" in the middle so the LEDs don't
// flicker on from small amounts of drift when the stick isn't touched.
const int centerValue = 512;
const int deadZone    = 150;

void setup() {
  pinMode(swPin, INPUT_PULLUP); // Button reads LOW when pressed

  pinMode(ledUp, OUTPUT);
  pinMode(ledDown, OUTPUT);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledSelect, OUTPUT);

  Serial.begin(9600);
  Serial.println("Joystick direction indicator starting...");
}

void loop() {
  int xValue = analogRead(vrxPin);
  int yValue = analogRead(vryPin);
  bool buttonPressed = (digitalRead(swPin) == LOW);

  digitalWrite(ledUp, LOW);
  digitalWrite(ledDown, LOW);
  digitalWrite(ledLeft, LOW);
  digitalWrite(ledRight, LOW);

  if (yValue < centerValue - deadZone) {
    digitalWrite(ledUp, HIGH);
    Serial.println("UP");
  } else if (yValue > centerValue + deadZone) {
    digitalWrite(ledDown, HIGH);
    Serial.println("DOWN");
  }

  if (xValue < centerValue - deadZone) {
    digitalWrite(ledLeft, HIGH);
    Serial.println("LEFT");
  } else if (xValue > centerValue + deadZone) {
    digitalWrite(ledRight, HIGH);
    Serial.println("RIGHT");
  }

  digitalWrite(ledSelect, buttonPressed ? HIGH : LOW);
  if (buttonPressed) {
    Serial.println("BUTTON PRESSED");
  }

  delay(100);
}
