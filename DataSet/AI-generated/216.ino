#include <TM1637Display.h>  // Include the TM1637 display library

// Pin definitions for the TM1637 modules
const int clkPin = 2;         // Common CLK pin
const int dioPin1 = 3;       // DIO pin for the first module
const int dioPin2 = 4;       // DIO pin for the second module

// Create instances of the TM1637 displays
TM1637Display display1(clkPin, dioPin1);
TM1637Display display2(clkPin, dioPin2);

// Array of digits to display
const int digits[] = {0, 1, 2, 3};
const int numDigits = sizeof(digits) / sizeof(digits[0]);

// Timing variables
unsigned long previousMillis = 0;
const long interval = 1000;  // Time interval for rotation (1 second)

// Brightness levels (0-7 for TM1637)
int brightness = 0;

void setup() {
  display1.setBrightness(brightness);  // Set initial brightness for the first display
  display2.setBrightness(brightness);  // Set initial brightness for the second display
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Rotate digits to the left
    rotateDigits();

    // Change brightness for the next iteration
    brightness = (brightness + 1) % 8;  // Cycle through brightness levels (0-7)
    display1.setBrightness(brightness); // Update brightness for the first display
    display2.setBrightness(brightness); // Update brightness for the second display
  }
}

// Function to rotate digits to the left
void rotateDigits() {
  for (int i = 0; i < numDigits; i++) {
    // Display the current digit on both displays
    display1.showNumberDec(digits[i], false, 1, 0);
    display2.showNumberDec(digits[i], false, 1, 0);
    delay(200);  // Short delay for visibility

    // Clear the displays
    display1.clear();
    display2.clear();
  }
}
