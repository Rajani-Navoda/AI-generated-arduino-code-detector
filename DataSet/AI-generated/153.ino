#include <DCCpp.h>    // Include the DCC++ library

// Define the DCC control pins
const int turnoutPin1 = 2; // Digital pin for Turnout 1
const int turnoutPin2 = 3; // Digital pin for Turnout 2
const int lightPin1 = 4;   // Digital pin for Light 1
const int lightPin2 = 5;   // Digital pin for Light 2

void setup() {
  // Initialize the DCC library
  DCC::setup(); // Ensure your library initialization is correct
  
  // Set pin modes
  pinMode(turnoutPin1, OUTPUT);
  pinMode(turnoutPin2, OUTPUT);
  pinMode(lightPin1, OUTPUT);
  pinMode(lightPin2, OUTPUT);
  
  // Initialize all devices to off
  digitalWrite(turnoutPin1, LOW);
  digitalWrite(turnoutPin2, LOW);
  digitalWrite(lightPin1, LOW);
  digitalWrite(lightPin2, LOW);
}

void loop() {
  // Check for incoming DCC commands
  DCC::process();  // Process any received DCC commands
  
  // Example: Turnout control based on DCC commands
  if (DCC::isAccessoryOn(1)) {
    digitalWrite(turnoutPin1, HIGH); // Turnout 1
  } else {
    digitalWrite(turnoutPin1, LOW);
  }

  if (DCC::isAccessoryOn(2)) {
    digitalWrite(turnoutPin2, HIGH); // Turnout 2
  } else {
    digitalWrite(turnoutPin2, LOW);
  }
  
  // Example: Light control based on DCC commands
  if (DCC::isAccessoryOn(3)) {
    digitalWrite(lightPin1, HIGH); // Light 1
  } else {
    digitalWrite(lightPin1, LOW);
  }

  if (DCC::isAccessoryOn(4)) {
    digitalWrite(lightPin2, HIGH); // Light 2
  } else {
    digitalWrite(lightPin2, LOW);
  }
  
  delay(100);  // Small delay for stability
}
