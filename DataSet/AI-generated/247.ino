#include <BreadcrumbsAD57X4R.h>

// Pin definitions
const int CS_PIN_1 = 10; // Chip select pin for DAC 1
const int CS_PIN_2 = 11; // Chip select pin for DAC 2
const int LDAC_PIN = 9;  // Load DAC pin (if needed)
const int RST_PIN = 8;   // Reset pin (if used)

BreadcrumbsAD57X4R dac1(CS_PIN_1, LDAC_PIN, RST_PIN);
BreadcrumbsAD57X4R dac2(CS_PIN_2, LDAC_PIN, RST_PIN);

// DAC settings
const int MAX_VALUE = 4095; // Maximum value for 12-bit DAC

void setup() {
  Serial.begin(9600);
  dac1.begin();
  dac2.begin();
  
  Serial.println("Multi-Chip DAC Control");
}

void loop() {
  for (int value = 0; value <= MAX_VALUE; value += 100) {
    // Set values for each DAC independently
    dac1.setValue(0, value); // Set channel 0 of DAC 1
    dac2.setValue(0, MAX_VALUE - value); // Set channel 0 of DAC 2
    dac1.update(); // Update DAC 1
    dac2.update(); // Update DAC 2
    
    Serial.print("DAC 1 Channel 0 set to: ");
    Serial.print(value);
    Serial.print(" | DAC 2 Channel 0 set to: ");
    Serial.println(MAX_VALUE - value);
    
    delay(100); // Delay for smooth transition
  }

  // Reset both DACs to 0
  dac1.setValue(0, 0);
  dac2.setValue(0, 0);
  dac1.update();
  dac2.update();
  delay(1000);
}
