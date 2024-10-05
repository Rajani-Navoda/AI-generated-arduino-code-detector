#include <SPI.h>

// Define pins
const int CS_PIN = 10; // Chip select pin for the AD7124-8

// AD7124-8 command definitions
#define READ_REGISTER 0x00
#define WRITE_REGISTER 0x40
#define READ_DATA 0x20

// Function prototypes
void writeRegister(uint8_t reg, uint32_t value);
uint32_t readRegister(uint8_t reg);
uint32_t readData();

void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  SPI.begin();
  // Initialize the AD7124-8 (set up necessary registers)
  // Example: configure the desired channels
  // writeRegister(CHANNEL_REGISTER, channelSettings);
  // Add any other initial configurations as needed

  Serial.println("AD7124-8 Continuous Sampling Example");
}

void loop() {
  // Read data from differential pairs 2&3 to 12&13
  for (int channel = 2; channel <= 13; channel += 2) {
    uint32_t voltage = readData(channel);
    Serial.print("Voltage at channel ");
    Serial.print(channel);
    Serial.print(": ");
    Serial.println(voltage);
    
    // Control the sample rate based on your filterWord settings
    delay(100); // Adjust the delay as needed
  }
}

// Function to write a value to a register
void writeRegister(uint8_t reg, uint32_t value) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(WRITE_REGISTER | reg);
  SPI.transfer((value >> 24) & 0xFF);
  SPI.transfer((value >> 16) & 0xFF);
  SPI.transfer((value >> 8) & 0xFF);
  SPI.transfer(value & 0xFF);
  digitalWrite(CS_PIN, HIGH);
}

// Function to read a value from a register
uint32_t readRegister(uint8_t reg) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(READ_REGISTER | reg);
  uint32_t value = (SPI.transfer(0) << 24) |
                   (SPI.transfer(0) << 16) |
                   (SPI.transfer(0) << 8) |
                   SPI.transfer(0);
  digitalWrite(CS_PIN, HIGH);
  return value;
}

// Function to read data from the specified channel
uint32_t readData(int channel) {
  // Select the appropriate register or channel settings here
  // Example: configure the ADC to read from the specified channel
  // writeRegister(CHANNEL_REGISTER, channelSettings);
  
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(READ_DATA | channel);
  uint32_t value = (SPI.transfer(0) << 24) |
                   (SPI.transfer(0) << 16) |
                   (SPI.transfer(0) << 8) |
                   SPI.transfer(0);
  digitalWrite(CS_PIN, HIGH);
  return value;
}
