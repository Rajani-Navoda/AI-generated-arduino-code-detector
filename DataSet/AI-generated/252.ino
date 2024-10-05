#include <SPI.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin for the AD7124
const int LED_PIN = 9;  // LED pin

// Function prototypes
void setupAD7124();
float readVoltage();
void blinkLED(int times);

void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Set CS high (inactive)

  SPI.begin();
  setupAD7124(); // Initialize the AD7124

  Serial.println("AD7124 Voltmeter");
}

void loop() {
  // Read voltage at AIN1/AIN0
  float voltage = readVoltage();

  Serial.print("Measured Voltage (V): ");
  Serial.println(voltage);

  // Blink the LED to indicate a reading
  blinkLED(1);

  delay(1000); // Wait before the next read
}

// Function to initialize the AD7124
void setupAD7124() {
  // Example register initialization for the AD7124
  // This will need to be customized based on your configuration needs
  // Write to configuration registers here
}

// Function to read the voltage from AIN1/AIN0
float readVoltage() {
  // Add the code to read from the AIN1/AIN0 channel
  // Implement the conversion from ADC reading to voltage
  uint32_t rawValue = 0; // Placeholder for raw ADC reading
  // SPI communication to read raw value goes here
  // e.g., rawValue = readRegister(...);

  // Convert raw ADC value to voltage
  float voltage = (rawValue / 16777215.0) * 2.5; // Example conversion for 24-bit ADC
  return voltage; // Return the measured voltage
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
