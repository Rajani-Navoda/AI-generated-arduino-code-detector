#include <AD5231.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin
const int CLK_PIN = 13; // Clock pin
const int DATA_PIN = 11; // Data pin

AD5231 pot(CLK_PIN, DATA_PIN, CS_PIN);

// Function to calculate resistance based on wiper value
float calculateResistance(uint8_t wiperValue) {
  // Define the maximum resistance (ohms) according to your potentiometer
  const float maxResistance = 10000.0; // e.g., 10k ohms
  return (maxResistance * wiperValue) / 255.0; // 255 is the max wiper value
}

void setup() {
  Serial.begin(9600);
  pot.begin();
  
  // Set the wiper to a specific value (0-255)
  uint8_t wiperValue = 128; // Example: set to mid-scale
  pot.setWiper(wiperValue);
  
  // Calculate and display resistance
  float resistance = calculateResistance(wiperValue);
  Serial.print("Wiper Value: ");
  Serial.print(wiperValue);
  Serial.print(", Resistance: ");
  Serial.print(resistance);
  Serial.println(" ohms");
}

void loop() {
  // Add your loop code here if needed
}
