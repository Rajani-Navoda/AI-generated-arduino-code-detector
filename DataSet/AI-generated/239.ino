#include <AD5231.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin for AD5231
const int CLK_PIN = 13; // Clock pin
const int DATA_PIN = 11; // Data pin
const int POT_PIN = A1; // Analog pin for manual potentiometer

AD5231 pot(CLK_PIN, DATA_PIN, CS_PIN);

// Maximum wiper value for AD5231
const uint8_t MAX_WIPER_VALUE = 255;

void setup() {
  Serial.begin(9600);
  pot.begin();
}

void loop() {
  // Read the manual potentiometer value
  int potValue = analogRead(POT_PIN);
  
  // Map the potentiometer value (0-1023) to wiper value (0-255)
  uint8_t wiperValue = map(potValue, 0, 1023, 0, MAX_WIPER_VALUE);
  
  // Set the wiper of the AD5231
  pot.setWiper(wiperValue);
  
  // Display the wiper value on Serial Monitor
  Serial.print("Manual Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(", Wiper Value: ");
  Serial.println(wiperValue);
  
  delay(100); // Short delay for readability
}
