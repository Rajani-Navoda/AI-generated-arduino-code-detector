#include <BreadcrumbsAD57X4R.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin
const int LDAC_PIN = 9; // Load DAC pin (if needed)
const int RST_PIN = 8;  // Reset pin (if used)

BreadcrumbsAD57X4R dac(CS_PIN, LDAC_PIN, RST_PIN);

// DAC settings
const int NUM_CHANNELS = 4; // Number of DAC channels
const int MAX_VALUE = 4095;  // Maximum value for 12-bit DAC
const int DELAY_TIME = 100;   // Delay time in milliseconds

void setup() {
  Serial.begin(9600);
  dac.begin();
}

void loop() {
  // Update all channels simultaneously
  for (int value = 0; value <= MAX_VALUE; value += 100) {
    for (int channel = 0; channel < NUM_CHANNELS; channel++) {
      dac.setValue(channel, value); // Set value for each channel
    }
    dac.update(); // Update all DAC channels simultaneously
    delay(DELAY_TIME); // Delay for a smooth transition
  }

  // Reset all channels to 0
  for (int channel = 0; channel < NUM_CHANNELS; channel++) {
    dac.setValue(channel, 0);
  }
  dac.update(); // Final update to set all channels to 0
  delay(DELAY_TIME);
}
