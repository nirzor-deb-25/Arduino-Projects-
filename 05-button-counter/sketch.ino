// Segment pins in order: A, B, C, D, E, F, G
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int buttonPin = 9;

// Lookup table: which segments (A-G) light up for each digit 0-9
// 1 = ON, 0 = OFF, order matches segPins array {A,B,C,D,E,F,G}
const byte digitTable[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

int count = 0;
int lastButtonState = HIGH;

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  displayDigit(count);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // detect a fresh press (transition from HIGH to LOW), not a held press
  if (buttonState == LOW && lastButtonState == HIGH) {
    count++;
    if (count > 9) {
      count = 0;  // wrap back to 0 after 9
    }
    displayDigit(count);
    Serial.println(count);
    delay(50); // basic debounce
  }

  lastButtonState = buttonState;
}

void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digitTable[digit][i]);
  }
}
