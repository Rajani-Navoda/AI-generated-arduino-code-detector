#include <BreadcrumbsAD57X4R.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin
const int LDAC_PIN = 9; // Load DAC pin (if needed)
const int RST_PIN = 8;  // Reset pin (if used)

BreadcrumbsAD57X4R dac(CS_PIN, LDAC_PIN, RST_PIN);

// DAC settings
const int MAX_VALUE = 4095; // Maximum value for 12-bit DAC
const int STEP_SIZE = 1;     // Increment step size
const int DELAY_TIME = 10;   // Delay time in milliseconds

void setup() {
  Serial.begin(9600);
  dac.begin();
}

void loop() {
  for (int value = 0; value <= MAX_VALUE; value += STEP_SIZE) {
    dac.setValue(value); // Set DAC output
    delay(DELAY_TIME);   // Delay for smooth waveform
  }
  // Reset to 0 to create the sawtooth effect
  dac.setValue(0);
}
