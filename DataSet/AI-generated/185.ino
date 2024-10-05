#include <AceButton.h>
#include <CapacitiveSensor.h>

using namespace AceButton;

// Define the button and capacitive sensor pins
const int buttonPin = 2; // Pin for AceButton
const int sendPin = 4;   // Pin for CapacitiveSensor
const int receivePin = 5; // Pin for CapacitiveSensor

CapacitiveSensor cs = CapacitiveSensor(sendPin, receivePin);
Button button(buttonPin);

void setup() {
  Serial.begin(9600);

  // Initialize button
  button.init();
  button.setEventHandler(buttonEvent);

  // Initialize capacitive sensor
  cs.setCSThreshold(1000); // Adjust this threshold based on your setup
}

void loop() {
  // Check button state
  button.read();

  // Check capacitive sensor
  long sensorValue = cs.capacitiveSensor(30);
  if (sensorValue > 1000) { // Adjust threshold for touch sensitivity
    Serial.println("Touch detected!");
  }

  delay(100); // Simple delay for readability
}

// Handle button events
void buttonEvent(AceButton* button, uint8_t eventType) {
  if (eventType == AceButton::kEventPressed) {
    Serial.println("Button pressed!");
  }
}
