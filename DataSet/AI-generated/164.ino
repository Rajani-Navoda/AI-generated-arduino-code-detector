#include <Wire.h>

// I2C address of PCA9505/PCA9506 (modify according to your setup)
#define PCA9505_ADDRESS 0x20

const int ledPin = 0; // GPIO pin to which LED is connected (e.g., P0_0)

// Register addresses (based on PCA9505/PCA9506 datasheet)
#define IODIR_REG 0x00 // I/O direction register
#define GPIO_REG  0x09 // GPIO register

void setup() {
  Wire.begin(); // Initialize I2C communication
  Serial.begin(9600); // Initialize Serial for debugging

  // Initialize the PCA9505/PCA9506
  initPCA9505();

  // Turn off the LED initially
  setGPIO(ledPin, LOW);
}

void loop() {
  // Blink the LED
  setGPIO(ledPin, HIGH); // Turn on LED
  delay(1000);           // Wait for 1 second
  setGPIO(ledPin, LOW);  // Turn off LED
  delay(1000);           // Wait for 1 second

  // Print to Serial Monitor
  Serial.println("LED blinked!");
}

// Function to initialize the PCA9505/PCA9506
void initPCA9505() {
  Wire.beginTransmission(PCA9505_ADDRESS);
  Wire.write(IODIR_REG); // Address of IODIR register
  Wire.write(0xFF);      // Set all pins as output (0x00 for input)
  Wire.endTransmission();
}

// Function to set GPIO value
void setGPIO(int pin, bool value) {
  Wire.beginTransmission(PCA9505_ADDRESS);
  Wire.write(GPIO_REG);       // Address of GPIO register
  Wire.write((1 << pin) * value); // Set or clear the specific pin
  Wire.endTransmission();
}
