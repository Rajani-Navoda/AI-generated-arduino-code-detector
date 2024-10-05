#include <SPI.h>

// Pin definitions
const int CS_PIN = 10; // Chip select pin for the AD7124
const int LED_PIN = 9; // LED pin

// Function prototypes
void setupAD7124();
float readTemperature();
float readResistance();
void blinkLED(int times);

void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Set CS high (inactive)

  SPI.begin();
  setupAD7124(); // Initialize the AD7124

  Serial.println("CN-0381 RTD Thermometer");
}

void loop() {
  // Read temperature and resistance
  float temperature = readTemperature();
  float resistance = readResistance();

  Serial.print("Temperature (°C): ");
  Serial.print(temperature);
  Serial.print(", Resistance (Ω): ");
  Serial.println(resistance);

  // Blink the LED to indicate a reading
  blinkLED(1);

  delay(1000); // Wait before the next read
}

// Function to initialize the AD7124
void setupAD7124() {
  // Configure the necessary registers for the AD7124
  // Example initialization code (you will need to customize this)
  // writeRegister(...); // Write your register configuration here
}

// Function to read the temperature
float readTemperature() {
  // Add the code to read temperature from the RTD using the AD7124
  // Implement the conversion from ADC reading to temperature
  return 0.0; // Placeholder return value
}

// Function to read the resistance
float readResistance() {
  // Add the code to read resistance from the RTD
  return 0.0; // Placeholder return value
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
