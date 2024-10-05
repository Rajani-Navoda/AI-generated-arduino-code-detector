#include <AD5231.h> // Include the AD5231 library

// Define the I2C address of the AD5231
#define AD5231_ADDRESS 0x2C // Adjust as necessary for your setup

AD5231 pot(AD5231_ADDRESS); // Create an instance of the AD5231

void setup() {
  Serial.begin(9600); // Start serial communication

  // Initialize the AD5231
  pot.begin();
  pot.setWiper(0); // Set the initial wiper value (0-127 for 128 steps)
}

void loop() {
  // Get the current wiper value
  int wiperValue = pot.getWiper();
  
  // Calculate the resistance (assuming a 10kΩ pot, adjust as needed)
  float totalResistance = 10000.0; // Total resistance of the potentiometer
  float resistance = (wiperValue / 127.0) * totalResistance;

  // Print the wiper value and calculated resistance
  Serial.print("Wiper Value: ");
  Serial.print(wiperValue);
  Serial.print(" | Calculated Resistance: ");
  Serial.print(resistance);
  Serial.println(" ohms");

  // Delay for a second before the next reading
  delay(1000);
}
