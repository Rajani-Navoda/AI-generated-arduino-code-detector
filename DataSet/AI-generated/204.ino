#include <AceSPI.h>   // Include AceSPI library for SPI communication

using ace_spi::HardSpiInterface;

// Pin definitions
const int csPin = 10;  // Chip select pin for MAX7219

// SPI interface using HardSpiInterface from AceSPI
HardSpiInterface spiInterface(13, 11, 12);  // SCK, MOSI, MISO (MISO not used)

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

// Digit patterns for 7-segment display (0-7)
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

// Array to hold digits to be displayed
byte digitsToDisplay[8] = {0, 1, 2, 3, 4, 5, 6, 7};

// Brightness control (0-15 for MAX7219)
int brightness = 8;

void setup() {
  // Setup chip select pin
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);  // Disable the chip initially

  // Initialize SPI interface
  spiInterface.begin();

  // Initialize MAX7219
  initMAX7219();

  // Set brightness
  setBrightness(brightness);

  // Render the initial digits to the display
  renderDisplay();
}

void loop() {
  // Example: dynamically change the display if needed in the loop
}

// Function to initialize the MAX7219
void initMAX7219() {
  // Disable shutdown mode
  sendCommand(MAX7219_REG_SHUTDOWN, 0x01);

  // Set scan limit to display all 8 digits
  sendCommand(MAX7219_REG_SCANLIMIT, 0x07);

  // Set decode mode to 'no decode' for 7-segment data
  sendCommand(MAX7219_REG_DECODEMODE, 0x00);

  // Turn off display test mode
  sendCommand(MAX7219_REG_DISPLAYTEST, 0x00);
}

// Function to set brightness (0-15)
void setBrightness(int level) {
  level = constrain(level, 0, 15);  // Ensure brightness is within the valid range
  sendCommand(MAX7219_REG_INTENSITY, level);
}

// Function to render the digits to the 8-digit display
void renderDisplay() {
  for (int i = 0; i < 8; i++) {
    sendCommand(MAX7219_REG_DIGIT0 + i, digitPatterns[digitsToDisplay[i]]);
  }
}

// Function to send commands to MAX7219 using SPI
void sendCommand(byte address, byte data) {
  // Start communication by pulling CS pin low
  digitalWrite(csPin, LOW);
  
  // Send address and data over SPI
  spiInterface.transfer(address);  // Send the register address
  spiInterface.transfer(data);     // Send the corresponding data
  
  // End communication by pulling CS pin high
  digitalWrite(csPin, HIGH);
}
