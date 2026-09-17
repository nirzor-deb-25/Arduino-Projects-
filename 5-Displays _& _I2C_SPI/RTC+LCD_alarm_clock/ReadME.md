# RTC + LCD Alarm Clock

## Overview
This project combines a DS1307 real-time clock module with a 16x2 I2C LCD to build a functioning alarm clock. It's the first project to put two I2C devices on the same bus at once — the RTC and the LCD share the same SDA/SCL wires, but coexist without conflict because each has its own unique I2C address (RTC = 0x68, LCD = 0x27). A buzzer sounds when the current time matches the alarm time, and a push button silences it.

## What I Learned
- How multiple I2C devices can share the same two physical wires simultaneously, as long as each has a distinct address
- How to use the RTClib library to read hours, minutes, and seconds from a hardware real-time clock instead of relying on `millis()` (which resets every time the board powers off)
- How to compare the current time against a fixed alarm time and trigger an action only once per matching minute, instead of retriggering continuously every loop cycle
- How to combine time-based logic (RTC), display output (LCD), sound output (buzzer), and user input (button) all in a single sketch
- That in the Wokwi simulator, the DS1307 starts already synced to the real current system time, which is different from real hardware where you typically set the time once via code

## Circuit
[Circuit Diagram](./Circuit%20Diagram%2035.png)

- RTC GND → Arduino GND
- RTC 5V → Arduino 5V
- RTC SDA → Arduino A4
- RTC SCL → Arduino A5
- LCD GND → Arduino GND
- LCD VCC → Arduino 5V
- LCD SDA → Arduino A4 (shared with RTC)
- LCD SCL → Arduino A5 (shared with RTC)
- Buzzer + → Arduino pin 8
- Buzzer – → Arduino GND
- Button (one leg) → Arduino pin 2
- Button (other leg) → Arduino GND

## Components Used
- Arduino Uno
- 1x DS1307 RTC Module
- 1x 16x2 LCD with I2C backpack
- 1x Buzzer
- 1x Push Button

## Code Summary
```cpp
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzerPin = 8;
const int buttonPin = 2;

int alarmHour   = 7;
int alarmMinute = 30;

bool alarmTriggered = false;
int lastMinuteChecked = -1;

void setup() {
  Wire.begin();
  rtc.begin();
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  DateTime now = rtc.now();

  lcd.setCursor(0, 0);
  lcd.print("Time  ");
  printTwoDigits(now.hour());
  lcd.print(":");
  printTwoDigits(now.minute());
  lcd.print(":");
  printTwoDigits(now.second());

  lcd.setCursor(0, 1);
  lcd.print("Alarm ");
  printTwoDigits(alarmHour);
  lcd.print(":");
  printTwoDigits(alarmMinute);

  if (now.hour() == alarmHour && now.minute() == alarmMinute) {
    if (lastMinuteChecked != now.minute()) {
      alarmTriggered = true;
      lastMinuteChecked = now.minute();
    }
  } else {
    lastMinuteChecked = -1;
  }

  if (alarmTriggered) {
    tone(buzzerPin, 1000);
    if (digitalRead(buttonPin) == LOW) {
      alarmTriggered = false;
      noTone(buzzerPin);
    }
  } else {
    noTone(buzzerPin);
  }

  delay(200);
}
```

## Test Results
- The LCD correctly displayed live time on line 1 and the fixed alarm time on line 2, updating every second
- Setting the alarm to a near-future time correctly triggered the buzzer and "RING!" label once the clock reached that minute
- Pressing the push button successfully silenced the alarm
- The RTC and LCD operated simultaneously on the shared I2C bus with no address conflicts or communication errors

## Key Takeaway
This project tied together everything from the previous stage — I2C communication, real-time data, and physical input/output — into one cohesive device. It also introduced an important real-world timing pattern: triggering an event exactly once when a condition becomes true, rather than repeatedly for as long as it stays true, which is essential for anything alarm- or notification-based.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[OLED Display with I2C](../OLED-Display-I2C) — pixel-addressable graphics display over I2C.

## Next Project
_Coming soon._
