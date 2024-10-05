#include <Wire.h>
#include <TEA5767.h>  // Ensure you have the TEA5767 library installed

// Create a TEA5767 instance
TEA5767 radio;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize the radio
  if (!radio.begin()) {
    Serial.println("Failed to initialize radio!");
    while (1); // Halt
  }
  
  Serial.println("Radio initialized.");
  radio.setFrequency(100.0);  // Set initial frequency to 100.0 MHz
}

void loop() {
  // Display current frequency
  float currentFreq = radio.getFrequency();
  Serial.print("Current Frequency: ");
  Serial.println(currentFreq);

  // Tune up
  if (digitalRead(2) == LOW) {  // Assume a button on pin 2 to tune up
    currentFreq += 0.1; // Tune up by 0.1 MHz
    radio.setFrequency(currentFreq);
    delay(500); // Debounce delay
  }
  
  // Tune down
  if (digitalRead(3) == LOW) {  // Assume a button on pin 3 to tune down
    currentFreq -= 0.1; // Tune down by 0.1 MHz
    radio.setFrequency(currentFreq);
    delay(500); // Debounce delay
  }

  delay(1000); // Update every second
}
