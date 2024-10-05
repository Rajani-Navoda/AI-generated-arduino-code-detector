#include <TM1638.h>  // Include the TM1638 library

// Pin definitions for the TM1638 module
const int STROBE_PIN = 2;   // Strobe pin
const int CLOCK_PIN = 3;    // Clock pin
const int DATA_PIN = 4;     // Data pin

// Create an instance of the TM1638 display
TM1638 tm1638(STROBE_PIN, CLOCK_PIN, DATA_PIN);

// Array of digits to display
const int digits[] = {0, 1, 2, 3, 4, 5};
const int numDigits = sizeof(digits) / sizeof(digits[0]);

// Timing variables
unsigned long previousMillis = 0;
const long interval = 1000;  // Time interval for scrolling (1 second)

// Brightness levels (0-7 for TM1638)
int brightness = 0;

void setup() {
  tm1638.init();                      // Initialize the TM1638 module
  tm1638.setBrightness(brightness);   // Set initial brightness
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
    tm1638.setBrightness(brightness);   // Update brightness
  }
}

// Function to scroll digits to the left
void scrollDigits() {
  for (int i = 0; i < numDigits; i++) {
    // Display the current digit
    tm1638.displayNumber(digits[i], i);  // Display digit at position i
    delay(200);  // Short delay for visibility

    // Clear the display
    tm1638.clearDisplay();
  }
}
