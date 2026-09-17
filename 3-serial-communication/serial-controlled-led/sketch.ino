const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Type 'on' or 'off' and press Enter to control the LED.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // removes any trailing \r or whitespace

    if (command == "on") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED turned ON");
    } else if (command == "off") {
      digitalWrite(ledPin, LOW);
      Serial.println("LED turned OFF");
    } else {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }
}
