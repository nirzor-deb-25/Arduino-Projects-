const int redPin = 10;
const int yellowPin = 11;
const int greenPin = 12;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // RED
  digitalWrite(redPin, HIGH);
  Serial.println("RED - Stop");
  delay(3000);
  digitalWrite(redPin, LOW);

  // GREEN
  digitalWrite(greenPin, HIGH);
  Serial.println("GREEN - Go");
  delay(3000);
  digitalWrite(greenPin, LOW);

  // YELLOW
  digitalWrite(yellowPin, HIGH);
  Serial.println("YELLOW - Caution");
  delay(1000);
  digitalWrite(yellowPin, LOW);
}
