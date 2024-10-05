// Pin definitions
const int dataPin = 11;   // DS: Serial Data Input
const int clockPin = 12;  // SHCP: Shift Register Clock
const int latchPin = 13;  // STCP: Storage Register Clock

void setup() {
  // Set the 74HC595 pins as outputs
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  // Shift out data to the 74HC595
  // In this example, we turn on all LEDs connected to the 74HC595

  // Data to be sent to the 74HC595
  byte data = 0b11111111;  // Binary data for turning on all LEDs

  // Latch low to start sending data
  digitalWrite(latchPin, LOW);

  // Shift out the data
  shiftOut(dataPin, clockPin, MSBFIRST, data);

  // Latch high to output the data
  digitalWrite(latchPin, HIGH);

  // Wait for a second
  delay(1000);

  // Turn off all LEDs
  data = 0b00000000;

  // Latch low to start sending data
  digitalWrite(latchPin, LOW);

  // Shift out the data
  shiftOut(dataPin, clockPin, MSBFIRST, data);

  // Latch high to output the data
  digitalWrite(latchPin, HIGH);

  // Wait for a second
  delay(1000);
}
