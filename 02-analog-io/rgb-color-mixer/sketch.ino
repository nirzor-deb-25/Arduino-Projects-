const int redPotPin = A0;
const int greenPotPin = A1;
const int bluePotPin = A2;

const int redLedPin = 9;
const int greenLedPin = 10;
const int blueLedPin = 11;

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int redValue = analogRead(redPotPin);
  int greenValue = analogRead(greenPotPin);
  int blueValue = analogRead(bluePotPin);

  int redBrightness = map(redValue, 0, 1023, 0, 255);
  int greenBrightness = map(greenValue, 0, 1023, 0, 255);
  int blueBrightness = map(blueValue, 0, 1023, 0, 255);

  analogWrite(redLedPin, redBrightness);
  analogWrite(greenLedPin, greenBrightness);
  analogWrite(blueLedPin, blueBrightness);

  Serial.print("R: ");
  Serial.print(redBrightness);
  Serial.print("  G: ");
  Serial.print(greenBrightness);
  Serial.print("  B: ");
  Serial.println(blueBrightness);

  delay(100);
}
