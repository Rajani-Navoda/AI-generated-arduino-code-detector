const int numLEDs = 10;  // Number of LEDs
const int ledPins[numLEDs] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Array of LED pins

void setup() {
  // Initialize each LED pin as an output
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Example sequence to simulate a railroad signal

  // All LEDs off
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(1000);  // Wait for 1 second

  // Turn on LEDs to simulate a signal pattern
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);  // Wait for 100 milliseconds
    digitalWrite(ledPins[i], LOW);
  }
  delay(1000);  // Wait for 1 second

  // Turn on a specific pattern of LEDs (example: LEDs 1, 2, 3, 4, 5 on)
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(1000);  // Wait for 1 second

  // Turn off all LEDs
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(1000);  // Wait for 1 second
}
