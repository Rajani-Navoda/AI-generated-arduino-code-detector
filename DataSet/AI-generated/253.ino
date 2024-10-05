#include <SPI.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin for the AD7173
const int LED_PIN = 9;  // LED pin

// Function prototypes
void setupAD7173();
uint32_t readADCData();
void blinkLED(int times);
void writeRegister(uint8_t reg, uint32_t value);
uint32_t readRegister(uint8_t reg);

void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Set CS high (inactive)

  SPI.begin();
  setupAD7173(); // Initialize the AD7173

  Serial.println("AD7173 ADC Example");
}

void loop() {
  // Read data from the ADC
  uint32_t adcValue = readADCData();

  // Print the ADC value to the Serial Monitor
  Serial.print("ADC Value: ");
  Serial.println(adcValue);

  // Blink the LED to indicate a reading
  blinkLED(1);

  delay(1000); // Wait before the next read
}

// Function to initialize the AD7173
void setupAD7173() {
  // Configure the necessary registers for the AD7173
  writeRegister(0x00, 0x01); // Example: Write to a register (replace with actual config)
  // Add further register configurations as needed
}

// Function to read the ADC data
uint32_t readADCData() {
  digitalWrite(CS_PIN, LOW);
  delayMicroseconds(1); // Ensure time for CS to settle

  // Send command to read data
  SPI.transfer(0x20); // Example command to read data (replace with actual command)
  uint32_t value = (SPI.transfer(0) << 24) |
                   (SPI.transfer(0) << 16) |
                   (SPI.transfer(0) << 8) |
                   SPI.transfer(0);
                   
  digitalWrite(CS_PIN, HIGH);
  return value; // Return the raw ADC value
}

// Function to write a value to a register
void writeRegister(uint8_t reg, uint32_t value) {
  digitalWrite(CS_PIN, LOW);
  delayMicroseconds(1); // Ensure time for CS to settle

  SPI.transfer(reg); // Register address
  SPI.transfer((value >> 24) & 0xFF);
  SPI.transfer((value >> 16) & 0xFF);
  SPI.transfer((value >> 8) & 0xFF);
  SPI.transfer(value & 0xFF);

  digitalWrite(CS_PIN, HIGH);
}

// Function to blink the LED
void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, LOW); // Turn on LED
    delay(200);
    digitalWrite(LED_PIN, HIGH); // Turn off LED
    delay(200);
  }
}
