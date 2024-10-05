#include <AceSPI.h>   // AceSPI library for SPI communication

using ace_spi::HardSpiInterface;

// Define pin for Chip Select (CS)
const int csPin = 10;  // Chip Select pin for the MAX7219

// SPI interface using AceSPI HardSpiInterface (SCK = 13, MOSI = 11, MISO = 12 (not used))
HardSpiInterface spiInterface(13, 11, 12);

// MAX7219 register addresses
const byte MAX7219_REG_NOOP = 0x00;
const byte MAX7219_REG_DIGIT0 = 0x01;
const byte MAX7219_REG_DIGIT1 = 0x02;
const byte MAX7219_REG_DIGIT2 = 0x03;
const byte MAX7219_REG_DIGIT3 = 0x04;
const byte MAX7219_REG_DIGIT4 = 0x05;
const byte MAX7219_REG_DIGIT5 = 0x06;
const byte MAX7219_REG_DIGIT6 = 0x07;
const byte MAX7219_REG_DIGIT7 = 0x08;
const byte MAX7219_REG_DECODEMODE = 0x09;
const byte MAX7219_REG_INTENSITY = 0x0A;
const byte MAX7219_REG_SCANLIMIT = 0x0B;
const byte MAX7219_REG_SHUTDOWN = 0x0C;
const byte MAX7219_REG_DISPLAYTEST = 0x0F;

// Digit patterns for the 7-segment display (0-7)
const byte digitPatterns[] = {
  0b01111110, // 0
  0b00110000, // 1
  0b01101101, // 2
  0b01111001, // 3
  0b00110011, // 4
  0b01011011, // 5
  0b01011111, // 6
  0b01110000  // 7
};

// Array to hold the digits to display on the 8-digit LED module
byte digitsToDisplay[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// Brightness control (0-15 for MAX7219)
int brightness = 8;

void setup() {
  // Setup the chip select pin
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);  // Disable the chip at the start

  // Initialize SPI interface
  spiInterface.begin();

  // Initialize MAX7219
  initMAX7219();

  // Set the brightness level
  setBrightness(brightness);

  // Render the initial digits to the display
  renderDisplay();
}

void loop() {
  // Example: if you need to dynamically update the display, you can do that here
}

// Function to initialize the MAX7219 controller
void initMAX7219() {
  // Disable shutdown mode (turn on the display)
  sendCommand(MAX7219_REG_SHUTDOWN, 0x01);

  // Set scan limit to display all 8 digits
  sendCommand(MAX7219_REG_SCANLIMIT, 0x07);

  // Set decode mode to 'no decode' for 7-segment data (direct segment control)
  sendCommand(MAX7219_REG_DECODEMODE, 0x00);

  // Turn off display test mode
  sendCommand(MAX7219_REG_DISPLAYTEST, 0x00);
}

// Function to set brightness (0-15)
void setBrightness(int level) {
  level = constrain(level, 0, 15);  // Ensure brightness level is within valid range
  sendCommand(MAX7219_REG_INTENSITY, level);
}

// Function to render the digits to the 8-digit LED display
void renderDisplay() {
  for (int i = 0; i < 8; i++) {
    sendCommand(MAX7219_REG_DIGIT0 + i, digitPatterns[digitsToDisplay[i]]);
  }
}

// Function to send a command to the MAX7219 using SPI
void sendCommand(byte address, byte data) {
  // Pull CS low to begin the SPI transmission
  digitalWrite(csPin, LOW);
  
  // Send the address and data to the MAX7219
  spiInterface.transfer(address);  // Send the register address
  spiInterface.transfer(data);     // Send the corresponding data
  
  // Pull CS high to end the SPI transmission
  digitalWrite(csPin, HIGH);
}
