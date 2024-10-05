#include <AceTMI.h>  // Include the AceTMI library for TM1638 communication

using ace_tmi::SimpleTmi1638Interface;

// Define pin connections for TM1638
const int strobePin = 8;  // Strobe pin for TM1638
const int clkPin = 9;     // Clock pin for TM1638
const int dioPin = 10;    // Data pin for TM1638

// TM1638 interface using SimpleTmi1638Interface
SimpleTmi1638Interface tmInterface(strobePin, clkPin, dioPin);

// Digit patterns for 7-segment display (0-7)
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

// Array to hold digits to display (0-7)
byte digitsToDisplay[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// Brightness level (0-7 for TM1638)
int brightness = 4;

void setup() {
  // Initialize the TM1638 interface
  tmInterface.begin();

  // Set the brightness level
  setBrightness(brightness);

  // Render the initial digits to the display
  renderDisplay();
}

void loop() {
  // Dynamically update the display if needed in this loop
}

// Function to set brightness (0-7 for TM1638)
void setBrightness(int level) {
  level = constrain(level, 0, 7);  // Ensure brightness level is within valid range
  tmInterface.writeCommand(0x88 | level);  // 0x88 is the base command, level adds brightness
}

// Function to render the digits to the 8-digit display
void renderDisplay() {
  for (int i = 0; i < 8; i++) {
    tmInterface.writeData(i << 1, digitPatterns[digitsToDisplay[i]]);  // Write the segment data for each digit
  }
}
