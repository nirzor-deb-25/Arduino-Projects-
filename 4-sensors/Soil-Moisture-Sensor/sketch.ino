// Soil Moisture Sensor
// Components: Arduino Uno, Soil Moisture Sensor (simulated with a potentiometer in Wokwi), LED
//
// Real hardware note: a soil moisture sensor's AOUT pin behaves just like the
// potentiometer's wiper pin here - it outputs a variable analog voltage. Wetter
// soil = lower resistance = different voltage than dry soil.

const int sensorPin = A0;  // Soil sensor AOUT / potentiometer wiper
const int ledPin    = 8;   // "Soil too dry" alert LED

const int dryThreshold = 500; // Adjust based on calibration (0-1023 scale)
// Lower raw values usually mean wetter soil for resistive sensors,
// but this can be inverted depending on your specific sensor module - test and flip if needed.

int sensorValue = 0;
int moisturePercent = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Soil moisture monitor starting...");
}

void loop() {
  sensorValue = analogRead(sensorPin);

  // Map raw analog value (0-1023) to a 0-100% moisture scale.
  // Adjust the input range (0, 1023) after calibrating with your real sensor
  // in dry air vs. a cup of water.
  moisturePercent = map(sensorValue, 1023, 0, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Raw: ");
  Serial.print(sensorValue);
  Serial.print("  Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  if (sensorValue > dryThreshold) {
    digitalWrite(ledPin, HIGH); // Soil too dry - alert on
    Serial.println("Soil is DRY - consider watering!");
  } else {
    digitalWrite(ledPin, LOW);  // Soil moisture OK
  }

  delay(1000);
}
