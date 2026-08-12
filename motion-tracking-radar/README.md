# 🎯 Arduino Motion-Tracking Radar

A simple radar system built with an Arduino Uno, an HC-SR04 ultrasonic sensor, and an SG90 servo motor. The servo sweeps the ultrasonic sensor back and forth from 0° to 180°, measuring distance at each angle — just like a real radar sweep.

Built and simulated using [Wokwi](https://wokwi.com/).

## 🔧 How It Works

1. The servo continuously sweeps from 0° → 180° and back
2. At every angle, the HC-SR04 sensor sends out an ultrasonic pulse and measures how long it takes to bounce back off an object
3. That time is converted into a distance (in cm)
4. The angle and distance are sent together over Serial as `angle,distance` — this raw data is what a radar display application would use to draw a live sweep

## 🛠️ Components Used

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller — runs the code, coordinates sensor + servo |
| HC-SR04 Ultrasonic Sensor | Measures distance to nearby objects |
| SG90 Servo Motor | Rotates the sensor to scan across a range of angles |

## 🔌 Circuit Diagram

![Circuit Diagram 1]
![Circuit Diagram 2]

## 🔗 Wiring

| Component Pin | Arduino Pin |
|---|---|
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| HC-SR04 Trig | Digital Pin 9 |
| HC-SR04 Echo | Digital Pin 10 |
| Servo Signal (PWM) | Digital Pin 6 |
| Servo VCC | 5V |
| Servo GND | GND |

## 💻 Code

See [`sketch.ino`](./sketch.ino) for the full Arduino code.

## ▶️ Run the Simulation

Try it live on Wokwi: [arduino-motion-tracking-radar](https://wokwi.com/projects/472093367962560513)

## 📁 Files

- `sketch.ino` — Arduino source code
- `diagram.json` — Wokwi circuit diagram definition
- `libraries.txt` — required libraries (Servo.h)
