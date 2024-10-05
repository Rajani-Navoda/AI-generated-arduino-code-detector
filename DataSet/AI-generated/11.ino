#include <ALog.h>  // Include the ALog library

// Define the LED pin (use LED_BUILTIN for most Arduino boards)
const int ledPin = LED_BUILTIN;

// Create an instance of the ALog class
ALog logger;

void setup() {
  // Initialize serial communication for logging
  Serial.begin(9600);
  logger.begin(Serial);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Log the startup message
  logger.log("BottleLogger started. LED blinking...");
}

void loop() {
  // Turn the LED on and log the action
  digitalWrite(ledPin, HIGH);
  logger.log("LED ON");
  
  // Wait for one second
  delay(1000);

  // Turn the LED off and log the action
  digitalWrite(ledPin, LOW);
  logger.log("LED OFF");

  // Wait for one second
  delay(1000);
}
