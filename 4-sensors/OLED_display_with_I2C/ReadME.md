# OLED Display with I2C

## Overview
This project drives a 128x64 SSD1306 OLED display over I2C. Unlike the character-based LCD from the previous project, the OLED is a fully pixel-addressable graphics display — every pixel can be controlled individually, which means it can draw shapes, bars, and custom layouts, not just fixed text cells. It shares the same 2-wire I2C bus (SDA/SCL) as the LCD, but uses a different default address (0x3C instead of 0x27).

## What I Learned
- The difference between a character LCD (fixed text cells only) and a graphics display like the SSD1306 (individually addressable pixels)
- How to use the Adafruit_GFX and Adafruit_SSD1306 libraries together — GFX provides the drawing primitives, SSD1306 handles the actual hardware communication
- That different I2C displays can have different default addresses (0x3C here vs. 0x27 for the LCD), so hardcoding one blindly can silently fail
- How to combine text of different sizes (`setTextSize()`) and simple shapes (`drawRect()`, `fillRect()`) on the same screen to build a small dashboard-style layout
- How to check `display.begin()`'s return value to detect a wiring or address problem early, instead of guessing why the screen stays blank

## Circuit
[Circuit Diagram](./Circuit%20Diagram%2034.png)

- OLED GND → Arduino GND
- OLED VCC → Arduino 5V
- OLED SCL → Arduino A5
- OLED SDA → Arduino A4

## Components Used
- Arduino Uno
- 1x SSD1306 OLED Display (128x64, I2C)

## Code Summary
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

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
```

## Test Results
- Display initialized successfully at address `0x3C` on the first attempt, no fallback needed
- "OLED Display Ready" splash screen showed correctly for 2 seconds before clearing
- Uptime counter updated smoothly every second, with the progress bar filling and looping every 10 seconds as designed
- No flickering or ghosting between frames, since `clearDisplay()` runs before every redraw

## Key Takeaway
This project extended the I2C concept from the LCD project into full graphics territory. Rather than just placing text at fixed positions, the SSD1306's pixel-level control opens the door to custom UI elements like progress bars, icons, and even simple animations — all still communicating over the same lightweight 2-wire I2C bus.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[LCD 16x2 with I2C](../LCD-16x2-I2C) — introduction to the I2C protocol using character-based text output.

## Next Project
_Coming soon._
