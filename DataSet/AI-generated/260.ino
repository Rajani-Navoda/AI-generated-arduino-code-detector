
#include <SPI.h>

const int CS_PIN = 22;  // Chip Select pin for the ADC
const int SCLK_PIN = 18; // Serial Clock pin
const int MISO_PIN = 19; // Master In Slave Out pin
const int MOSI_PIN = 23; // Master Out Slave In pin

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud
  pinMode(CS_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(MOSI_PIN, OUTPUT);
  
  digitalWrite(CS_PIN, HIGH); // Set CS high (inactive)
  SPI.begin(SCLK_PIN, MISO_PIN, MOSI_PIN, CS_PIN); // Initialize SPI
}

void loop() {
  float adcValue = readADC(); // Read value from the ADC
  Serial.println(adcValue); // Print ADC value to Serial Monitor
  delay(500); // Wait before the next reading
}

// Function to read the ADC value
float readADC() {
  digitalWrite(CS_PIN, LOW); // Enable ADC by setting CS low
  
  // Send a command to read the ADC value
  byte command = 0x00; // Example command (modify as per ADC's datasheet)
  byte highByte = SPI.transfer(command); // Read high byte
  byte lowByte = SPI.transfer(0x00); // Read low byte
  
  digitalWrite(CS_PIN, HIGH); // Disable ADC by setting CS high

  // Combine high byte and low byte to get the ADC value
  int adcRawValue = (highByte << 8) | lowByte;
  
  // Convert raw ADC value to voltage (if needed)
  float voltage = (adcRawValue * 3.3) / 1023.0; // Adjust for your ADC resolution (10-bit example)
  return voltage;
}