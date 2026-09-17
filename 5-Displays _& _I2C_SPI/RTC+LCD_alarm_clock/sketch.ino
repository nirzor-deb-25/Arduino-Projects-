// RTC + LCD Alarm Clock
// Components: Arduino Uno, DS1307 RTC, 16x2 I2C LCD, Buzzer, Push Button
//
// The RTC and LCD share the same I2C bus (SDA/SCL) but have different
// addresses (RTC = 0x68, LCD = 0x27), so both can coexist on A4/A5.

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzerPin = 8;
const int buttonPin = 2; // Silences the alarm when pressed (active LOW)

int alarmHour   = 7;
int alarmMinute = 30;

bool alarmTriggered = false;
int lastMinuteChecked = -1;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC - check wiring.");
    while (true);
  }

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lcd.init();
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("Alarm Clock");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();
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
  lcd.print(alarmTriggered ? " RING!" : "      ");

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

void printTwoDigits(int value) {
  if (value < 10) {
    lcd.print("0");
  }
  lcd.print(value);
}
