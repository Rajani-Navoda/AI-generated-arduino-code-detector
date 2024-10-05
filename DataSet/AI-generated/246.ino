#include <BreadcrumbsAD57X4R.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin
const int LDAC_PIN = 9; // Load DAC pin (if needed)
const int RST_PIN = 8;  // Reset pin (if used)

BreadcrumbsAD57X4R dac(CS_PIN, LDAC_PIN, RST_PIN);

// DAC settings
const int NUM_CHANNELS = 4; // Number of DAC channels
const int MAX_VALUE = 4095;  // Maximum value for 12-bit DAC

void setup() {
  Serial.begin(9600);
  dac.begin();
  Serial.println("Interactive DAC Control");
  Serial.println("Enter channel (0-3) and value (0-4095) separated by a space:");
}

void loop() {
  if (Serial.available() > 0) {
    int channel = Serial.parseInt();
    int value = Serial.parseInt();

    if (channel >= 0 && channel < NUM_CHANNELS && value >= 0 && value <= MAX_VALUE) {
      dac.setValue(channel, value); // Set the value for the specified channel
      dac.update(); // Update the DAC
      Serial.print("Set channel ");
      Serial.print(channel);
      Serial.print(" to value ");
      Serial.println(value);
    } else {
      Serial.println("Invalid input! Please enter channel (0-3) and value (0-4095).");
    }
  }
}
