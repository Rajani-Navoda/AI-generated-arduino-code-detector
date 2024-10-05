#include <AD5231.h> // Include the AD5231 library

// Define the I2C address of the AD5231
#define AD5231_ADDRESS 0x2C // Adjust if necessary

AD5231 pot(AD5231_ADDRESS); // Create an instance of the AD5231

void setup() {
  Serial.begin(9600); // Start serial communication

  // Initialize the AD5231
  pot.begin();

  // Testing various functions
  testAD5231();
}

void loop() {
  // No need for repeated testing in loop; put code here if you want to repeat actions
}

void testAD5231() {
  Serial.println("Starting AD5231 Test...");

  // 1. Read the Wiper Position
  int wiperValue = pot.getWiper();
  Serial.print("Wiper Position: ");
  Serial.println(wiperValue);

  // 2. Read Memory
  uint8_t memoryValue = pot.readMemory();
  Serial.print("Memory Value: ");
  Serial.println(memoryValue);

  // 3. Save New Data to Memory
  pot.writeMemory(64); // Example value
  Serial.println("Saved 64 to memory.");

  // 4. Set Wiper Position
  pot.setWiper(32);
  Serial.println("Wiper set to position 32.");

  // 5. Save Wiper Position to Memory
  pot.saveWiperToMemory();
  Serial.println("Wiper position saved to memory.");

  // 6. Reset the Digital Potentiometer
  pot.reset();
  Serial.println("Digital Potentiometer reset.");

  // 7. Toggle Logic Pins O1 & O2
  pot.toggleLogicPins();
  Serial.println("Logic pins toggled.");

  // 8. Increase Wiper Position by One
  wiperValue = pot.getWiper();
  pot.setWiper(wiperValue + 1);
  Serial.print("Increased Wiper Position to: ");
  Serial.println(pot.getWiper());

  // 9. Decrease Wiper Position by One
  wiperValue = pot.getWiper();
  pot.setWiper(wiperValue - 1);
  Serial.print("Decreased Wiper Position to: ");
  Serial.println(pot.getWiper());
}

