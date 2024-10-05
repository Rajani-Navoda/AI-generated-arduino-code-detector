#include <AD5254_asukiaaa.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin
const int CLK_PIN = 13; // Clock pin
const int DATA_PIN = 11; // Data pin

AD5254 pot(CLK_PIN, DATA_PIN, CS_PIN);

void setup() {
  Serial.begin(9600);
  pot.begin();
  
  // Load initial values from memory
  loadInitialValues();
}

void loop() {
  // Optionally, you can add code to change wiper positions dynamically
  // or read and print the wiper values periodically
  delay(1000);
}

void loadInitialValues() {
  // Assuming we have two potentiometers in this example
  for (int i = 0; i < 2; i++) {
    // Read the wiper position from the specified potentiometer
    uint8_t wiperValue = pot.readWiper(i);
    Serial.print("Wiper Value for Potentiometer ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(wiperValue);

    // Optionally, you can load this value into another potentiometer
    // Here we're just setting it back to itself for demonstration
    pot.setWiper(i, wiperValue);
    Serial.print("Wiper Value loaded for Potentiometer ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(wiperValue);
  }
}
