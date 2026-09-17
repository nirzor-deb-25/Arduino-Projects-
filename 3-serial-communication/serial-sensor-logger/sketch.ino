const int sensorPin = A0;
unsigned long lastLogTime = 0;
const long logInterval = 1000; // log once per second

void setup() {
  Serial.begin(9600);
  Serial.println("Timestamp(ms),SensorValue,VoltageEquivalent");
  // CSV header row — makes this file easy to open in Excel/Sheets later
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastLogTime >= logInterval) {
    lastLogTime = currentTime;

    int sensorValue = analogRead(sensorPin);
    float voltage = sensorValue * (5.0 / 1023.0); // convert raw reading to actual voltage

    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(sensorValue);
    Serial.print(",");
    Serial.println(voltage, 2); // 2 decimal places
  }

  // other code could run here freely — logging doesn't block anything
}
