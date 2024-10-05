#include <TM1637Display.h>  // Include the TM1637 display library

// Pin definitions for the TM1637 module
const int clkPin = 2;  // CLK pin for TM1637
const int dioPin = 3;  // DIO pin for TM1637

// Create an instance of the TM1637 display
TM1637Display display(clkPin, dioPin);

// Button pins
const int buttonPins[6] = {4, 5, 6, 7, 8, 9};  // Array of button pins
int buttonValues[6] = {0};  // Array to store button states

void setup() {
  display.setBrightness(0x0f);  // Set maximum brightness

  // Initialize button pins
  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);  // Set each button pin as input with pull-up resistor
  }

  // Display initial state
  updateDisplay(0);
}

void loop() {
  // Read button states and update display
  readButtons();
  updateDisplay(getActiveButton());
  delay(100);  // Short delay for debounce
}

// Function to read button states
void readButtons() {
  for (int i = 0; i < 6; i++) {
    buttonValues[i] = digitalRead(buttonPins[i]);  // Read button state
  }
}

// Function to get the index of the active button
int getActiveButton() {
  for (int i = 0; i < 6; i++) {
    if (buttonValues[i] == LOW) {  // Check if button is pressed
      return i;  // Return index of pressed button
    }
  }
  return -1;  // Return -1 if no button is pressed
}

// Function to update the display based on the active button
void updateDisplay(int activeButton) {
  // Default display value
  String displayValue = "FF-0-0";

  if (activeButton >= 0) {
    // Update display based on the active button
    displayValue = "F" + String(7 - activeButton) + "-1-" + String(activeButton);
  }

  // Convert string to displayable format
  display.showNumberDecEx(displayValue.toInt(), 0b01000000, true);  // Display formatted string
}
