#include <Wire.h>
#include <Adafruit_MCP23017.h>

// Create an instance of the MCP23017 object
Adafruit_MCP23017 mcp;

const int ledPin = 0; // GPIO pin to which LED is connected (GPB0)

// Setup function
void setup() {
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize the MCP23017
  mcp.begin(); // Use default address 0x20
  
  // Set the GPIO pin as an output
  mcp.pinMode(ledPin, OUTPUT);
  
  // Turn off the LED initially
  mcp.digitalWrite(ledPin, LOW);
  
  // Serial communication for debugging
  Serial.begin(9600);
}

// Loop function
void loop() {
  // Blink the LED
  mcp.digitalWrite(ledPin, HIGH); // Turn on LED
  delay(1000);                    // Wait for 1 second
  mcp.digitalWrite(ledPin, LOW);  // Turn off LED
  delay(1000);                    // Wait for 1 second
  
  // Print to Serial Monitor
  Serial.println("LED blinked!");
}
