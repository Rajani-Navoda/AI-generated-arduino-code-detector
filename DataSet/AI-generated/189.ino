#include <stdint.h>
#include <Arduino.h>

// Define the analog pin for reading button values
const int ANALOG_PIN = A0; // Pin connected to the resistor ladder

// Define the threshold values for button detection
const int BUTTON1_THRESHOLD = 100;  // Threshold for Button 1
const int BUTTON2_THRESHOLD = 400;  // Threshold for Button 2
const int BUTTON3_THRESHOLD = 800;  // Threshold for Button 3

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read the value from the analog pin
  int analogValue = analogRead(ANALOG_PIN);
  
  // Print the analog value to the Serial Monitor
  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  
  // Determine which button is pressed based on the analog value
  if (analogValue < BUTTON1_THRESHOLD) {
    Serial.println("Button 1 Pressed");
  } else if (analogValue < BUTTON2_THRESHOLD) {
    Serial.println("Button 2 Pressed");
  } else if (analogValue < BUTTON3_THRESHOLD) {
    Serial.println("Button 3 Pressed");
  } else {
    Serial.println("No Button Pressed");
  }

  delay(500); // Wait for a short period before reading again
}
