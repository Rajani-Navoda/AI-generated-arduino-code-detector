#include <AceTMI.h>  // Include the AceTMI library for TM1637 communication

using ace_tmi::SimpleTmi1637Interface;

// Define pin connections for TM1637
const int clkPin = 2;  // Clock pin for TM1637
const int dioPin = 3;  // Data pin for TM1637

// TM1637 interface using SimpleTmi1637Interface
SimpleTmi1637Interface tmInterface(clkPin, dioPin);

// Digit patterns for 7-segment display (0-3)
const byte digitPatterns[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111  // 3
};

// Array to hold digits to display (0-3)
byte digitsToDisplay[4] = {0, 1, 2, 3};

// Brightness level (0-7 for TM1637)
int brightness = 4;

void setup() {
  // Initialize the TM1637 interface
  tmInterface.begin();

  // Set the brightness level
  setBrightness(brightness);

  // Render the initial digits to the display
  renderDisplay();
}

void loop() {
  // You can add code here to dynamically change the display if needed
}

// Function to set the brightness (0-7 for TM1637)
void setBrightness(int level) {
  level = constrain(level, 0, 7);  // Ensure brightness level is within valid range
  tmInterface.writeCommand(0x88 | level);  // Brightness command: 0x88 is the base command, level is added
}

// Function to render the digits to the 4-digit display
void renderDisplay() {
  tmInterface.start();  // Start communication with TM1637
  tmInterface.write(0xC0);  // Address command: 0xC0 for auto-increment starting from address 0
  
  // Write the digits to the display
  for (int i = 0; i < 4; i++) {
    tmInterface.write(digitPatterns[digitsToDisplay[i]]);  // Send the segment data for each digit
  }
  
  tmInterface.stop();  // Stop communication with TM1637
}
