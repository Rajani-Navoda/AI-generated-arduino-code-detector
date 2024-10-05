#include <SPI.h>

const int CS_PIN = 10; // Chip Select pin for the AD7193

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Set CS high (inactive)
  SPI.begin();
  initializeAD7193(); // Initialize the AD7193
}

void loop() {
  float voltage = readDifferentialVoltage(); // Read differential voltage from the AD7193
  Serial.print("Differential Voltage (V): ");
  Serial.println(voltage, 6); // Print the voltage with 6 decimal places
  delay(1000); // Wait before the next reading
}

// Function to initialize the AD7193
void initializeAD7193() {
  // Write configuration settings to the AD7193 for differential measurement
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x00); // Example command to initialize (replace with actual command)
  // Add further initialization commands as needed
  digitalWrite(CS_PIN, HIGH);
}

// Function to read the differential voltage from the AD7193
float readDifferentialVoltage() {
  digitalWrite(CS_PIN, LOW);
  // Read the data from the AD7193
  uint32_t rawValue = SPI.transfer(0x00); // Replace with the correct read command
  digitalWrite(CS_PIN, HIGH);
  
  // Convert raw ADC value to voltage (V)
  // Adjust the conversion based on your configuration and reference
  float voltage = (rawValue * 3.3) / 8388608.0; // Example conversion (3.3V reference)
  return voltage;
}