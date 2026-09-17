// OLED Display with I2C (SSD1306, 128x64)
// Components: Arduino Uno, SSD1306 OLED Display
//
// Like the I2C LCD, this display shares the same 2-wire I2C bus (SDA/SCL),
// but instead of just printing text to fixed character cells, it's a full
// pixel-addressable graphics display - so we can draw shapes and animate too.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1   // No dedicated reset pin used in this wiring
#define SCREEN_ADDRESS 0x3C // Default SSD1306 I2C address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastUpdate = 0;
int counter = 0;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed - check wiring/address.");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("OLED Display Ready");
  display.println("SSD1306 via I2C");
  display.display();

  delay(2000);
}

void loop() {
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();
    counter++;

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Uptime Counter");

    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print(counter);
    display.println(" s");

    int barWidth = map(counter % 10, 0, 10, 0, SCREEN_WIDTH - 4);
    display.drawRect(0, 50, SCREEN_WIDTH, 10, SSD1306_WHITE);
    display.fillRect(2, 52, barWidth, 6, SSD1306_WHITE);

    display.display();
  }
}
