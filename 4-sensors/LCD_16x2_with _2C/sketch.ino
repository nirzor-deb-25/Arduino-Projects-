// 16x2 LCD with I2C
// Components: Arduino Uno, 16x2 LCD with I2C backpack
//
// The I2C backpack lets us control the entire display using just 2 signal
// wires (SDA, SCL) instead of the 6+ wires a standard LCD normally needs.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Most I2C LCD backpacks use address 0x27 or 0x3F.
// If the screen shows nothing but the backlight is on, try changing this.
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastUpdate = 0;
int counter = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print("I2C LCD Ready");

  delay(2000);
  lcd.clear();
}

void loop() {
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();
    counter++;

    lcd.setCursor(0, 0);
    lcd.print("Uptime counter:");

    lcd.setCursor(0, 1);
    lcd.print(counter);
    lcd.print(" seconds   ");
  }
}
