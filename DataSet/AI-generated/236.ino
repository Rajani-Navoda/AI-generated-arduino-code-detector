#include <AD5231.h> // Include the AD5231 library

// Define the I2C address of the AD5231
#define AD5231_ADDRESS 0x2C // Adjust as necessary for your setup

AD5231 pot(AD5231_ADDRESS); // Create an instance of the AD5231

const int analogPin = A1; // Analog pin where the manual potentiometer is connected

void setup() {
  Serial.begin(9600); // Start serial communication

  // Initialize the AD5231
  pot.begin();
  pot.setWiper(0); // Set the initial wiper value to 0
}

void loop() {
  // Read the value from the manual potentiometer (0-1023)
  int manualValue = analogRead(analogPin);

  // Map the manual value to the wiper range (0-127)
  int wiperValue = map(manualValue, 0, 1023, 0, 127);

  // Set the wiper of the AD5231
  pot.setWiper(wiperValue);

  // Print the manual potentiometer value and the corresponding wiper value
  Serial.print("Manual Potentiometer Value: ");
  Serial.print(manualValue);
  Serial.print(" | Wiper Value: ");
  Serial.println(wiperValue);

  // Delay for a short period
  delay(500);
}
