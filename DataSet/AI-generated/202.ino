#include <AceSPI.h>  // Include AceSPI library for SPI communication

using ace_spi::HardSpiInterface;

// Pin definitions for the 74HC595
const int latchPin = 10;  // ST_CP latch pin of 74HC595
const int enablePin = 9;  // Optional, used to control brightness via PWM
const int numDigits = 8;  // Number of digits in the display (8 digits)

// SPI configuration
HardSpiInterface spiInterface(13, 11, 12);  // SCK, MOSI, MISO (MISO not needed)

// Segment data for displaying digits 0-7 (common anode setup, adjust if common cathode)
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

// Array to hold the digits to be displayed (0-7)
byte digitsToDisplay[numDigits] = {0, 1, 2, 3, 4, 5, 6, 7};

// Multiplexing variables
int currentDigit = 0;
unsigned long lastUpdateTime = 0;
const unsigned long multiplexDelay = 2000;  // Delay between multiplexing (2ms)

// Brightness control (using enablePin and PWM)
int brightness = 128;  // Brightness value (0-255)

void setup() {
  // Setup pin modes
  pinMode(latchPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  // Initialize SPI interface
  spiInterface.begin();
  
  // Set initial brightness using PWM
  analogWrite(enablePin, brightness);
}

void loop() {
  // Multiplexing: cycle through digits faster than human response time (~16ms)
  if (micros() - lastUpdateTime >= multiplexDelay) {
    lastUpdateTime = micros();
    
    // Shift out data for the current digit and segment pattern
    shiftOutData(currentDigit);
    
    // Move to the next digit (loop back after the last digit)
    currentDigit = (currentDigit + 1) % numDigits;
  }
}

// Function to shift out data to 74HC595 using SPI
void shiftOutData(int digitIndex) {
  // Disable output (optional for reducing flicker)
  digitalWrite(latchPin, LOW);
  
  // Send data to the 74HC595
  spiInterface.transfer(digitPatterns[digitsToDisplay[digitIndex]]);  // Send segment data
  spiInterface.transfer(1 << digitIndex);  // Enable the corresponding digit

  // Latch the data to the 74HC595 (output to display)
  digitalWrite(latchPin, HIGH);
}
