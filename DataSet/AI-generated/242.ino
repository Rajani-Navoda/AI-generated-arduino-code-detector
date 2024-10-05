#include <AD5254_asukiaaa.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin
const int CLK_PIN = 13; // Clock pin
const int DATA_PIN = 11; // Data pin

AD5254 pot(CLK_PIN, DATA_PIN, CS_PIN);

// Function prototypes
void readWiperValue();
void writeWiperValue(uint8_t value);

void setup() {
  Serial.begin(9600);
  pot.begin();

  // Read the initial wiper value
  readWiperValue();

  // Example: Set a new wiper value
  uint8_t newWiperValue = 128; // Set to mid-scale
  writeWiperValue(newWiperValue);
}

void loop() {
  // Periodically read the wiper value
  readWiperValue();
  delay(2000); // Wait 2 seconds before the next read
}

void readWiperValue() {
  // Read the wiper position from the potentiometer
  uint8_t wiperValue = pot.readWiper(0); // Reading from potentiometer 0
  Serial.print("Current Wiper Value: ");
  Serial.println(wiperValue);
}

void writeWiperValue(uint8_t value) {
  // Set the wiper position to a new value
  pot.setWiper(0, value); // Writing to potentiometer 0
  Serial.print("Wiper Value Set To: ");
  Serial.println(value);
  
  // Optionally, save to memory (if supported)
  pot.saveWiperToMemory(0);
  Serial.println("Wiper value saved to memory.");
}
