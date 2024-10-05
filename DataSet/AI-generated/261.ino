
#include <SPI.h>

const int W_CLK = 10; // Word Clock (Chip Select)
const int FQ_UD = 9;  // Frequency Update Pin
const int RESET = 8;  // Reset Pin

void setup() {
  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UD, OUTPUT);
  pinMode(RESET, OUTPUT);
  
  SPI.begin(); // Initialize SPI

  resetAD9850(); // Reset the AD9850
  setFrequency(1000000); // Set frequency to 1 MHz as an example
}

void loop() {
  // No continuous operation in this example, the frequency is set in setup.
}

// Function to reset AD9850
void resetAD9850() {
  digitalWrite(RESET, LOW);
  delay(10);
  digitalWrite(RESET, HIGH);
  delay(10);
  digitalWrite(RESET, LOW);
}

// Function to set frequency on AD9850
void setFrequency(long frequency) {
  long freqWord = (frequency * 4294967296) / 125000000; // Calculate the tuning word
  for (int i = 0; i < 4; i++) {
    SPI.transfer(freqWord >> (i * 8)); // Send 32-bit frequency tuning word, LSB first
  }
  
  SPI.transfer(0x000); // Control byte (for phase and power-down bits if needed)
  
  pulseFQ_UD(); // Pulse the FQ_UD pin to update frequency
}

// Function to pulse FQ_UD pin
void pulseFQ_UD() {
  digitalWrite(FQ_UD, LOW);
  delayMicroseconds(1);
  digitalWrite(FQ_UD, HIGH);
  delayMicroseconds(1);
  digitalWrite(FQ_UD, LOW);
}