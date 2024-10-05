#include <Wire.h>  // Include Wire library for I2C communication
#include <Adafruit_LEDBackpack.h>  // Include Adafruit library for HT16K33

// Create an instance of the Adafruit 7-segment display class
Adafruit_7segment display = Adafruit_7segment();

// Digits to display (0-3)
byte digitsToDisplay[4] = {0, 1, 2, 3};

// Brightness level (0-15 for HT16K33)
int brightness = 0;

// Timing variables
unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second interval for scrolling

void setup() {
  // Initialize the display with I2C address 0x70 (default for HT16K33)
  display.begin(0x70);

  // Set initial brightness
  setBrightness(brightness);

  // Display the initial digits
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

// Function to set the brightness (0-15 for HT16K33)
void setBrightness(int level) {
  level = constrain(level, 0, 15);  // Ensure brightness level is within valid range
  display.setBrightness(level);
}

// Function to render the digits to the display
void renderDisplay() {
  for (int i = 0; i < 4; i++) {
    display.writeDigitNum(i, digitsToDisplay[i]);  // Write each digit to the display
  }
  display.writeDisplay();  // Update the display with the new data
}

// Function to scroll the digits to the left
void scrollDigits() {
  // Shift all digits to the left
  for (int i = 0; i < 3; i++) {
    digitsToDisplay[i] = digitsToDisplay[i + 1];
  }

  // Loop the last digit to the first position
  digitsToDisplay[3] = (digitsToDisplay[3] + 1) % 10;  // Increment and wrap around if greater than 9
}

// Function to update the brightness level
void updateBrightness() {
  brightness = (brightness + 1) % 16;  // Increment and wrap brightness (0-15)
  setBrightness(brightness);
}
