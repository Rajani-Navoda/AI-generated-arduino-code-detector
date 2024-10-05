#include <aREST.h>

// Create an instance of the aREST class
aREST rest = aREST();

// Define a variable to demonstrate remote control
int ledPin = 13;
int ledState = LOW;

// Setup function runs once at startup
void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize the LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Attach the aREST library to the Serial port
  rest.function("led", ledControl);
  rest.variable("ledState", &ledState);

  // Print initialization message
  Serial.println("aREST server is running. You can interact with it via HTTP requests.");
}

// Loop function runs repeatedly
void loop() {
  // Update the aREST library with incoming Serial data
  rest.handle(client);
}

// Function to control the LED
int ledControl(String command) {
  if (command == "on") {
    ledState = HIGH;
  } else if (command == "off") {
    ledState = LOW;
  } else {
    return -1; // Invalid command
  }
  digitalWrite(ledPin, ledState);
  return ledState;
}
