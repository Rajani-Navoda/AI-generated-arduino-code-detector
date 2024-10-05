#include <ShiftRegister74HC595.h>  // Include the library for the 74HC595 shift register

// Pin definitions for the shift register
const int latchPin = 4;  // Latch pin for 74HC595
const int clockPin = 5;  // Clock pin for 74HC595
const int dataPin = 6;   // Data pin for 74HC595

// Create an instance of the ShiftRegister74HC595 class
ShiftRegister74HC595<1> sr(latchPin, clockPin, dataPin);  // Using 1 shift register

// Array to hold digit patterns for digits 0-7
const byte digitPatterns[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111  // 7
};

// Array to hold brightness levels for each digit (0-255)
int brightnessLevels[8] = {32, 64, 96, 128, 160, 192, 224, 255};

// Array to hold the current digits to display
byte digitsToDisplay[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// Timing variables
unsigned long previousMillis = 0;
const long interval = 200;  // Time interval for rotation (200ms)

void setup() {
  // Initialize the shift register
  sr.setAllLow();  // Clear all segments
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the display was updated
    previousMillis = currentMillis;

    // Rotate the digits to the left
    rotateDigits();

    // Render the digits with their brightness
    renderDisplay();
  }
}

// Function to rotate the digits to the left
void rotateDigits() {
  byte firstDigit = digitsToDisplay[0];
  for (int i = 0; i < 7; i++) {
    digitsToDisplay[i] = digitsToDisplay[i + 1];
  }
  digitsToDisplay[7] = firstDigit;  // Loop the first digit to the end
}

// Function to render the digits to the display with brightness control
void renderDisplay() {
  for (int i = 0; i < 8; i++) {
    // Set the segments for the current digit
    sr.setAll(digitPatterns[digitsToDisplay[i]]);
    
    // Use PWM to control the brightness for the current digit
    analogWrite(latchPin, brightnessLevels[i]);  // This line assumes latchPin is PWM capable

    // Turn on the current digit (multiplexing)
    digitalWrite(latchPin, HIGH);
    delay(5);  // Small delay for visibility
    digitalWrite(latchPin, LOW);
  }
}
