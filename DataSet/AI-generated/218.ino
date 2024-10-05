#include <TM1638.h>  // Include the TM1638 library

// Pin definitions for the TM1638 module
const int STROBE_PIN = 2;   // Strobe pin
const int CLOCK_PIN = 3;    // Clock pin
const int DATA_PIN = 4;     // Data pin

// Create an instance of the TM1638 display
TM1638 tm1638(STROBE_PIN, CLOCK_PIN, DATA_PIN);

// Function to update the display based on button states
void updateDisplay(int buttonStates[], int brightness) {
  // Clear the display
  tm1638.clearDisplay();

  // Display button states
  for (int i = 0; i < 8; i++) {
    if (buttonStates[i]) {
      tm1638.displayNumber(1, i);  // Display "1" if button is pressed
    } else {
      tm1638.displayNumber(0, i);  // Display "0" if button is not pressed
    }
  }
  
  // Set brightness based on the button pressed
  tm1638.setBrightness(brightness);
}

void setup() {
  tm1638.init();              // Initialize the TM1638 module
  tm1638.setBrightness(0);    // Set initial brightness to 0
}

void loop() {
  // Array to store button states
  int buttonStates[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  // Read button states
  int buttons = tm1638.getButtons(); // Get the current button states

  // Update button states array and brightness
  for (int i = 0; i < 8; i++) {
    buttonStates[i] = (buttons & (1 << i)) ? 1 : 0; // Update the button state
    if (buttonStates[i]) {
      tm1638.setBrightness(i); // Set brightness based on which button is pressed
    }
  }

  // Update the display with the current button states
  updateDisplay(buttonStates, tm1638.getBrightness());
  
  delay(100);  // Short delay to avoid flickering
}
