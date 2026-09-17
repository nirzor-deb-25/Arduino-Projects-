# LCD 16x2 with I2C

## Overview
This project drives a 16x2 character LCD display using an I2C backpack module. Instead of the 6+ wires a standard LCD normally requires (RS, EN, D4-D7, plus power), the I2C backpack condenses everything down to just two signal wires — SDA and SCL — using the I2C communication protocol. This was the first project in the Displays & I2C/SPI stage, and the first to communicate with a peripheral using a shared two-wire bus instead of dedicated pins per signal.

## What I Learned
- How I2C works at a basic level: multiple devices can share the same two wires (SDA for data, SCL for clock), each identified by a unique address
- That I2C LCD backpacks commonly default to address `0x27` or `0x3F`, and picking the wrong one results in a blank (but backlit) screen
- How to use the `LiquidCrystal_I2C` library's `setCursor()` and `print()` functions to control exactly where text appears on the display
- How to update part of the screen (a live counter) without blocking the rest of the program, using `millis()` instead of `delay()`
- Why leaving trailing spaces after a printed number matters — it clears out leftover digits from a previous, longer number instead of leaving visual artifacts

## Circuit
[Circuit Diagram](./Circuit%20Diagram%2033.png)

- LCD GND → Arduino GND
- LCD VCC → Arduino 5V
- LCD SDA → Arduino A4
- LCD SCL → Arduino A5

## Components Used
- Arduino Uno
- 1x 16x2 LCD with I2C backpack

## Code Summary
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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
```

## Test Results
- Display showed the "Hello, World!" / "I2C LCD Ready" welcome message correctly for 2 seconds on startup
- After clearing, the live counter updated cleanly every second with no flickering or leftover characters from previous numbers
- Address `0x27` worked on the first attempt with no need to fall back to `0x3F`

## Key Takeaway
This project marked a shift from simple digital/analog I/O to communicating with a device over a proper protocol (I2C). It also introduced non-blocking timing with `millis()`, a pattern that will matter a lot more once projects need to do multiple time-based things at once without one `delay()` freezing everything else.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Joystick-Controlled LED Direction Indicator](../Joystick-Controlled) — combining analog and digital inputs.

## Next Project
_Coming soon._
