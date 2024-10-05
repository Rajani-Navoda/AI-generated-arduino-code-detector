#include <AD5231.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin
const int CLK_PIN = 13; // Clock pin
const int DATA_PIN = 11; // Data pin
const int WIPER_PIN = A1; // Analog pin for reading wiper position

AD5231 pot(CLK_PIN, DATA_PIN, CS_PIN);

// Function prototypes
void testPotentiometer();

void setup() {
  Serial.begin(9600);
  pot.begin();
  testPotentiometer();
}

void loop() {
  // You can add additional functionality here if needed
}

void testPotentiometer() {
  // 1. Read the wiper position
  int wiperValue = pot.readWiper();
  Serial.print("Initial Wiper Position (0-255): ");
  Serial.println(wiperValue);

  // 2. Set the wiper to a given position
  uint8_t newWiperValue = 128; // Example value
  pot.setWiper(newWiperValue);
  Serial.print("Set Wiper Position to: ");
  Serial.println(newWiperValue);
  
  // 3. Read and print the wiper position again
  wiperValue = pot.readWiper();
  Serial.print("Current Wiper Position (0-255): ");
  Serial.println(wiperValue);
  
  // 4. Save wiper's position to memory
  pot.saveWiperToMemory();
  Serial.println("Wiper position saved to memory.");

  // 5. Reset the digital potentiometer
  pot.reset();
  Serial.println("AD5231 reset.");

  // 6. Read memory (for testing purposes, read back the wiper value)
  pot.setWiper(0); // Set to 0 to test memory reading
  pot.readWiper(); // Just to ensure it's functioning post-reset

  // 7. Toggle O1 and O2 logic pins (if connected)
  // Note: These pins are not connected in the original setup
  // Uncomment below if you wire them accordingly
  // pot.toggleO1();
  // pot.toggleO2();

  // 8. Increase and decrease the wiper position
  for (uint8_t i = 0; i < 5; i++) {
    pot.increaseWiperPosition();
    Serial.print("Wiper Increased to: ");
    Serial.println(pot.readWiper());
    delay(500);
  }
  
  for (uint8_t i = 0; i < 5; i++) {
    pot.decreaseWiperPosition();
    Serial.print("Wiper Decreased to: ");
    Serial.println(pot.readWiper());
    delay(500);
  }
}
