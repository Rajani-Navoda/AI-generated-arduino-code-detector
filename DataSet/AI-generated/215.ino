#include <TM1637Display.h>  // Include the TM1637 display library

// Pin definitions for the TM1637 module
const int clkPin = 2;  // CLK pin for TM1637
const int dioPin = 3;  // DIO pin for TM1637

// Create an instance of the TM1637 display
TM1637Display display(clkPin, dioPin);

// Array of digits to display
const int digits[] = {0, 1, 2, 3, 4, 5};
const int numDigits = sizeof(digits) / sizeof(digits[0]);

// Timing variables
unsigned long previousMillis = 0;
const long interval = 1000;  // Time interval for scrolling (1 second)

// Brightness levels (0-7 for TM1637)
int brightness = 0;

void setup() {
  display.setBrightness(brightness);  // Set initial brightness
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Scroll the digits to the left
    scrollDigits();

    // Change brightness for the next iteration
    brightness = (brightness + 1) % 8;  // Cycle through brightness levels (0-7)
    display.setBrightness(brightness);  // Update brightness
  }
}

// Function to scroll digits to the left
void scrollDigits() {
  for (int i = 0; i < numDigits; i++) {
    // Show the current digit
    display.showNumberDec(digits[i], false, 1, 0);
    delay(200);  // Short delay for visibility

    // Clear the display
    display.clear();
  }
}
