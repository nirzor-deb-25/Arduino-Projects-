#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22 // change to DHT11 if using that sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius by default

  // check if readings failed (common with real DHT sensors due to timing sensitivity)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return; // skip the rest of this loop iteration
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000); // DHT sensors are slow — don't read faster than every ~2 seconds
}
