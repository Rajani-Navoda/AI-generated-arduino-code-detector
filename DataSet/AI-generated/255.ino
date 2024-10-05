/*
  Example sketch to send value to DAC via serial interface.
  Open serial connection, type value between 0 and 4095 and press enter.
  Check newline (NL) terminator in your terminal.
*/

#include <SPI.h> // Include the SPI library for DAC communication

const int DAC_CS_PIN = 10; // Chip Select pin for the DAC

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  pinMode(DAC_CS_PIN, OUTPUT);
  digitalWrite(DAC_CS_PIN, HIGH); // Set CS high (inactive)
}

void loop() {
  if (Serial.available()) { // Check if data is available to read
    int value = Serial.parseInt(); // Read the integer from serial input

    if (value >= 0 && value <= 4095) { // Check if the value is within range
      writeDAC(value); // Send the value to the DAC
      Serial.print("Value sent to DAC: ");
      Serial.println(value);
    } else {
      Serial.println("Please enter a value between 0 and 4095.");
    }
  }
}

// Function to write a value to the DAC
void writeDAC(int value) {
  digitalWrite(DAC_CS_PIN, LOW); // Enable the DAC by pulling CS low
  SPI.transfer((value >> 8) & 0xFF); // Send the high byte
  SPI.transfer(value & 0xFF); // Send the low byte
  digitalWrite(DAC_CS_PIN, HIGH); // Disable the DAC by pulling CS high
}
