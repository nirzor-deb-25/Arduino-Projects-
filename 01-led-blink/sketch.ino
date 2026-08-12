void setup() {
  pinMode(13, OUTPUT);   // set pin 13 as output
}

void loop() {
  digitalWrite(13, HIGH); // turn LED on
  delay(1000);             // wait 1 second
  digitalWrite(13, LOW);  // turn LED off
  delay(1000);             // wait 1 second
}
