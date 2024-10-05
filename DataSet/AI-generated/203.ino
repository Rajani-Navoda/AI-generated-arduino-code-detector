#include <Wire.h>            // I2C communication library
#include <AceWire.h>         // AceWire library for I2C control

using ace_wire::TwoWireInterface;

// Constants for HT16K33
const byte HT16K33_ADDRESS = 0x70;  // Default I2C address for HT16K33
const byte CMD_SYSTEM_SETUP = 0x20; // Turn on the oscillator
const byte CMD_DISPLAY_ON = 0x81;   // Turn on the display
const byte CMD_BRIGHTNESS = 0xE0;   // Set brightness, followed by brightness value (0-15)

// I2C interface
TwoWireInterface wireInterface;

// Digit patterns for 7-segment display (common anode)
const byte digitPatterns[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111  // 3
};

// Array to hold digits (0-3) to display on the 4-digit LED
byte digitsToDisplay[4] = {0, 1, 2, 3};

// Brightness control (0-15 for HT16K33)
int brightness = 8;

void setup() {
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize HT16K33
  initHT16K33();
  
  // Set brightness
  setBrightness(brightness);
  
  // Render the initial digits to the display
  renderDisplay();
}

void loop() {
  // Example: if you want to update the display over time, you can add code here
}

// Function to initialize the HT16K33
void initHT16K33() {
  wireInterface.beginTransmission(HT16K33_ADDRESS);
  wireInterface.write(CMD_SYSTEM_SETUP);  // Turn on system oscillator
  wireInterface.endTransmission();
  
  wireInterface.beginTransmission(HT16K33_ADDRESS);
  wireInterface.write(CMD_DISPLAY_ON);  // Turn on display, no blinking
  wireInterface.endTransmission();
}

// Function to set brightness (0-15)
void setBrightness(int level) {
  level = constrain(level, 0, 15);  // Ensure brightness level is within valid range
  wireInterface.beginTransmission(HT16K33_ADDRESS);
  wireInterface.write(CMD_BRIGHTNESS | level);  // Set brightness command
  wireInterface.endTransmission();
}

// Function to render the digits to the 4-digit display
void renderDisplay() {
  wireInterface.beginTransmission(HT16K33_ADDRESS);
  
  // HT16K33 requires alternating bytes for segment data
  for (int i = 0; i < 4; i++) {
    wireInterface.write(2 * i);             // Write digit address (0, 2, 4, 6)
    wireInterface.write(digitPatterns[digitsToDisplay[i]]);  // Write segment data
  }
  
  wireInterface.endTransmission();
}
