#include <AceSegment.h>  // Include the AceSegment library

// Pin definitions
const int latchPin = 4;  // Latch pin for 74HC595 or other LED modules
const int clockPin = 5;  // Clock pin
const int dataPin = 6;   // Data pin

// Create a ScanningModule instance
ScanningModule scanningModule(latchPin, clockPin, dataPin);

// Create an array for the digits to display
const byte digitsToDisplay[] = {0, 1, 2, 3};

// Brightness level (0-255)
int brightness = 0;

// Timing variables
unsigned long previousMillis = 0;
const long interval = 200;  // Time interval for digit rotation

void setup() {
  // Initialize the scanning module
  scanningModule.begin();
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

    // Update the brightness level
    updateBrightness();

    // Render the display with the current brightness
    renderDisplay();
  }
}

// Function to rotate the digits to the left
void rotateDigits() {
  byte firstDigit = digitsToDisplay[0];
  for (int i = 0; i < 3; i++) {
    digitsToDisplay[i] = digitsToDisplay[i + 1];
  }
  digitsToDisplay[3] = firstDigit;  // Loop the first digit to the end
}

// Function to update the brightness (0-255)
void updateBrightness() {
  brightness += 32;  // Increment brightness
  if (brightness > 255) {
    brightness = 0;  // Wrap around brightness
  }
}

// Function to render the digits to the display
void renderDisplay() {
  for (int i = 0; i < 4; i++) {
    // Set the digit and brightness for the current digit
    scanningModule.setDigit(i, digitsToDisplay[i], brightness);
  }
  scanningModule.flush();  // Update the display
}
