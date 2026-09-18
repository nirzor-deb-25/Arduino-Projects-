# RFID Door Lock (SPI)

## Overview
This project uses an MFRC522 RFID reader to simulate a door lock: tapping a tag reads its unique ID (UID), which is compared against a hardcoded list of authorized UIDs to grant or deny access. It's the first project using SPI, a faster multi-wire communication protocol distinct from the single-wire and I2C protocols used elsewhere.

## What I Learned
- How SPI differs from simpler digital I/O and single-wire protocols: it uses dedicated MOSI, MISO, and SCK lines plus a chip-select (SS) pin, enabling fast communication with peripherals like RFID readers, SD cards, and displays
- The two-step initialization pattern common to SPI/I2C peripherals: initializing the communication bus itself (`SPI.begin()`) before initializing the specific connected device (`rfid.PCD_Init()`)
- How to read a tag's UID as an array of bytes and print it in hexadecimal for debugging
- How to implement byte-array comparison for access control — checking each byte of a scanned UID against a known authorized UID
- That MFRC522 modules run on 3.3V, not 5V, unlike most other modules used so far in this series

## Circuit

![Circuit Diagram](./Circuit%20Diagram%2040.png)

- RFID SDA → Arduino pin 10
- RFID SCK → Arduino pin 13
- RFID MOSI → Arduino pin 11
- RFID MISO → Arduino pin 12
- RFID RST → Arduino pin 9
- RFID VCC → Arduino 3.3V
- RFID GND → Arduino GND

## Components Used
- Arduino Uno
- 1x MFRC522 RFID Reader module
- RFID tag (simulated in Wokwi)

## Code Summary
```cpp
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

byte authorizedUID[4] = {0x01, 0x02, 0x03, 0x04};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Tap an RFID tag to test...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Tag UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (compareUID(rfid.uid.uidByte, rfid.uid.size)) {
    Serial.println("Access GRANTED");
  } else {
    Serial.println("Access DENIED");
  }

  rfid.PICC_HaltA();
}

bool compareUID(byte *scannedUID, byte size) {
  if (size != 4) return false;
  for (byte i = 0; i < 4; i++) {
    if (scannedUID[i] != authorizedUID[i]) return false;
  }
  return true;
}
```

## Test Results
- Tapping the simulated Blue Card (UID: 01 02 03 04) before updating the authorized list: correctly printed "Access DENIED"
- After updating `authorizedUID` to match the Blue Card's actual UID: tapping it again correctly printed "Access GRANTED"
- Confirms the UID comparison logic responds accurately to both matching and non-matching tags

## Key Takeaway
SPI-based peripherals follow a consistent pattern — initialize the bus, initialize the device, then use library methods to interact with it — that generalizes to many other high-speed modules. This project also reinforced a genuinely useful access-control pattern: comparing scanned data against a known authorized list, byte by byte.

## Simulation
Built and tested on [Wokwi](https://wokwi.com).

## Previous Project
[Rotary Encoder](../../06-interrupts-timers/rotary-encoder) — the last Interrupts & Timers project.

## Next Project
[Two Arduinos Talking via I2C](../i2c-two-arduinos) — moving into I2C-based device-to-device communication.
