#include <LedControl.h>  // Include the LedControl library for MAX7219

// Pin connections for MAX7219 (dataPin, clkPin, csPin)
const int dataPin = 2;
const int clkPin = 3;
const int csPin = 4;

// Create an instance of the LedControl class
LedControl lc = LedControl(dataPin, clkPin, csPin, 1);  // 1 device (1 MAX7219)

// Digits to display (0-7)
byte digitsToDisplay[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// Brightness level (0-15 for MAX7219)
int brightness = 0;

// Timing variables
unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second interval for scrolling

void setup() {
  // Initialize the MAX7219
  lc.shutdown(0, false);  // Wake up the MAX7219
  lc.setIntensity(0, brightness);  // Set initial brightness
  lc.clearDisplay(0);  // Clear the display

  // Display initial digits
  renderDisplay();
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 1 second has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the digits were updated
    previousMillis = currentMillis;

    // Scroll digits to the left
    scrollDigits();

    // Update the brightness level
    updateBrightness();

    // Render the new digits and brightness
    renderDisplay();
  }
}

// Function to scroll the digits to the left
void scrollDigits() {
  // Shift all digits to the left
  byte firstDigit = digitsToDisplay[0];
  for (int i = 0; i < 7; i++) {
    digitsToDisplay[i] = digitsToDisplay[i + 1];
  }
  // Loop the first digit to the last position
  digitsToDisplay[7] = firstDigit;
}

// Function to update the brightness (0-15 for MAX7219)
void updateBrightness() {
  brightness = (brightness + 1) % 16;  // Increment and wrap brightness (0-15)
  lc.setIntensity(0, brightness);  // Set the new brightness level
}

// Function to render the digits to the display
void renderDisplay() {
  for (int i = 0; i < 8; i++) {
    lc.setDigit(0, i, digitsToDisplay[i], false);  // Display each digit
  }
}
